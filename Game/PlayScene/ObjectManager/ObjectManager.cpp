/*
* @file		ObjectManager.cpp
* @brief	�I�u�W�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "ObjectManager.h"

ObjectManager::ObjectManager(ShadowInformation* shadowInformation, GameManager* gameManager)
	:
	m_shadowInformation(shadowInformation),
	m_gameManager(gameManager)
{
	//		���b�V���̕`��𐶐�����
	m_drawMesh = std::make_unique<DrawMesh>();

	//		�w�i�I�u�W�F�N�g�̐���
	m_backGroundObject = std::make_unique<BackGroundObject>();

	//		�t�@�N�g���[
	m_factory = std::make_unique<Factory>(this);

	//		�I�u�W�F�N�g�̓ǂݍ��݃N���X�̐���
	m_loadObjectInformation = std::make_unique<LoadingObjectInformation>();
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{
	//		�X�e�[�W�̓ǂݍ���
	m_loadObjectInformation->Load(0);

	int wireNumber = 0;

	for (int i = 0, max = static_cast<int>
		(m_loadObjectInformation->GetObjectInformation().size());
		i < max; ++i)
	{
		//		���C���[���I�u�W�F�N�g�̍쐻
		CreateWireInformation(i, &wireNumber);

		m_factoryObject.push_back(m_factory->CreateObject(
			Factory::Object(m_loadObjectInformation->GetObjectInformation()[i].objectType),
			m_loadObjectInformation->GetObjectInformation()[i]));

	}

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		�O���C�_�[�̃��b�V��
		if (m_factoryObject[i]->GetObjectType() == Factory::Grider)
		{
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(0));
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(1));
		}

		//		�ǂ̃��b�V�� �����b�V���@�S�[���I�u�W�F�N�g
		if (m_factoryObject[i]->GetObjectType() == Factory::Wall ||
			m_factoryObject[i]->GetObjectType() == Factory::Goal ||
			m_factoryObject[i]->GetObjectType() == Factory::Floor)
		{
			m_objectMesh.push_back(m_factoryObject[i]->GetObjectMesh(0));
		}
	}

	//		�w�i�I�u�W�F�N�g�̏�����
	m_backGroundObject->Initialize(m_objectMesh, m_wireObjectPosition);
}

void ObjectManager::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_playerPosition = playerPosition;

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		�X�V����
		m_factoryObject[i]->Update();
	}
}

void ObjectManager::Render(DirectX::SimpleMath::Vector3 cameraVelocity,
	DirectX::SimpleMath::Vector3 cameraPosition)
{
	m_cameraVelocity = cameraVelocity;
	m_cameraPosition = cameraPosition;

	m_backGroundObject->Render(cameraVelocity, cameraPosition);

	for (int i = 0; i < m_factoryObject.size(); ++i)
	{
		//		�`�揈��
		m_factoryObject[i]->Render();
	}
}

void ObjectManager::Finalize()
{
	m_objectMesh.clear();

	m_backGroundObject->Finalize();

	m_factoryObject.clear();
}

bool ObjectManager::Culling(DirectX::SimpleMath::Vector3 position)
{
	//		�J�����O�̏���!!!!!
	
	//		������400�ȏ�̏ꍇ�J�����O����
	if ((position - m_cameraPosition).Length() >= 400.0f)
	{
		return true;
	}

	//		�v���C���[�̕������쐬����
	DirectX::SimpleMath::Vector3 objectVelocity =  position - m_cameraPosition;

	//		�@�����O��菬�����ꍇ�J�����O����
	if (m_cameraVelocity.Dot(objectVelocity) < 0.0f)
	{
		return true;
	}

	return false;
}

void ObjectManager::CreateWireInformation(int index, int *wireNumber)
{
	if (Factory::Object(m_loadObjectInformation->GetObjectInformation()[index].objectType)
		== Factory::Object::Wire)
	{
		WireObjectInformation information;

		//		�ԍ�
		information.number = *wireNumber;
		*wireNumber += 1;

		//		���W
		information.position =
			m_loadObjectInformation->GetObjectInformation()[index].position;


		m_wireInformation.push_back(information);
	}
}
