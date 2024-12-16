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
		m_angleMin(0.0f),
		m_viewAngle(70.0f),
		m_mouseSpeed(5.0f),
		m_nowViewAngle(0.0f),
		m_startDirection(0.0f),
		m_playerSpeed(0.0f),
		m_wallHeadMove(0.0f),
		m_direction(0.0f),
		m_stopJudgement(false),
		m_shakeHeadJudgement(false)
	{};

	//		�f�X�g���N�^
	~PlayerCameraInformation() {};

	void Initialize()
	{
		m_angleMin = 0.0f;
		m_viewAngle = 70.0f;
		m_mouseSpeed = 5.0f;
		m_angle = { 0.0f, 0.0f };
	}

	void Finalize()
	{
		m_angleMin = 0.0f;
		m_viewAngle = 70.0f;
		m_mouseSpeed = 5.0f;
		m_angle = { 0.0f, 0.0f };
		m_viewVelocity = DirectX::SimpleMath::Vector3::Zero;
		m_up = DirectX::SimpleMath::Vector3::Zero;
		m_target = DirectX::SimpleMath::Vector3::Zero;
		m_eye = DirectX::SimpleMath::Vector3::Zero;
		m_cameraMove = DirectX::SimpleMath::Vector2::Zero;
	}

public:

	//		�ő�p�xY
	const float ANGLE_Y_MAX = 50.0f;

	//		�ŏ��p�xY
	const float ANGLE_Y_MIN = -50.0f;

	//		�����ύX����Œᑬ�x
	const float ANGLE_CHANGE_MIN_SPEED = 30.0f;

	//		�����ύX����ō����x
	const float ANGLE_CHANGE_MAX_SPEED = 60.0f;

private:

	//		����p
	float m_viewAngle;

	//		�}�E�X�̑��x
	float m_mouseSpeed;

	//		�ŏ��l
	float m_angleMin;

	//		���݂̎���p
	float m_nowViewAngle;

	//		�J�n���̕���
	float m_startDirection;

	//		�v���C���[�̑��x
	float m_playerSpeed;

	//		���𓮂�����
	float m_wallHeadMove;

	//		�J�������~�߂邩�ǂ���
	bool m_stopJudgement;

	//		����h�炵�Ă��邩�ǂ���
	bool m_shakeHeadJudgement;

	//		�J�����̊p�x
	DirectX::SimpleMath::Vector2 m_angle;

	//		�����x�N�g��
	DirectX::SimpleMath::Vector3 m_viewVelocity;

	DirectX::SimpleMath::Vector3 m_up;

	DirectX::SimpleMath::Vector3 m_target;

	DirectX::SimpleMath::Vector3 m_eye;

	//		�J�����̈ړ���
	DirectX::SimpleMath::Vector2 m_cameraMove;

	//		�v���C���[�̍���
	DirectX::SimpleMath::Vector3 m_playerHeight;

	//		�v���C���[�̈ړ�����
	DirectX::SimpleMath::Vector3 m_direction;

	//		�ǂ̖@��
	DirectX::SimpleMath::Vector3 m_wallNormalize;

	//		����h�炷�x�N�g��
	DirectX::SimpleMath::Vector3 m_shakeHeadVelocity;

public:

	/*
	*	����p��ݒ肷��
	*
	*	@param	(angle)	�p�x
	*/
	void SetViewAngle(float angle) { m_viewAngle = angle; }

	/*
	*	����p���󂯎��
	*
	*	@return	�p�x
	*/
	float GetViewAngle() { return m_viewAngle; }

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

	/*
	*	�}�E�X�̑��x���󂯎��
	*
	*	@return	���x
	*/
	float GetCameraSpeed() { return m_mouseSpeed; }

	/*
	*	�}�E�X�̑��x��ݒ肷��
	*
	*	@param	(speed)
	*/
	void SetCameraSpeed(float speed) { m_mouseSpeed = speed; }

	/*
	*	���݂̎���p��ݒ肷��
	*
	*	@param	(viewAngle)	����p�x
	*/
	void SetNowViewAngle(float viewAngle) { m_nowViewAngle = viewAngle; }

	/*
	*	���݂̎���p���󂯎��
	*
	*	@return ����p
	*/
	float GetNowViewAngle() { return m_nowViewAngle; }

	/*
	*	�J�n���̕��@��ݒ肷��
	*
	*	@param	(direction)	�p�x
	*/
	void SetStartDirection(float direction) { m_startDirection = direction; }

	/*
	*	�J�n���̕������󂯎��
	*
	*	@return �p�x
	*/
	float GetStartDirection() { return m_startDirection; }

	/*
	*	�v���C���[�̍������󂯎��
	*
	*	@return ����
	*/
	void SetPlayerHeight(DirectX::SimpleMath::Vector3 height) { m_playerHeight = height; }

	/*
	*	�v���C���[�̍������󂯎��
	*
	*	@return ����
	*/
	DirectX::SimpleMath::Vector3 GetPlayerHeight() { return m_playerHeight; }

	/*
	*	�v���C���[�̑��x��ݒ肷��
	*
	*	@param	(speed)	���x
	*/
	void SetPlayerSpeed(float speed) { m_playerSpeed = speed; }

	/*
	*	�v���C���[�̑��x���󂯎��
	*
	*	@return ���x
	*/
	float GetPlayerSpeed() { return m_playerSpeed; }

	/*
	*	���𓮂����ʂ�ݒ肷��
	*
	*	@param	(move)	�ړ���
	*/
	void SetWallHeight(float move) { m_wallHeadMove = move; }

	/*
	*	���𓮂����ʂ��󂯎��
	*
	*	@return �ړ���
	*/
	float GetWallHeight() { return m_wallHeadMove; }


	/*
	*	�v���C���[�̈ړ�������ݒ肷��
	*
	*	@param	(direction)	�ړ�����
	*/
	void SetDirection(DirectX::SimpleMath::Vector3 direction) { m_direction = direction; }

	/*
	*	�v���C���[�̈ړ������󂯎��
	*
	*	@return �ړ�����
	*/
	DirectX::SimpleMath::Vector3 GetDirection() { return m_direction; }

	/*
	*	�ǂ̖@����ݒ肷��
	*
	*	@param	(noramlize) �@��
	*/
	void SetWallNormalize(DirectX::SimpleMath::Vector3 normalize) { m_wallNormalize = normalize; }

	/*
	*	�ǂ̖@�����󂯎��
	*
	*	@return �@��
	*/
	DirectX::SimpleMath::Vector3 GetWallNormalize() { return m_wallNormalize; }

	/*
	*	��~���Ă��邩�󂯎��
	* 
	*	@return true : ��~���Ă��� false : ��~���Ă��Ȃ�
	*/
	bool GetStopJudgement() { return m_stopJudgement; }

	/*
	*	��~���Ă��邩�ݒ肷��
	* 
	*	@param	(judgement) true : ��~���Ă��� false : ��~���Ă��Ȃ�
	*/
	void SetStopJudgement(bool judgement) { m_stopJudgement = judgement; }

	/*
	*	����h�炷�x�N�g�����󂯎��
	* 
	*	@return �x�N�g��
	*/
	DirectX::SimpleMath::Vector3 GetShaekHeadVelocity() { return m_shakeHeadVelocity; }

	/*
	*	����h�炷�x�N�g����ݒ肷��
	* 
	*	@param	(velocity)	�x�N�g��
	*/
	void SetSheakHeadVelocity(DirectX::SimpleMath::Vector3 velocity) { m_shakeHeadVelocity = velocity; }

	/*
	*	����U�邩�ǂ����󂯎��
	*
	*	@return	true : ����U���Ă��� false : ����U���Ă��Ȃ�
	*/
	bool GetShackHeadJudgement() { return m_shakeHeadJudgement; }

	/*
	*	����U�邩�ǂ����ݒ肷��
	* 
	*	@param	(judgement)	true : ����U���Ă��� false : ����U���Ă��Ȃ�
	*/
	void SetShackHeadJudgement(bool judgement) { m_shakeHeadJudgement = judgement; }
};
