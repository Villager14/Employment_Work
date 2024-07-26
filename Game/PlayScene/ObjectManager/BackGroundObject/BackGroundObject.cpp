/*
* @file		BackGroundObject.cpp
* @brief	背景オブジェクト
* @author	Morita
* @date		2024/05/23
*/

#include "pch.h"

#include "BackGroundObject.h"

#include "PostProcess.h"

#include "Common/ReaData.h"

BackGroundObject::BackGroundObject()
{
}

BackGroundObject::~BackGroundObject()
{
}

void BackGroundObject::Initialize(std::vector<ObjectMesh*> mesh,
	const std::vector<DirectX::SimpleMath::Vector3>& wirePosition)
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Background.cmo", *m_effect);

	m_floorModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			/*
			auto fog = dynamic_cast<DirectX::IEffectFog*>(effect);

			if (fog)
			{
				fog->SetFogEnabled(true);
				fog->SetFogStart(100.0f);
				fog->SetFogEnd(300.0f);
				fog->SetFogColor(DirectX::Colors::MediumSeaGreen);
			}

			auto light = dynamic_cast<DirectX::IEffectLights*>(effect);

			if (light)
			{
				light->SetAmbientLightColor(DirectX::SimpleMath::Vector3::Zero);
				light->SetLightEnabled(0, false);
				light->SetLightEnabled(1, false);
				light->SetLightEnabled(2, false);
			}

			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect)
			{
				basicEffect->SetEmissiveColor(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
			}
			*/

			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(true);
				basicEffect->SetPerPixelLighting(true);
				basicEffect->SetTextureEnabled(true);
				basicEffect->SetVertexColorEnabled(false);
			}

		});

	//		背景の情報を生成する
	m_information = std::make_unique<BackGroundObjectInformation>();

	m_information->Create(mesh, wirePosition);

	// ピクセルシェーダーの作成（トーラス用）
	std::vector<uint8_t> ps_torus =
		DX::ReadData(L"Resources/Shader/BillShader/BillShaderPS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps_torus.data(), ps_torus.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	UNREFERENCED_PARAMETER(m_constBuffer);

	ConstBuffer buffer = {};

	//		シェーダにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(buffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreateBuffer(&bd, nullptr, &m_buffer);

	m_constBuffer.fogLength = {100.0f, 300.0f, 0.0f,0.0f};
	m_constBuffer.fogColor = DirectX::Colors::MediumSeaGreen;
}

void BackGroundObject::Update()
{
}

void BackGroundObject::Render(DirectX::SimpleMath::Vector3 cameraVelocity,
	DirectX::SimpleMath::Vector3 cameraPosition)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	for (int i = 0, max = static_cast<int>(m_information->GetObjectPosition().size()); i < max; ++i)
	{
		//		カリングの処理
		if (!Culling(i, cameraVelocity, cameraPosition)) continue;

		//		回転処理
		DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::
			CreateFromQuaternion(m_information->GetObjectQuaternion()[i]);

		//		座標
		world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_information->GetObjectPosition()[i]);

		//		モデルの描画
		m_floorModel->Draw(context,
			*LibrarySingleton::GetInstance()->GetCommonState(),
			world, LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj(), false, [&]() {

				m_constBuffer.cameraPosition = { cameraPosition.x, cameraPosition.y, cameraPosition.z, 0.0f };

				//		受け渡し用バッファ
				context->UpdateSubresource(m_buffer.Get(), 0, NULL, &m_constBuffer, 0, 0);

				//		定数バッファの設定
				ID3D11Buffer* cbuff[] = { m_buffer.Get()};

				context->PSSetConstantBuffers(0, 1, cbuff);

				context->PSSetShader(m_pixselShader.Get(), nullptr, 0);
			});
	}
}

void BackGroundObject::Finalize()
{
}

bool BackGroundObject::Culling(int index,
	DirectX::SimpleMath::Vector3 cameraVelocity,
	DirectX::SimpleMath::Vector3 cameraPosition)
{
	if ((DirectX::SimpleMath::Vector3(m_information->GetObjectPosition()[index].x,
		0.0f, m_information->GetObjectPosition()[index].z) -
		DirectX::SimpleMath::Vector3(cameraPosition.x, 0.0f, cameraPosition.z)).Length() > 400.0f)
	{
		return false;
	}

	//		カメラからのオブジェクトの距離
	DirectX::SimpleMath::Vector3 objectVelocityUnder =
		m_information->GetObjectPosition()[index] - cameraPosition;

	//		正規化処理
	objectVelocityUnder.Normalize();

	//		オブジェクトの座標
	DirectX::SimpleMath::Vector3 velocity = m_information->GetObjectPosition()[index];

	//		オブジェクトの上部の座標
	velocity += DirectX::SimpleMath::Vector3::Transform({0.0f, 1.0f, 0.0f},
		m_information->GetObjectQuaternion()[index]) * 400.0f;

	//		カメラからのオブジェクトの距離上部
	DirectX::SimpleMath::Vector3 objectVelocityTop =
		velocity - cameraPosition;

	//		正規化処理
	objectVelocityTop.Normalize();

	//		内積が０より小さい場合処理をしない
	if (cameraVelocity.Dot(objectVelocityUnder) < 0.0f &&
		cameraVelocity.Dot(objectVelocityTop) < 0.0f)
	{
		return false;
	}

	return true;
}
