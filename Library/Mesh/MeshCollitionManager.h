/*
* @file		MeshCollitionManager.h
* @brief	���b�V���̓����蔻��}�l�[�W���[
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include "Triangle.h"

#include "ObjectMesh.h"

#include "MeshCollitionFloor.h"

#include "MeshCollitionWall.h"

class MeshCollitionManager
{
public:
	//		�R���X�g���N�^
	MeshCollitionManager();

	//		�f�X�g���N�^
	~MeshCollitionManager();
	
	//		����������
	void Initialize();

	//		���b�V���̓����蔻��
	/*
	*	���b�V���̓����蔻��
	* 
	*	@param	(objctMesh)			�I�u�W�F�N�g���b�V��
	*	@param	(playerPosition)	�v���C���[�̍��W
	*	@param	(height)			����
	*	@param	(slidingJudgement)	�X���C�f�B���O�����Ă��邩�ǂ���
	*/
	void MeshCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition,
		float height, bool slidingJudgement);

	/*
	*	�~�Ɖ~�̓����蔻��
	* 
	*	@param	(vertex)	���b�V���̒��_
	*	@param	(playerPos)	�v���C���[�̍��W
	*	@param	(rayStart)	�v���C���[�̒���
	*	@return �����������ǂ��� true : �������� false : �������Ă��Ȃ�
	*/
	bool CollitionCC(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
					 const DirectX::SimpleMath::Vector3& playerPos,
					 const float& playerLength);

	/*
	*	���ꕽ�ʏ�ɂ��邩�ǂ���
	* 
	*	@param	(vertex)	���b�V���̒��_
	*	@param	(rayStart)	���C�̎n�_
	*	@param	(rayEnd)	���C�̏I�_
	*	@param	(normalize)	���b�V���̖@��
	*	@param	(hitPoint)	���������ꏊ
	*	@return �܂܂�Ă��邩�ǂ���	true : �܂܂�Ă��� false : �܂܂�Ă��Ȃ�
	*/
	bool OnTheSamePlane(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
						const DirectX::SimpleMath::Vector3& rayStart,
						const DirectX::SimpleMath::Vector3& rayEnd,
						const DirectX::SimpleMath::Vector3& normalize,
						DirectX::SimpleMath::Vector3* hitPoint);

	/*
	*	�O�p�`�̓����ɂ��邩�ǂ���
	* 
	*	@param	(vertex)	���b�V���̒��_
	*	@param	(normalize)	���b�V���̖@��
	*	@param	(hitPoint)	���������ꏊ
	*	@return �����ɂ��邩�ǂ��� true : ���� false : �O��
	*/
	bool InsideTriangle(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
						const DirectX::SimpleMath::Vector3& normalize,
						const DirectX::SimpleMath::Vector3& hitPoint);

	void MeshHitPointClear();
private:

	//		�v���C���[�̃��C�̒�����
	const float PLAYER_ABOVE_RAY_LENGTH = 2.0f;

private:

	float playerUnderRayLength = 0.5f;
	
	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		���b�V���̓��������|�C���g
	std::vector<DirectX::SimpleMath::Vector3> m_meshHitPoint;

	//		�ǂ̓����蔻��
	std::vector<DirectX::SimpleMath::Vector2> m_wallHit;

	//		�ǂ̖@���̓����蔻��
	std::vector<DirectX::SimpleMath::Vector3> m_wallHitNormalize;

	//		���b�V�����̓����蔻��
	std::unique_ptr<MeshCollitionFloor> m_meshCollitionFloor;

	//		���b�V���̕Ǔ����蔻��
	std::unique_ptr<MeshCollitionWall> m_meshCollitionWall;

	//		�Ǖ����@��
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;

	//		�Ǖ������̃v���C���[�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wallWalkPlayerPosition;

public:

	/*
	*	���b�V���̓��������|�C���g���󂯎��
	* 
	*	@return		���W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetMeshHitPoint() { return m_meshHitPoint; }

	/*
	*	���b�V�����ǂɓ��������|�C���g���󂯎��
	*
	*	@return		�ړ���
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetMeshWallHit() { return m_wallHit; }

	/*
	*	���b�V���ǂɓ����������̖@�����󂯎��
	* 
	*	@return �@��
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWallHitNormalize() { return m_wallHitNormalize; }

	/*
	*	�ǂ̕����@����ݒ肷��
	*
	*	@param	(normalize) �@��
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	�ǂ̕����@�����󂯎��
	*
	*	@return �@��
	*/
	const DirectX::SimpleMath::Vector3& GetWallWalkNormalize() { return m_wallWalkNormalize; }

	/*
	*	�Ǖ������̃v���C���[�̍��W���󂯎��
	* 
	*	@return �Ǖ������̃v���C���[�̍��W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWallWalkPlayerPosition() { return m_wallWalkPlayerPosition; }

	/*
	*	���̖@�����󂯎��
	* 
	*	@return �@��
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetFloorNormalize() { return m_meshCollitionFloor->GetNormalize(); }
};