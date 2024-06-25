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

	m_wireObjectPosition.push_back({ 0.0f, 70.0f, 297.0f });
	m_wireObjectPosition.push_back({ -730.0f, 70.0f, 360.0f });
	m_wireObjectPosition.push_back({ -900.0f, 100.0f, 300.0f });
	m_wireObjectPosition.push_back({ -1050.0f, 130.0f, 330.0f });

	for (int i = 0; i < m_wireObjectPosition.size(); ++i)
	{
		//		���C���[�I�u�W�F�N�g�̐���
		m_wireObject.push_back(std::make_unique<WireObject>());

		//		���C���[�I�u�W�F�N�g�̏�����
		m_wireObject[i]->Initialize(m_wireObjectPosition[i]);
	}

	//		�ǃI�u�W�F�N�g�̐���
	m_wallObject = std::make_unique<WallObject>();

	//		�ǃI�u�W�F�N�g�̏�����
	m_wallObject->Initialize();

	//		�S�[���I�u�W�F�N�g�̐���
	m_goalObject = std::make_unique<GoalObject>();

	//		�S�[���I�u�W�F�N�g�̏���������
	m_goalObject->Initialize();

	//		�I�u�W�F�N�g���b�V����ǉ�����
	m_objectMesh.push_back(m_floorObject->GetObjectMesh());
	m_objectMesh.push_back(m_wallObject->GetObjectMesh());
	m_objectMesh.push_back(m_goalObject->GetObjectMesh());

	//		�w�i�I�u�W�F�N�g�̐���
	m_backGroundObject = std::make_unique<BackGroundObject>();

	//		�w�i�I�u�W�F�N�g�̏�����
	m_backGroundObject->Initialize(m_objectMesh, m_wireObjectPosition);

	//		���b�V���̕`��𐶐�����
	m_drawMesh = std::make_unique<DrawMesh>();
}

void ObjectManager::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_wirePosition.clear();

	for (int i = 0; i < m_wireObject.size(); ++i)
	{
		//		�J�����O���邩�ǂ���
		if (!Culling(m_wireObject[i]->GetPosition()))
		{
			m_wireObject[i]->Update(playerPosition);

			if (m_wireObject[i]->GetWireAvailableJudgement())
			{
				m_wirePosition.push_back(m_wireObject[i]->GetPosition());
			}
		}
	}

	//m_backGroundObject->Update();
}

void ObjectManager::Render(DirectX::SimpleMath::Vector3 cameraVelocity,
	DirectX::SimpleMath::Vector3 cameraPosition)
{
	m_cameraVelocity = cameraVelocity;
	m_cameraPosition = cameraPosition;

	m_backGroundObject->Render(cameraVelocity, cameraPosition);

	//		���̕`�揈��
	m_floorObject->Render(m_drawMesh.get());

	//		�ǂ̕`��
	m_wallObject->Render(m_drawMesh.get());

	for (const auto& e : m_wireObject)
	{
		//		�J�����O���邩�ǂ���
		if (!Culling(e->GetPosition()))
		{
			//		���C���[�I�u�W�F�N�g�̏���
			e->Render();
		}
	}

	m_goalObject->Render(m_drawMesh.get());
}

void ObjectManager::Finalize()
{
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
