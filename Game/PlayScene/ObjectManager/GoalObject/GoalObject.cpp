/*
* @file		GoalObject.cpp
* @brief	ゴールオブジェクトの描画
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "GoalObject.h"

#include <Effects.h>

#include "Common/ReaData.h"

#include <WICTextureLoader.h>

GoalObject::GoalObject(ObjectManager* objectManager)
	:
	m_floorModel{},
	m_rotation(0.0f),
	m_objectManager(objectManager)
{
	//		オブジェクトメッシュの生成
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

GoalObject::~GoalObject()
{

}

void GoalObject::Initialize(ObjectInformation information)
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_floorModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Goal.cmo", *m_effect);


	m_position = information.position;

	m_rotation = information.rotation;

	//		初期化処理
	m_objectMesh->Initialize(L"Resources/ModelMesh/Goal.obj");

	m_world = DirectX::SimpleMath::Matrix::CreateScale(1.0f);

	//		静的オブジェクトにする
	m_objectMesh->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y)), m_position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		オブジェクトのタイプを設定（床）
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Goal);

	//		通常描画をするようにする
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);
}

void GoalObject::Update()
{
	m_rotation.z += LibrarySingleton::GetInstance()->GetElpsedTime() * 10.0f;
}

void GoalObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	UNREFERENCED_PARAMETER(postEffectObjectShader);
	UNREFERENCED_PARAMETER(flag);

	m_world = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rotation.z));

	m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y));

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	for (const auto& it : m_floorModel->meshes)
	{
		auto mesh = it.get();

		mesh->PrepareForRendering(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
			*LibrarySingleton::GetInstance()->GetCommonState(), true);

		mesh->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()
			->GetD3DDeviceContext(),
			m_world, LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj());
	}

	//drawMesh->StaticRender(m_objectMesh.get());
}

void GoalObject::Finalize()
{
	m_floorModel.release();
}
