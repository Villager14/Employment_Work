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

#include <SpriteFont.h>

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

void FloorObject::Initialize(ObjectInformation information)
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	std::wostringstream oss;

	oss << Library::StringToWString(information.modelPath);

	//		モデルの読み込み
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		oss.str().c_str(), *m_effect);
	
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

	std::wostringstream oss2;

	oss2 << Library::StringToWString(information.collitionPath);

	//		初期化処理
	m_objectMesh->Initialize(oss2.str().c_str());

	m_world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		静的オブジェクトにする
	m_objectMesh->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(information.rotation.x)), information.position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(information.position);

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
