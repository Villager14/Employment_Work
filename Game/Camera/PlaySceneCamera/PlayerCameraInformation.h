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
	PlayerCameraInformation(){};

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
	const float VIEWING_ANGLE_MAX = 100.0f;

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

	//		�J�����̊p�x
	DirectX::SimpleMath::Vector2 m_angle;

	//		�����x�N�g��
	DirectX::SimpleMath::Vector3 m_viewVelocity;
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
};
