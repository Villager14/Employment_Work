/*
* @file		FloorObject.cpp
* @brief	床オブジェクトの描画
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "FloorObject.h"

#include <Effects.h>

FloorObject::FloorObject(ShadowInformation* shadowInformation)
	:
	m_floorModel{},
	m_shadowInformation(shadowInformation)
{
}

FloorObject::~FloorObject()
{

}

void FloorObject::Initialize()
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
					::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Floor.cmo", *m_effect);

	//		オブジェクトメッシュの生成
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		初期化処理
	m_objectMesh->Initialize(L"Resources/ModelMesh/Floor.obj");

	m_world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		静的オブジェクトにする
	m_objectMesh->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0)), {0.0f, 0.0f, 0.0f});

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);

	//		オブジェクトのタイプを設定（床）
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Floor);

}

void FloorObject::Update()
{
}

void FloorObject::Render(DrawMesh* drawMesh)
{
	//		モデルの描画
	//m_floorModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
	//	*LibrarySingleton::GetInstance()->GetCommonState(),
	//	m_world, LibrarySingleton::GetInstance()->GetView(),
	//	LibrarySingleton::GetInstance()->GetProj());

	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

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

	//		メッシュの描画
	//drawMesh->StaticRender(m_objectMesh.get());
}

void FloorObject::Finalize()
{
}
