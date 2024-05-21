/*
* @file		PlayerCameraManager.h
* @brief	�v���C���[�̃J�����̃}�l�[�W���[
* @author	Morita
* @date		2024/05/08
*/

#pragma once

#include "IPlayerCamera.h"

#include "State/DebugCamera.h"
#include "State/PlayerCamera.h"
#include "State/PlayerWallWalkCamera.h"

#include "Game/PlayScene/Player/PlayerInformationCamera.h"


class DebugCamera;
class PlayerCamera;
class PlayerWallWalkCamera;

class PlayerCameraManager
{
public:
	//		�R���X�g���N�^
	PlayerCameraManager();

	//		�f�X�g���N�^
	~PlayerCameraManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update(PlayerInformationCamera* playerInformationCamera);

	//		�I������
	void Finalize();

	//		�J�����̈ړ�����
	void CameraMove();

	/*
	*	��Ԃ�؂�ւ���
	* 
	*	@param	(state)	�V�������
	*/
	void ChangeState(IPlayerCamera* state);

	//		����p
	void ViewingAngle();

private:

	//		���
	IPlayerCamera* m_state;

	//		�f�o�b�N�J����
	std::unique_ptr<DebugCamera> m_debugCamera;

	//		�v���C���[�J����
	std::unique_ptr<PlayerCamera> m_playerCamera;

	//		�ǂ𑖂�J����
	std::unique_ptr<PlayerWallWalkCamera> m_playerWallWalkCamera;

public:
	/*
	*	�f�o�b�N�J�����̏�Ԃ��󂯎��
	* 
	*	@return �f�o�b�N�J�����̃C���X�^���X�̃|�C���^
	*/
	DebugCamera* GetDebugCamera() { return m_debugCamera.get(); }

	/*
	*	�v���C���[�J�����̏�Ԃ��󂯎��
	* 
	*	@return �v���C���[�J�����̃C���X�^���X�̃|�C���^
	*/
	PlayerCamera* GetPlayerCamera() { return m_playerCamera.get(); }

	/*
	*	�Ǒ���J�����̏�Ԃ��󂯎��
	* 
	*	@return �v���C���[�Ǒ���̃C���X�^���X�̃|�C���^
	*/
	PlayerWallWalkCamera* GetWallWalkCamera() { return m_playerWallWalkCamera.get(); }

private:

	//		�ő�p�xY
	const float ANGLE_Y_MAX = 50.0f;

	//		�ŏ��p�xY
	const float ANGLE_Y_MIN = -50.0f;

	//		�J�����̑��x
	const float CAMERA_SPEED = 5.0f;

private:

	//		�J�����p�v���C���[�̏��
	PlayerInformationCamera* m_playerInformationCamera;

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
	*	�J�����p�̃v���C���[�̏����󂯎��
	* 
	*	@return �J�������
	*/
	PlayerInformationCamera* GetPlayerInformationCamera() { return m_playerInformationCamera; }
};
