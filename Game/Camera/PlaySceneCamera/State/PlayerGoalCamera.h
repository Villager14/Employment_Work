/*
* @file		PlayerGoalCamera.h
* @brief	�v���C���[�̃S�[���J����
* @author	Morita
* @date		2024/06/27
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerGoalCamera : public IPlayerCamera
{
public:

	//		�R���X�g���N�^
	PlayerGoalCamera(PlayerCameraManager* playerCameraManager);
	//		�f�X�g���N�^
	~PlayerGoalCamera();
	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	void Finalize() override;

	//		�J�����̈ړ�
	void CameraMove();

private:

	//		�������������̊p�x
	const float DOWN_VIEW_ANGLE = -50.0f;

	//		���s�p�x�ő厞��
	const float PARALLEL_MAXIMUM_TIME = 2.0f;

	//		���s�p�x���x
	const float PARALLEL_MAXIMUM_SPEED = 2.0f;

private:

	//		�J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	PlayerCameraManager* m_playerCameraManager;

	//		�p�x
	DirectX::SimpleMath::Vector2 m_angle;

	//		�o�ߎ���
	float m_elapsedTime;

	//		������������
	float m_downElapsedTime;
};
