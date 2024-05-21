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
#include "State/PlayerStartCamera.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "PlayerCameraInformation.h"

class DebugCamera;
class PlayerCamera;
class PlayerWallWalkCamera;
class PlayerStartCamera;

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
	void Update(PlayerInformation* playerInformation);

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

	//		�v���C���[�X�^�[�g�J����
	std::unique_ptr<PlayerStartCamera> m_playerStartCamera;

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

	/*
	*	�X�^�[�g�J������Ԃ��󂯎��	
	* 
	*	@return �v���C���[�X�^�[�g�J�����̃C���X�^���X�̃|�C���^
	*/
	PlayerStartCamera* GetStartCamera() { return m_playerStartCamera.get(); }

private:
	//		�J�����̏��
	std::unique_ptr<PlayerCameraInformation> m_information;

	//		�J�����p�v���C���[�̏��
	PlayerInformation* m_playerInformation;
	
public:

	/*
	*	�J�����̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerCameraInformation* GetInformation() { return m_information.get(); }
	
	/*
	*	�v���C���[�̏����󂯎��
	* 
	*	@return �v���C���[�̏��
	*/
	PlayerInformation* GetPlayerInformationCamera() { return m_playerInformation; }
};
