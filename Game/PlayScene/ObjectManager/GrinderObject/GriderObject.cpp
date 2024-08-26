/*
* @file		GriderObject.h
* @brief	�j�ӃI�u�W�F�N�g�̕`��
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
	//		�I�u�W�F�N�g���b�V���̐���
	//m_objectMesh = ;
	m_objectMesh.push_back(std::make_unique<ObjectMesh>());
	m_objectMesh.push_back(std::make_unique<ObjectMesh>());

	//		�I�u�W�F�N�g���b�V���̐���
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

	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_griderRotationObject = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/GrinderRotation.cmo", *m_effect);

	//		���f���̓ǂݍ���
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
	//		����������
	m_objectMesh[0]->Initialize(L"Resources/ModelMesh/Grider.obj");

	m_world = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		�ÓI�I�u�W�F�N�g�ɂ���
	m_objectMesh[0]->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0)), m_position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		�I�u�W�F�N�g�̃^�C�v��ݒ�i���j
	m_objectMesh[0]->SetObuectType(ObjectMesh::ObjectType::Floor);

	//		����������
	m_objectMesh[1]->Initialize(L"Resources/ModelMesh/GriderRotation.obj");

	m_world = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		�ÓI�I�u�W�F�N�g�ɂ���
	m_objectMesh[1]->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0)), m_position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		�I�u�W�F�N�g�̃^�C�v��ݒ�i���j
	m_objectMesh[1]->SetObuectType(ObjectMesh::ObjectType::DamageObject);
}
