/*
* @file		FloorObject.cpp
* @brief	床オブジェクトの描画
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "WallObject.h"

#include <Effects.h>

WallObject::WallObject(ObjectManager* objectManager)
	:
	m_floorModel{},
	m_objectManager(objectManager)
{
	//		オブジェクトメッシュの生成
	m_objectMesh = std::make_unique<ObjectMesh>();
}

WallObject::~WallObject()
{

}

void WallObject::Initialize(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation)
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/WallObject01.cmo", *m_effect);

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


	//		初期化処理
	m_objectMesh->Initialize(L"Resources/ModelMesh/WallObject01.obj");

	m_world = DirectX::SimpleMath::Matrix::CreateRotationY(rotation.y);

	m_move = position;

	//		静的オブジェクトにする
	m_objectMesh->StaticProcess(m_world, m_move);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_move);

	//		オブジェクトタイプの設定（壁）
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Wall);
}

void WallObject::Update()
{
}

void WallObject::Render()
{
	//		モデルの描画
	m_floorModel->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());

	//		メッシュの描画
	//drawMesh->StaticRender(m_objectMesh.get());
}

void WallObject::Finalize()
{
	m_floorModel.release();
}
