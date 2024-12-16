/*
* @file		PlayerCamera.h
* @brief	�v���C���[�̃J����
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerCamera : public IPlayerCamera
{
public:

	//		�R���X�g���N�^
	PlayerCamera(PlayerCameraManager* playerCameraManager);
	//		�f�X�g���N�^
	~PlayerCamera();
	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	void Finalize() override;
	
	//		��Ԃ̑J�ڂ̊m�F
	void ChangeStateConfirmation();

private:

	//		�J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	PlayerCameraManager* m_playerCameraManager;

	//		�n�_�̍��W
	DirectX::SimpleMath::Vector3 m_position;
};
