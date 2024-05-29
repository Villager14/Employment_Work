/*
* @file		MeshCollitionManaager.cpp
* @brief	���b�V���̓����蔻��}�l�[�W���[
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "MeshCollitionManager.h"

MeshCollitionManager::MeshCollitionManager()
{
}

MeshCollitionManager::~MeshCollitionManager()
{
}

void MeshCollitionManager::Initialize()
{
	//		���b�V�����̓����蔻��̐���
	m_meshCollitionFloor = std::make_unique<MeshCollitionFloor>(this);

	//		���b�V���̕ǂ̓����蔻��
	m_meshCollitionWall = std::make_unique<MeshCollitionWall>(this);
}

void MeshCollitionManager::MeshCollition(ObjectMesh* objectMesh,
			const DirectX::SimpleMath::Vector3& playerPosition,
			float height, bool slidingJudgement,
			GameManager* gameManager)
{
	//		�X���C�f�B���O��Ԃ��ǂ���
	if (slidingJudgement)
	{
		playerUnderRayLength = 1.0f;
	}
	else
	{
		playerUnderRayLength = 0.5f;
	}

	//		���C�̒�����ݒ肷��
	m_meshCollitionFloor->SetRayLength(playerUnderRayLength, PLAYER_ABOVE_RAY_LENGTH);

	//		�ǂ̓����蔻��
	m_wallHit = m_meshCollitionWall->WallCollition(objectMesh, playerPosition, height);

	//		�I�u�W�F�N�g�^�C�v���ǂ̎�
	if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::Wall)
	{
		//		�ǂɓ��������@��
		m_wallHitNormalize = m_meshCollitionWall->GetNormalize();
	}

	m_wallWalkPlayerPosition = m_meshCollitionWall->WallWalk(objectMesh, playerPosition);

	if (m_wallHit.size() == 0)
	{
		m_playerPosition = playerPosition;
	}
	else
	{
		m_playerPosition = { m_wallHit[0].x, playerPosition.y, m_wallHit[0].y };
	}

	//		���̓����蔻����X�V����
	m_meshHitPoint = m_meshCollitionFloor->FloorCollition(objectMesh, m_playerPosition);

	if (m_meshHitPoint.size() != 0)
	{
		//		�S�[���ɓ������Ă���ꍇ
		if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::Goal)
		{
			//		�S�[����ݒ肷��
			gameManager->SetGoalJudgement(true);
		}
	}
}

bool MeshCollitionManager::CollitionCC(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
									   const DirectX::SimpleMath::Vector3& playerPos,
									   const float& playerLength)
{
	//		���b�V���̍ő�̕ӂ̒��������߂�
	float meshLength = std::max((vertex[0] - vertex[1]).Length(),
		std::max((vertex[0] - vertex[2]).Length(),
			(vertex[1] - vertex[2]).Length()));

	//		���b�V���̒��S�_�����߂�
	DirectX::SimpleMath::Vector3 m_centerPoint = (vertex[0] + vertex[1] + vertex[2]) / 3.0f;

	//		�v���C���[�ƃ��b�V���̒��S�̍��W�����b�V���̒����ƃv���C���[�̃��C�̒�����菬������
	if ((m_centerPoint - playerPos).Length() <= meshLength + playerLength)
	{
		//		�������Ă���
		return true;
	}

	//		�������Ă��Ȃ�
	return false;
}

bool MeshCollitionManager::OnTheSamePlane(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& rayStart, const DirectX::SimpleMath::Vector3& rayEnd,
	const DirectX::SimpleMath::Vector3& normalize, DirectX::SimpleMath::Vector3* hitPoint)
{
	//		�O�p�`�̒��S�����߂�
	DirectX::SimpleMath::Vector3 center =
		(vertex[0] + vertex[1] + vertex[2]) / 3;

	//		���C�̕����Ɍ����Ă���x�N�g�����o��
	DirectX::SimpleMath::Vector3 velocityS = rayStart - center;
	DirectX::SimpleMath::Vector3 velocityE = rayEnd - center;

	//		���ς����
	float dotS = normalize.Dot(velocityS);
	float dotE = normalize.Dot(velocityE);

	//		�l���O�ȏ�̏ꍇ���������Ȃ�
	if (dotS * dotE <= 0)
	{
		//		���ʏ�̓_�����߂�
		float m = abs(dotS);
		float n = abs(dotE);

		//		�������Ă���|�C���g
		*hitPoint = (rayStart * n + rayEnd * m) / (m + n);

		//		�܂܂�Ă���
		return true;
	}

	//		�܂܂�Ă��Ȃ�
	return false;

}

bool MeshCollitionManager::InsideTriangle(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& normalize, const DirectX::SimpleMath::Vector3& hitPoint)
{
	for (int i = 0; i < 3; ++i)
	{
		//		�����������W�Ɍ������x�N�g��
		DirectX::SimpleMath::Vector3 hitVelocity = hitPoint - vertex[i];

		//		�ʂ̒��_�Ɍ������x�N�g��
		DirectX::SimpleMath::Vector3 meshVelocity = vertex[(i + 2) % 3] - vertex[i];

		//		�O�ς����߂�
		DirectX::SimpleMath::Vector3 cross = hitVelocity.Cross(meshVelocity);

		//		���K��
		cross.Normalize();

		//		�@���ƊO�ς̓��ς����
		float d = normalize.Dot(cross);

		//		0�ȉ��̏ꍇ�O�p�`�̊O���ɂ���
		if (d < 0)
		{
			//		�O��
			return false;
		}
	}

	//		����
	return true;
}


void MeshCollitionManager::MeshHitPointClear()
{
	m_meshHitPoint.clear();
	//		�ǂ̓����蔻���
	m_wallHit.clear();

}

