/*
* @file		PlayerCameraInformation.cpp
* @brief	�v���C���[�̃J�����̏��
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "pch.h"

class PlayerCameraInformation
{
public:
	//		�R���X�g���N�^
	PlayerCameraInformation()
		:
		m_angleMin(0.0f)
	{};

	//		�f�X�g���N�^
	~PlayerCameraInformation() {};


private:

	//		�ő�p�xY
	const float ANGLE_Y_MAX = 50.0f;

	//		�ŏ��p�xY
	const float ANGLE_Y_MIN = -50.0f;

	//		�J�����̑��x
	const float CAMERA_SPEED = 5.0f;

	//		����p�ő�
	const float VIEWING_ANGLE_MAX = 90.0f;

	//		����p�ŏ�
	const float VIEWING_ANGLE_MIN = 70.0f;

public:

	/*
	*	�ő�p�xY���󂯎��
	*
	*	@return �p�x
	*/
	float GetMaxAngleY() { return ANGLE_Y_MAX; }

	/*
	*	�ŏ��p�xY���󂯎��
	*
	*	@return �p�x
	*/
	float GetMinAngleY() { return ANGLE_Y_MIN; }

	/*
	*	�J�����̑��x���󂯎��
	*
	*	@return ���x
	*/
	float GetCameraSpeed() { return CAMERA_SPEED; }

private:

	//		�ŏ��l
	float m_angleMin;

	//		�J�����̊p�x
	DirectX::SimpleMath::Vector2 m_angle;

	//		�����x�N�g��
	DirectX::SimpleMath::Vector3 m_viewVelocity;

	DirectX::SimpleMath::Vector3 m_up;

	DirectX::SimpleMath::Vector3 m_target;

	DirectX::SimpleMath::Vector3 m_eye;

	//		�J�����̈ړ���
	DirectX::SimpleMath::Vector2 m_cameraMove;

public:

	/*
	*	�J�����̊p�x���󂯂Ƃ�
	*
	*	@return �p�x
	*/
	const DirectX::SimpleMath::Vector2 GetAngle() { return m_angle; }

	/*
	*	�J�����̊p�x��ݒ肷��
	*
	*	@param	(angle)	�p�x
	*/
	void SetAngle(DirectX::SimpleMath::Vector2 angle) { m_angle = angle; }

	/*
	*	�����x�N�g����ݒ肷��
	*
	*	@param	(velocity)	�x�N�g��
	*/
	void SetViewVelocity(const DirectX::SimpleMath::Vector3& velicity) { m_viewVelocity = velicity; }

	/*
	*	�����x�N�g�����󂯎��
	*
	*	@return �x�N�g��
	*/
	const DirectX::SimpleMath::Vector3& GetViewVelocity() { return m_viewVelocity; }

	/*
	*	����p�ŏ��p�x���󂯎��
	*
	*	@return �p�x
	*/
	const float GetViewingAngleMin() { return VIEWING_ANGLE_MIN; }

	/*
	*	����p�ő�p�x���󂯎��
	*
	*	@return �p�x
	*/
	const float GetViewingAngleMax() { return VIEWING_ANGLE_MAX; }

	/*
	*	Eye�x�N�g����ݒ肷��
	*
	*	@param	(eye)	�����x�N�g��
	*/
	void SetEye(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }

	/*
	*	Eye�x�N�g�����󂯎��
	*
	*	@return �����x�N�g��
	*/
	DirectX::SimpleMath::Vector3 GetEye() { return m_eye; }

	/*
	*	�^�[�Q�b�g��ݒ肷��
	*
	*	@param	(target)	�^�[�Q�b�g�x�N�g��
	*/
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }

	/*
	*	�^�[�Q�b�g���󂯎��
	*
	*	@return �^�[�Q�b�g
	*/
	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }

	/*
	*	�A�b�v�x�N�g����ݒ肷��
	*
	*	@param	(up)	�A�b�v�x�N�g��
	*/
	void SetUp(DirectX::SimpleMath::Vector3 up) { m_up = up; }

	/*
	*	�A�b�v�x�N�g�����󂯎��
	*
	*	@return �A�b�v�x�N�g��
	*/
	DirectX::SimpleMath::Vector3 GetUP() { return m_up; }

	/*
	*	�J�����̈ړ��ʂ�ݒ肷��
	*
	*	@param	(move)	�ړ���
	*/
	void SetCameraMove(DirectX::SimpleMath::Vector2 move) { m_cameraMove = move; }

	/*
	*	�J�����̈ړ��ʂ��󂯎��
	*
	*	@return �ړ���
	*/
	DirectX::SimpleMath::Vector2 GetCameraMove() { return m_cameraMove; }

	/*
	*	�J�����p�x�̍ŏ��l���󂯎��
	*
	*	@return �ŏ��l
	*/
	float GetCameraAngleMin() { return m_angleMin; }

	/*
	*	�J�����p�x�̍ŏ��l��ݒ肷��
	* 
	*	@param	(angle)	�p�x
	*/
	void SetCameraAngleMin(float angle) { m_angleMin = angle; }
};
