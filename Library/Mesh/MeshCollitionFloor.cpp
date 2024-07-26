/*
* @file		MeshCollitionFloor.cpp
* @brief	���b�V���̓����蔻�菰
* @author	Morita
* @date		2024/04/27
*/

#include "pch.h"

#include "MeshCollitionFloor.h"

#include "MeshCollitionManager.h"

MeshCollitionFloor::MeshCollitionFloor(MeshCollitionManager* meshCollitionManager)
	:
	m_meshCollitionManager(meshCollitionManager),
	m_rayAboveLength(0.0f),
	m_rayUnderLength(0.0f),
	m_minLengthMP(0.0f)
{
}

MeshCollitionFloor::~MeshCollitionFloor()
{
}

const std::vector<DirectX::SimpleMath::Vector3>& MeshCollitionFloor::FloorCollition(
	ObjectMesh* objectMesh, const DirectX::SimpleMath::Vector3& playerPosition)
{
	FloorCollitionInitalize(playerPosition);

	//		���_
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	{
		//		�����ǂ������f����
		if (!FloorJudgement(objectMesh->GetNormalizePosition(i))) continue;

		//		���_�̍��W���󂯎��
		vertex[0] = objectMesh->GetVertexPosition(i, 0);
		vertex[1] = objectMesh->GetVertexPosition(i, 1);
		vertex[2] = objectMesh->GetVertexPosition(i, 2);

		//		�~�̓����蔻�肪�������Ă��Ȃ��ꍇ����ȏ㏈�������Ȃ�
		if (!m_meshCollitionManager->CollitionCC(vertex, m_rayStart, 2.0f))continue;

		//		���ꕽ�ʏ�ɂ��邩�ǂ���
		if (!m_meshCollitionManager->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			objectMesh->GetNormalizePosition(i), &m_hitPoint))
		{
			//		�ђʎ��̏���

			//		�ߋ��̍��W�����C�̊J�n�ʒu�ɂ���
			m_rayStart = m_pastPosition;

			//		��Ƀ��C���グ��
			m_rayStart.y += m_rayAboveLength;

			//		���ꕽ�ʏ�ɂ��邩�ǂ���
			if (!m_meshCollitionManager->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
				objectMesh->GetNormalizePosition(i), &m_hitPoint))
			{
				continue;
			}
		}

		//		���b�V���̎O�p�`�̓������ǂ���
		if (m_meshCollitionManager->InsideTriangle(vertex,
			objectMesh->GetNormalizePosition(i),
			m_hitPoint))
		{
			//		�������Ă��镔����ǉ�����
			m_hitMeshPoint.push_back(m_hitPoint);
			//		�@����ǉ�
			m_normalize.push_back(objectMesh->GetNormalizePosition(i));
		}
	}

	//		���b�V���ɓ������Ă��邩
	if (DistancePlayer()) return m_hitMeshPoint;

	//		�v���C���[�̑��������蔻��
	//PlayerFootRadian(objectMesh, playerPosition);

	return m_hitMeshPoint;
}

void MeshCollitionFloor::PlayerFootRadian(ObjectMesh* objectMesh)
{
	//		���_
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	{
		//		�����ǂ������f����
		if (!FloorJudgement(objectMesh->GetNormalizePosition(i))) continue;

		//		���_�̍��W���󂯎��
		vertex[0] = objectMesh->GetVertexPosition(i, 0);
		vertex[1] = objectMesh->GetVertexPosition(i, 1);
		vertex[2] = objectMesh->GetVertexPosition(i, 2);

		CreateFootRay(vertex);

		//		�~�̓����蔻�肪�������Ă��Ȃ��ꍇ����ȏ㏈�������Ȃ�
		if (!m_meshCollitionManager->CollitionCC(vertex, m_playerPosition, 2.0f))continue;

		//		���ꕽ�ʏ�ɂ��邩�ǂ���
		if (!m_meshCollitionManager->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			objectMesh->GetNormalizePosition(i), &m_hitPoint)) continue;

		//		���b�V���̎O�p�`�̓������ǂ���
		if (m_meshCollitionManager->InsideTriangle(vertex,
			objectMesh->GetNormalizePosition(i),
			m_hitPoint))
		{
			//		�������Ă��镔����ǉ�����
			m_hitMeshPoint.push_back(m_hitPoint);

			//		�v���C���[�ƃ��b�V���̍ŒZ���������߂�
			MinLengthMP();
		}
	}
}

bool MeshCollitionFloor::FloorJudgement(const DirectX::SimpleMath::Vector3& normalize)
{
	//		������̖@���ƃ��b�V���̖@���œ��ς����
	float dot = DirectX::SimpleMath::Vector3(0, 1, 0).Dot(normalize);

	//		�@���̕�������������Ă��Ȃ��ꍇ(45�x�܂�)
	if (dot < 0.5f)
	{
		//		���ł͂Ȃ�
		return false;
	}

	return true;
}

bool MeshCollitionFloor::DistancePlayer()
{
	//		�����������W�̐����O�ȉ��̎�
	if (m_hitMeshPoint.size() <= 0)
	{

		return false;
	}
	//		�ł��v���C���[����߂����W
	DirectX::SimpleMath::Vector3 position = m_hitMeshPoint[0];

	//		�ł��v���C���[����߂����W�ƃv���C���[�Ƃ̋���
	float length = (m_hitMeshPoint[0] - m_playerPosition).Length();

	//		�@��
	DirectX::SimpleMath::Vector3 normalize = m_normalize[0];

	//		�ł��v���C���[����߂����W���v�Z����
	for (int i = 0, max = static_cast<int>(m_hitMeshPoint.size()); i < max; ++i)
	{
		//		�����z��̗v�f�����傫�������ɂȂ����ꍇ
		if (i + 1 >= static_cast<int>(m_hitMeshPoint.size()))
		{
			break;
		}

		//		�������݂̍ŒZ���W���Z�������ꍇ
		if (length <= (m_hitMeshPoint[i + 1] - m_playerPosition).Length())
		{
			//		�ŒZ���W���X�V����
			length = (m_hitMeshPoint[i + 1] - m_playerPosition).Length();

			//		�ŒZ���W��������
			position = m_hitMeshPoint[i + 1];

			//		�@����������
			normalize = m_normalize[i + 1];
		}
	}

	//		���������|�C���g�̊J��
	m_hitMeshPoint.clear();

	//		�@���̊J��
	m_normalize.clear();

	//		�ŒZ���W��������
	m_hitMeshPoint.push_back(position);

	//		�@����������
	m_normalize.push_back(normalize);

	return true;
}

void MeshCollitionFloor::CreateFootRay(std::vector<DirectX::SimpleMath::Vector3> vertex)
{
	//		���b�V���̒��S
	DirectX::SimpleMath::Vector3 center =
		(vertex[0] + vertex[1] + vertex[2]) / 3.0f;

	//		���S�֌������x�N�g��
	DirectX::SimpleMath::Vector3 velocity = center - m_playerPosition;

	velocity.Normalize();

	velocity *= 2.0f;

	//		���C�̍��W�P
	m_rayStart = velocity + m_playerPosition;

	//		���C�̍��W�Q
	m_rayEnd = m_rayStart;

	//		���C�̒������グ��
	m_rayStart.y += m_rayAboveLength;

	//		���C�̒�����������
	m_rayEnd.y -= m_rayUnderLength;
}

void MeshCollitionFloor::FloorCollitionInitalize(const DirectX::SimpleMath::Vector3& playerPosition)
{
	//		���
	m_hitMeshPoint.clear();

	//		���
	m_normalize.clear();

	m_hitPoint = DirectX::SimpleMath::Vector3::Zero;

	//		�v���C���[�̍��W��ݒ肷��
	m_playerPosition = playerPosition;

	//		���C�̍��W�P
	m_rayStart = playerPosition;

	//		���C�̍��W�Q
	m_rayEnd = m_rayStart;

	//		���C�̒������グ��
	m_rayStart.y += m_rayAboveLength;

	//		���C�̒�����������
	m_rayEnd.y -= m_rayUnderLength;
}

void MeshCollitionFloor::MinLengthMP()
{
	//		���C�̍��W���o��
	DirectX::SimpleMath::Vector3 rayPosition = m_rayStart;

	//		���C�̌��_�ɖ߂�
	rayPosition.y -= m_rayAboveLength;

	//		���b�V���̐�����̎�
	if (m_hitMeshPoint.size() == 1)
	{
		//		���b�V���̒�����ۑ�����
		m_minLengthMP = (m_hitMeshPoint[0] - m_playerPosition).Length();

		//		�ŒZ���W��������
		m_hitMeshPoint.push_back(m_hitMeshPoint[0]);

		return;
	}

	DirectX::SimpleMath::Vector3 position;

	//		�������݂̍ŒZ���W���Z�������ꍇ
	if (m_minLengthMP >= (m_hitMeshPoint[1] - rayPosition).Length())
	{
		//		�ŒZ���W���X�V����
		m_minLengthMP = (m_hitMeshPoint[1] - m_playerPosition).Length();

		//		�ŒZ���W��������
		position = m_hitMeshPoint[1];
	}

	//		���b�V���̍폜
	m_hitMeshPoint.clear();

	//		�ŒZ���W��������
	m_hitMeshPoint.push_back(position);
}
