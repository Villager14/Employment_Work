/*
* @file		GriderObject.h
* @brief	破砕オブジェクトの描画
* @author	Morita
* @date		2024/08/09
*/

#include "pch.h"

#include "GriderObject.h"

#include <Effects.h>

#include "Common/ReaData.h"

#include <WICTextureLoader.h>

GriderObject::GriderObject(ObjectManager* objectManager)
	:
	m_rog(0.0f),
	m_objectManager(objectManager),
	m_shadowInformation()
{
	//		オブジェクトメッシュの生成
	//m_objectMesh = ;
	m_objectMesh.push_back(std::make_unique<ObjectMesh>());
	m_objectMesh.push_back(std::make_unique<ObjectMesh>());

	//		オブジェクトメッシュの生成
	//m_damageObjectMesh = std::make_unique<ObjectMesh>();
}

GriderObject::~GriderObject()
{
}

void GriderObject::Initialize(DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Vector3 rotation)
{
	m_position = position;

	m_rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll
	(rotation);

	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_griderRotationObject = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/GrinderRotation.cmo", *m_effect);

	//		モデルの読み込み
	m_griderObject = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Grinder.cmo", *m_effect);


	m_griderRotationObject->UpdateEffects([](DirectX::IEffect* effect)
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

	m_griderObject->UpdateEffects([](DirectX::IEffect* effect)
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

	CreateObjectMesh();
}

void GriderObject::Update()
{
	
	m_rog -= 10.0f * m_objectManager->GetGameManager()->GetGameSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_rotation = DirectX::SimpleMath::Quaternion
		::CreateFromYawPitchRoll(0.0f, 0.0f, m_rog);
}

void GriderObject::Render()
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	m_griderObject->Draw(context,
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());
	
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	world = DirectX::SimpleMath::Matrix::CreateScale(1.0f);

	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);
	
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_griderRotationObject->Draw(context,
		*LibrarySingleton::GetInstance()->GetCommonState(),
		world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());
}

void GriderObject::Finalize()
{
	m_griderRotationObject.release();
	m_griderObject.release();
}

void GriderObject::CreateObjectMesh()
{
	//		初期化処理
	m_objectMesh[0]->Initialize(L"Resources/ModelMesh/Grider.obj");

	m_world = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		静的オブジェクトにする
	m_objectMesh[0]->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0)), m_position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		オブジェクトのタイプを設定（床）
	m_objectMesh[0]->SetObuectType(ObjectMesh::ObjectType::Floor);

	//		初期化処理
	m_objectMesh[1]->Initialize(L"Resources/ModelMesh/GriderRotation.obj");

	m_world = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		静的オブジェクトにする
	m_objectMesh[1]->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0)), m_position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		オブジェクトのタイプを設定（床）
	m_objectMesh[1]->SetObuectType(ObjectMesh::ObjectType::DamageObject);
}
