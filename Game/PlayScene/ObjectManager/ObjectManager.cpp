/*
* @file		ObjectManager.cpp
* @brief	�I�u�W�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "ObjectManager.h"

ObjectManager::ObjectManager(ShadowInformation* shadowInformation)
	:
	m_shadowInformation(shadowInformation)
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{
	//		���̐���
	m_floorObject = std::make_unique<FloorObject>(m_shadowInformation);

	//		���̏���������
	m_floorObject->Initialize();

	for (int i = 0; i < 2; ++i)
	{
		//		���C���[�I�u�W�F�N�g�̐���
		m_wireObject.push_back(std::make_unique<WireObject>());
	}

	//		���C���[�I�u�W�F�N�g�̏�����
	m_wireObject[0]->Initialize({ -100.0f, 70.0f, 467.0f });
	m_wireObject[1]->Initialize({ -200.0f, 100.0f, 850.0f });

	//		�ǃI�u�W�F�N�g�̐���
	m_wallObject = std::make_unique<WallObject>();

	//		�ǃI�u�W�F�N�g�̏�����
	m_wallObject->Initialize();

	//		�S�[���I�u�W�F�N�g�̐���
	m_goalObject = std::make_unique<GoalObject>();

	//		�S�[���I�u�W�F�N�g�̏���������
	m_goalObject->Initialize();

	//		�w�i�I�u�W�F�N�g�̐���
	m_backGroundObject = std::make_unique<BackGroundObject>();

	//		�w�i�I�u�W�F�N�g�̏�����
	m_backGroundObject->Initialize();

	//		�I�u�W�F�N�g���b�V����ǉ�����
	m_objectMesh.push_back(m_floorObject->GetObjectMesh());
	m_objectMesh.push_back(m_wallObject->GetObjectMesh());
	m_objectMesh.push_back(m_goalObject->GetObjectMesh());

	//		���b�V���̕`��𐶐�����
	m_drawMesh = std::make_unique<DrawMesh>();
}

void ObjectManager::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_wirePosition.clear();

	for (int i = 0; i < m_wireObject.size(); ++i)
	{
		m_wireObject[i]->Update(playerPosition);

		if (m_wireObject[i]->GetWireAvailableJudgement())
		{
			m_wirePosition.push_back(m_wireObject[i]->GetPosition());
		}
	}

	//m_backGroundObject->Update();
}

void ObjectManager::Render()
{
	m_backGroundObject->Render();

	//		���̕`�揈��
	m_floorObject->Render(m_drawMesh.get());

	//		�ǂ̕`��
	m_wallObject->Render(m_drawMesh.get());

	for (const auto& e : m_wireObject)
	{
		//		���C���[�I�u�W�F�N�g�̏���
		e->Render(m_drawMesh.get());
	}

	m_goalObject->Render(m_drawMesh.get());
}

void ObjectManager::Finalize()
{
}
