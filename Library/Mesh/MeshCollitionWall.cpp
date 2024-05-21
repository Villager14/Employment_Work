/*
* @file		MeshCollitionWall.cpp
* @brief	���b�V���̓����蔻���
* @author	Morita
* @date		2024/04/28
*/

#include "pch.h"

#include "MeshCollitionWall.h"

#include "MeshCollitionManager.h"

MeshCollitionWall::MeshCollitionWall(MeshCollitionManager* meshCollitionManager)
	:
	m_meshCollitionManager(meshCollitionManager)
{
}

MeshCollitionWall::~MeshCollitionWall()
{
}

std::vector<DirectX::SimpleMath::Vector2> MeshCollitionWall::WallCollition(ObjectMesh* objectMesh,
	const DirectX::SimpleMath::Vector3& playerPosition, float height)
{
	m_playerPosition = playerPosition;

	m_normalize.clear();

	bool m_wallHitJudgement = false;

	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	//		�ǂ̓����蔻��
	for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	{
		//		�ǂ��ǂ������f����
		if (!WallJudgement(objectMesh->GetNormalizePosition(i))) continue;

		//		���_�̍��W���󂯎��
		vertex[0] = objectMesh->GetVertexPosition(i, 0);
		vertex[1] = objectMesh->GetVertexPosition(i, 1);
		vertex[2] = objectMesh->GetVertexPosition(i, 2);

		//		�~�̓����蔻��
		if (!m_meshCollitionManager->CollitionCC(vertex, m_playerPosition, height)) continue;

		//		�ǂ̍����̓����蔻��
		if (!WallHeight(vertex, height)) continue;

		
		//		���C�̊J�n�n�_
		m_rayStart = m_playerPosition;

		
		m_rayStart.y = std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y));

		m_rayStart.y += 0.01f;
		
		if (m_rayStart.y > m_playerPosition.y + 7.0f)
		{
			continue;
		}
		
		m_rayEnd = m_rayStart;

		m_rayEnd += -objectMesh->GetNormalizePosition(i) * 2.0f;

		//		���ꕽ�ʏ�ɂ��邩�ǂ���
		if (!m_meshCollitionManager->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			objectMesh->GetNormalizePosition(i), &m_hitPoint)) continue;

		//		���b�V���̎O�p�`�̓������ǂ���
		if (!m_meshCollitionManager->InsideTriangle(vertex,
			objectMesh->GetNormalizePosition(i),
			m_hitPoint)) continue;
		
		//		�X�̒��ɂ���ꍇ�������Ă���
		if (!Extrusion(objectMesh->GetNormalizePosition(i))) continue;

		//		�������Ă���
		m_wallHitJudgement = true;
	}

	m_moveVelocity.clear();

	//		�ǂƓ������Ă���ꍇ
	if (m_wallHitJudgement)
	{
		m_moveVelocity.push_back({ m_playerPosition.x, m_playerPosition.z });
	}

	return m_moveVelocity;
}

bool MeshCollitionWall::WallJudgement(const DirectX::SimpleMath::Vector3& normalize)
{
	//		45�x�ȏ�̖@���͕ǂƂ���
	if (DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).
		Dot(normalize) >= 0.5f)
	{
		//		�ǂł͂Ȃ�
		return false;
	}

	return true;
}

bool MeshCollitionWall::WallHeight(const std::vector<DirectX::SimpleMath::Vector3>& vertex, float height)
{
	//		�v���C���[�����b�V���̍������ɂ��Ȃ��ꍇ���������Ȃ�
	if (std::max(vertex[0].y, std::max(vertex[1].y, vertex[2].y)) <= m_playerPosition.y + 0.3f  ||
		std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y)) >= m_playerPosition.y + height)
	{
		//		�ǂ̍����O
		return false;
	}

	//		�ǂ̍�����
	return true;
}


bool MeshCollitionWall::Extrusion(const DirectX::SimpleMath::Vector3& normalize)
{
	//		���������|�C���g�ƃv���C���[�̍��W�̒���
	float length = (m_rayStart - m_hitPoint).Length();

	//		�������v���C���[�̔��a���傫����Ώ��������Ȃ�
	if (length > 2.0f)
	{
		return false;
	}

	//		�@����񎟌��ɂ���
	DirectX::SimpleMath::Vector2 normalizeV2 = { normalize.x, normalize.z };
	//		���K������
	normalizeV2.Normalize();

	//		�l�������ȏ�ɂȂ�Ȃ��悤�ɂ���
	float change = Library::Clamp(length, 0.0f, 2.0f);

	change *= 0.5f;

	//		�ω���
	normalizeV2 *= Library::Lerp(2.0f, 0.0f, change);

	//		�߂荞�񂾕��ړ�������
	m_playerPosition.x += normalizeV2.x;
	m_playerPosition.z += normalizeV2.y;

	m_normalize.push_back(normalize);

	return true;
}



std::vector<DirectX::SimpleMath::Vector3>& MeshCollitionWall::WallWalk
(ObjectMesh* objectMesh, const DirectX::SimpleMath::Vector3& playerPosition)
{
	//		���̒l����@�����쐬����
	m_meshCollitionManager->GetWallWalkNormalize();

	DirectX::SimpleMath::Vector2 normalize = 
	{ m_meshCollitionManager->GetWallWalkNormalize().x,
		m_meshCollitionManager->GetWallWalkNormalize().z };

	normalize.Normalize();

	normalize *= -1;

	//		���C�̊J�n
	DirectX::SimpleMath::Vector3 rayStart = playerPosition;

	//		���C�̏I��
	DirectX::SimpleMath::Vector3 rayEnd = playerPosition;

	normalize *= 3.0f;

	rayEnd += {normalize.x, 0.0f, normalize.y};

	m_hitpp.clear();

	//		���_
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	{
		//		�ǂ��ǂ������f����
		if (!WallJudgement(objectMesh->GetNormalizePosition(i))) continue;

		//		���_�̍��W���󂯎��
		vertex[0] = objectMesh->GetVertexPosition(i, 0);
		vertex[1] = objectMesh->GetVertexPosition(i, 1);
		vertex[2] = objectMesh->GetVertexPosition(i, 2);

		//		�v���C�[�̐L����菬�����ꍇ���������Ȃ�
		if (std::max(vertex[0].y, std::max(vertex[1].y, vertex[2].y)) - std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y)) < 7.0f)
		{
			continue;
		}

		//		�~�̓����蔻�肪�������Ă��Ȃ��ꍇ����ȏ㏈�������Ȃ�
		if (!m_meshCollitionManager->CollitionCC(vertex, rayStart, 2.0f))continue;

		//		���ꕽ�ʏ�ɂ��邩�ǂ���
		if (!m_meshCollitionManager->OnTheSamePlane(vertex, rayStart, rayEnd,
			objectMesh->GetNormalizePosition(i), &m_wallWalkHitPoint)) continue;

		//		���b�V���̎O�p�`�̓������ǂ���
		if (m_meshCollitionManager->InsideTriangle(vertex,
			objectMesh->GetNormalizePosition(i),
			m_wallWalkHitPoint))
		{
			//		�������Ă��镔����ǉ�����
			m_hitpp.push_back(m_wallWalkHitPoint);
		}
	}

	if (m_hitpp.size() == 1)
	{
		DirectX::SimpleMath::Vector3 pplayerPosition = { m_meshCollitionManager->GetWallWalkNormalize().x,
			0.0f, m_meshCollitionManager->GetWallWalkNormalize().z };

		pplayerPosition *= 2.0f;

		m_hitpp[0] += pplayerPosition;
	}

	return m_hitpp;
}
