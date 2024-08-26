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
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{
	m_wireObjectPosition.push_back({ 0.0f, 70.0f, 297.0f });

	for (int i = 0; i < m_wireObjectPosition.size(); ++i)
	{
		//		���C���[�I�u�W�F�N�g�̐���
		m_wireObject.push_back(std::make_unique<WireObject>());

		//		���C���[�I�u�W�F�N�g�̏�����
		m_wireObject[i]->Initialize(m_wireObjectPosition[i], i);

		//		���C���[�̏���ݒ肷��
		m_wireInformation.push_back(m_wireObject[i]->GetWireInformation());
	}

	//		�O���C���_�[�I�u�W�F�N�g
	m_factoryObject.push_back(m_factory->CreateObject(Factory::Grider, { -383.0f, 30.0f, 349.0f }, {0.0f, 0.0f, 0.0f}));
	//		�ǃI�u�W�F�N�g
	m_factoryObject.push_back(m_factory->CreateObject(Factory::Wall, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));
	//		���I�u�W�F�N�g
	m_factoryObject.push_back(m_factory->CreateObject(Factory::Floor, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));
	//		�S�[���I�u�W�F�N�g
	m_factoryObject.push_back(m_factory->CreateObject(Factory::Goal, { -580.0f, 17.0f, 350.0f }, { 0.0f, 90.0f, 0.0f }));

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
	for (int i = 0; i < m_wireObject.size(); ++i)
	{
		//		�J�����O���邩�ǂ���
		if (!Culling(m_wireObject[i]->GetPosition()))
		{
			//		���C���[�I�u�W�F�N�g�̍X�V����
			m_wireObject[i]->Update(playerPosition);
		}
	}

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

	for (const auto& e : m_wireObject)
	{
		//		�J�����O���邩�ǂ���
		if (!Culling(e->GetPosition()))
		{
			//		���C���[�I�u�W�F�N�g�̏���
			e->Render();
		}
	}
}

void ObjectManager::Finalize()
{
	m_objectMesh.clear();

	m_wireObject.clear();

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
