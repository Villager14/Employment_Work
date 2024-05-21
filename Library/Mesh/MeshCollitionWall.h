/*
* @file		MeshCollitionWall.cpp
* @brief	���b�V���̓����蔻���
* @author	Morita
* @date		2024/04/28
*/

#pragma once

#include "ObjectMesh.h"

class MeshCollitionManager;

class MeshCollitionWall
{
public:

	MeshCollitionWall(MeshCollitionManager* meshCollitionManager);

	~MeshCollitionWall();

	/*
	*	�ǂ̓����蔻��
	* 
	*	@param	(objectMesh)		�I�u�W�F�N�g���b�V��
	*	@param	(playerPosition)	�v���C���[�̍��W
	*	@param	(height)	�v���C���[�̍���
	*/
	std::vector<DirectX::SimpleMath::Vector2> WallCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition,
		float height);

	/*
	*	�ǂɓ����������̖@��
	*
	*	@return �@��
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetNormalize() { return m_normalize; }

	/*
	*	�ǂ��ǂ������f����
	* 
	*	@param	(normalize)	�@��
	*	@return �ǂ��ǂ��� true : �ǂł��� false : �ǂł͂Ȃ�
	*/
	bool WallJudgement(const DirectX::SimpleMath::Vector3& normalize);

	/*
	*	�ǂ̍����Ƀv���C���[�����邩�ǂ���
	* 
	*	@param	(vertex)	���_
	*	@param	(height)	�v���C���[�̍���
	*	@return �������ɂ��邩�ǂ��� true : ����@false : ���Ȃ�
	*/
	bool WallHeight(const std::vector<DirectX::SimpleMath::Vector3>& vertex, float height);

	bool Extrusion(const DirectX::SimpleMath::Vector3& normalize);

	std::vector<DirectX::SimpleMath::Vector3>& WallWalk(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition);

private:

	MeshCollitionManager* m_meshCollitionManager;

	//		�������Ă���|�C���g
	DirectX::SimpleMath::Vector3 m_hitPoint;

	//		�ړ���
	std::vector<DirectX::SimpleMath::Vector2> m_moveVelocity;

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		�@��
	std::vector<DirectX::SimpleMath::Vector3> m_normalize;

	//		
	DirectX::SimpleMath::Vector3 m_wallWalkHitPoint;

	std::vector<DirectX::SimpleMath::Vector3> m_hitpp;

	//		���C�̊J�n
	DirectX::SimpleMath::Vector3 m_rayStart;

	//		���C�̏I��
	DirectX::SimpleMath::Vector3 m_rayEnd;
};