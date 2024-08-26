/*
* @file		FloorObject.cpp
* @brief	床オブジェクトの描画
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "FloorObject.h"

#include <Effects.h>

#include "Common/ReaData.h"

#include <WICTextureLoader.h>

FloorObject::FloorObject(ObjectManager* objectManager)
	:
	m_floorModel{},
	m_objectManager(objectManager)
{
	//		オブジェクトメッシュの生成
	m_objectMesh = std::make_unique<ObjectMesh>();


}

FloorObject::~FloorObject()
{

}

void FloorObject::Initialize(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation)
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Floor.cmo", *m_effect);

	m_floorModel->UpdateEffects([](DirectX::IEffect* effect)
		{
			auto fog = dynamic_cast<DirectX::IEffectFog*>(effect);

			if (fog)
			{
				fog->SetFogEnabled(true);
				fog->SetFogStart(200.0f);
				fog->SetFogEnd(350.0f);
				fog->SetFogColor(DirectX::Colors::MediumSeaGreen);
			}
		});

	/*
	m_floorModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(false);
				basicEffect->SetPerPixelLighting(false);
				basicEffect->SetTextureEnabled(false);
				basicEffect->SetVertexColorEnabled(false);
				basicEffect->SetFogEnabled(false);
			}

		});

	// ピクセルシェーダーの作成（トーラス用）
	std::vector<uint8_t> ps_torus = DX::ReadData(L"Resources/Shader/Model/ModelPS.cso");
	DX::ThrowIfFailed(
		LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice()->CreatePixelShader(ps_torus.data(),
		ps_torus.size(), nullptr, m_floorPS.ReleaseAndGetAddressOf())
	);

	// テクスチャのロード
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Textures/floor.png",
		nullptr,
		m_texture.GetAddressOf()
	);
	*/


	//		初期化処理
	m_objectMesh->Initialize(L"Resources/ModelMesh/Floor.obj");

	m_world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		静的オブジェクトにする
	m_objectMesh->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(rotation.x)), position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(position);

	//		オブジェクトのタイプを設定（床）
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Floor);
}

void FloorObject::Update()
{
}

void FloorObject::Render()
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	/*
	m_floorModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&] {

			////		定数バッファの設定
			//ID3D11Buffer* cbuff[] = { m_shadowInformation->GetConstBufferShadow().Get(),
			//						m_shadowInformation->GetConstBufferDepth().Get()};

			//
			//context->VSSetConstantBuffers(1, 1, cbuff);
			//context->PSSetConstantBuffers(1, 2, cbuff);
			//
			////		シェーダーリソースビューを受け取る
			//auto srv = m_shadowInformation->GetRenderTexture()->GetShaderResourceView();

			////		作成したシャドウマップをリソースとして設定する
			//context->PSSetShaderResources(1, 1, &srv);

			////		テクスチャサンプラーの設定
			//ID3D11SamplerState* samplers[] = 
			//{ LibrarySingleton::GetInstance()->GetCommonState()->PointWrap(),
			//m_shadowInformation->GetShadowMapSampler().Get() };
			//context->PSSetSamplers(0, 2, samplers);

			////		シェーダーの設定
			//context->VSSetShader(m_shadowInformation->GetShadowVS().Get(), nullptr, 0);
			//context->PSSetShader(m_shadowInformation->GetShadowPS().Get(), nullptr, 0);

		});
		*/

	m_floorModel->Draw(context,
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&] {

			//ID3D11SamplerState* samplers[] = {LibrarySingleton::GetInstance()->GetCommonState()->PointWrap()};

			//context->PSSetSamplers(0, 1, samplers);

			//ID3D11SamplerState* samplesrs[1] = { common->PointWrap() };
			//context->PSSetSamplers(0, 1, samplesrs);

			//// オリジナルピクセルシェーダーの設定
			//context->PSSetShader(m_floorPS.Get(), nullptr, 0);

		});


	//		メッシュの描画
	//drawMesh->StaticRender(m_objectMesh.get());
}

void FloorObject::Finalize()
{
	m_floorModel.release();
}
