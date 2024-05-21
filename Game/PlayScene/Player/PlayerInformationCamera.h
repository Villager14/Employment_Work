/*
* @file		PlayerInformationCamera
* @brief	�J�����p�v���C���[�̏��
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "pch.h"

class PlayerInformationCamera
{
public:
	//		�R���X�g���N�^
	PlayerInformationCamera()
		:
		m_headWallMove(0.0f)
	{};

	//		�f�X�g���N�^
	~PlayerInformationCamera() {};


private:
	//		�����x
	DirectX::SimpleMath::Vector3 m_acceleration;

	//		�v���C���[�̍���
	DirectX::SimpleMath::Vector3 m_playerHeight;

	//		�ǈړ����̖@��
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;

	//		���̓���
	float m_headWallMove;

public:

	/*
	*	�v���C���[�̉����x���󂯎��
	*
	*	@return �����x
	*/
	const DirectX::SimpleMath::Vector3& GetAcceleration() { return m_acceleration; }

	/*
	*	�v���C���[�̍��W��ݒ肷��
	*
	*	@param	(acceleration)	�����x
	*/
	void SetAccelaration(DirectX::SimpleMath::Vector3 acceleration) { m_acceleration = acceleration; }

	/*
	*	�v���C���[�̍������󂯎��
	*
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerHeight() { return m_playerHeight; }

	/*
	*	�v���C���[�̍�����ݒ肷��
	*
	*	@param	(position)	���W
	*/
	void SetPlayerHeight(DirectX::SimpleMath::Vector3 position) { m_playerHeight = position; }

	/*
	*	�ǈړ����̖@�����󂯎��
	*
	*	@return �@��
	*/
	const DirectX::SimpleMath::Vector3& GetWallWalkNormalize() { return m_wallWalkNormalize; }

	/*
	*	�ǈړ����̖@����ݒ肷��
	*
	*	@param	(normalize)	�@��
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	���̓������󂯎��
	*
	*	@return �ړ���
	*/
	float GetHeadMove() { return m_headWallMove; }

	/*
	*	���̓�����ݒ肷��
	*
	*	@parma	�ړ���
	*/
	void SetHeadMove(float headWallMove) { m_headWallMove = headWallMove; }

};
