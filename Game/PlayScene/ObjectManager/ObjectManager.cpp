/*
* @file		ObjectManager.cpp
* @brief	�I�u�W�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{
	//		���̐���
	m_floorObject = std::make_unique<FloorObject>();

	//		���̏���������
	m_floorObject->Initialize();

	//		���C���[�I�u�W�F�N�g�̐���
	m_wireObject = std::make_unique<WireObject>();

	//		���C���[�I�u�W�F�N�g�̏�����
	m_wireObject->Initialize();

	//		�ǃI�u�W�F�N�g�̐���
	m_wallObject = std::make_unique<WallObject>();

	//		�ǃI�u�W�F�N�g�̏�����
	m_wallObject->Initialize();

	//		�I�u�W�F�N�g���b�V����ǉ�����
	m_objectMesh.push_back(m_floorObject->GetObjectMesh());

	m_objectMesh.push_back(m_wallObject->GetObjectMesh());

	//		���b�V���̕`��𐶐�����
	m_drawMesh = std::make_unique<DrawMesh>();
}

void ObjectManager::Update(const DirectX::SimpleMath::Vector3& playerPosition)
{
	m_wirePosition.clear();

	m_wireObject->Update(playerPosition);

	if (m_wireObject->GetWireAvailableJudgement())
	{
		m_wirePosition.push_back(m_wireObject->GetPosition());
	}
}

void ObjectManager::Render()
{
	//		���̕`�揈��
	m_floorObject->Render(m_drawMesh.get());

	//		�ǂ̕`��
	m_wallObject->Render(m_drawMesh.get());

	//		���C���[�I�u�W�F�N�g�̏���
	m_wireObject->Render(m_drawMesh.get());
}

void ObjectManager::Finalize()
{
}
