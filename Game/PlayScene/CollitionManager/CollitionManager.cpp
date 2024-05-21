/*
* @file		CollitionManager.cpp
* @brief	�����蔻��}�l�[�W���[
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "CollitionManager.h"

CollitionManager::CollitionManager()
{
}

CollitionManager::~CollitionManager()
{
}

void CollitionManager::Initialize()
{
	//		���b�V���̓����蔻��̐���
	m_meshCollition = std::make_unique<MeshCollitionManager>();

	//		������������
	m_meshCollition->Initialize();

	//		�e�̓����蔻��̐���
	m_bulletCollition = std::make_unique<BulletCollition>();

	//		�����蔻��̏��
	m_collitionInformation = std::make_unique<CollitionInformation>();
}

void CollitionManager::Update(PlayerInformationCollition* playerInformationCollition)
{
	//		�����蔻��̏�����
	m_meshCollition->MeshHitPointClear();

	//		�@���𑗂�
	m_meshCollition->SetWallWalkNormalize(playerInformationCollition->GetWallWalkNormalize());

	//		�v���C���[�̍��������߂�
	float height = playerInformationCollition->GetPlayerHeight().y - playerInformationCollition->GetPlayerPosition().y;

	//		�v���C���[�̍��W���󂯎��
	m_playerPosition = playerInformationCollition->GetPlayerPosition();

	//		�ˑR�̓����蔻����폜����
	m_collitionInformation->Clear();


	//		�ÓI�ȓ����蔻��
	for (int i = 0; i < m_objectMesh.size(); ++i)
	{
		if (m_objectMesh[i]->GetStaticObjectJudgement())
		{
			//		���b�V���̓����蔻��
			m_meshCollition->MeshCollition(m_objectMesh[i], m_playerPosition, height, 
								playerInformationCollition->GetSlidingJudgement());

			//		���̓����蔻��̏���ݒ肷��
			m_collitionInformation->FloorMeshInformation(m_meshCollition->GetMeshHitPoint(),
				m_meshCollition->GetFloorNormalize(), m_playerPosition);

			//		�ǂ̓����蔻�����ݒ肷��
			m_playerPosition = m_collitionInformation->WallMeshInformation(
					m_meshCollition->GetMeshWallHit(),
					m_meshCollition->GetWallHitNormalize(),
					m_meshCollition->GetWallWalkPlayerPosition(),
					m_playerPosition);
		}
	}

	//		�e�̓����蔻��
	m_bulletCollition->Collition(playerInformationCollition->GetPlayerPosition(), playerInformationCollition->GetPlayerHeight(), m_bulletPosition);
}
