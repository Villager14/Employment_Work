/*
* @file		Player.h
* @brief	�v���C���[�̏���
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "Game/PlayScene/CollitionManager/CollitionInformation.h"

#include "Game/PlayScene/Player/PlayerInformationCollition.h"

#include "Game/PlayScene/Player/PlayerInformationCamera.h"

#include "PlayerInformation.h"

#include "State/PlayerStay.h"
#include "State/PlayerWalk.h"
#include "State/PlayerCrouching.h"
#include "State/PlayerJump.h"
#include "State/PlayerSliding.h"
#include "State/PlayerDash.h"
#include "State/PlayerSlowTime.h"
#include "State/PlayerWallWalk.h"
#include "State/PlayerWire.h"
#include "State/PlayerWallJump.h"
#include "State/PlayerDeath.h"

#include "State/PlayerAttack.h"


class PlayerStay;
class PlayerWork;
class PlayerCrouching;
class PlayerJump;
class PlayerSliding;
class PlayerDash;
class PlayerSlowTime;
class PlayerWallWalk;
class PlayerWire;
class PlayerWallJump;
class PlayerDeath;

class Player
{
public:

	//		�R���X�g���N�^
	Player();

	//		�f�X�g���N�^
	~Player();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		���b�V���̍X�V
	void MeshUpdate();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		���S���������f����
	void DeathJudgement();

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(IPlayer* state);

	/*
	*	�ړ�����
	*
	*	@param	(keyPressJudgement)	�L�[�����������ǂ���
	*	@return �ړ�����
	*/
	DirectX::SimpleMath::Vector3 Direction(bool* keyPressjudgement);

	/*
	*	�ړ��������
	*
	*	@param (direction) �ړ�����������
	*	@return ����
	*/
	DirectX::SimpleMath::Vector3 MoveDirection
	(const DirectX::SimpleMath::Vector3 direction);

	/*
	*	�d�͏���
	* 
	*	@param	(weekJudgement)	�ア�d�͂ɂ��邩�ǂ���
	*/
	void Gravity(bool weekJudgement = false);

	//		�����b�V���ɓ������Ă��邩���f����
	bool FloorMeshHitJudgement();

	//		�ǃ��b�V���ɓ������Ă��邩���f����
	bool WallMeshHitJudgement();

	/*
	*	����Ԃɂ���
	*
	*	@param	(firstHeight)	�ŏ��̍���
	*	@param	(endHeight)		�ŏI�I�ȍ���
	*	@param	(speed)			���x
	*/
	void PlayerHeightTransition(const float& firstHeight, const float& endHeight, const float& speed);

	/*
	*	���C���[�A�N�V���������邩�ǂ���
	* 
	*	@returnr ���邩�ǂ��� true : �s�� fales : �s��Ȃ�
	*/
	bool WireActionJudgement();

	//		�ǃW�����v��ԂɂȂ邩�ǂ���
	void WallWalkJudgement();

private:

	//		���݂̏��
	IPlayer* m_state;

	//		�v���C���[�ҋ@���
	std::unique_ptr<PlayerStay> m_playerStay;

	//		�v���C���[�������
	std::unique_ptr<PlayerWalk> m_playerWalk;

	//		�v���C���[���Ⴊ�ݏ��
	std::unique_ptr<PlayerCrouching> m_playerCrouching;

	//		�v���C���[�̃W�����v���
	std::unique_ptr<PlayerJump> m_playerJump;

	//		�v���C���[�̃X���C�f�B���O���
	std::unique_ptr<PlayerSliding> m_playerSliding;

	//		�v���C���[�̃_�b�V�����
	std::unique_ptr<PlayerDash> m_playerDash;

	//		�v���C���[�ᑬ���
	std::unique_ptr<PlayerSlowTime> m_playerSlowTime;

	//		�v���C���[�̕Ǒ�����
	std::unique_ptr<PlayerWallWalk> m_playerWallWalk;

	//		�v���C���[�̃��C���[���
	std::unique_ptr<PlayerWire> m_playerWire;

	//		�v���C���[�̕ǃW�����v���
	std::unique_ptr<PlayerWallJump> m_playerWallJump;

	//		�v���C���[�̎��S���
	std::unique_ptr<PlayerDeath> m_playerDeath;
public:

	/*
	*	�ҋ@��Ԃ��󂯎��
	*
	*	@return �ҋ@��Ԃ̃C���X�^���X�̃|�C���^
	*/
	PlayerStay* GetStayState() { return m_playerStay.get(); }

	/*
	*	������Ԃ��󂯎��
	*
	*	@return ������Ԃ̃C���X�^���X�̃|�C���^
	*/
	PlayerWalk* GetWalkState() { return m_playerWalk.get(); }

	/*
	*	���Ⴊ�ݏ�Ԃ��󂯎��
	*
	*	@return ���Ⴊ�ݏ�Ԃ̃C���X�^���X�̃|�C���^
	*/
	PlayerCrouching* GetCrouchingState() { return m_playerCrouching.get(); }

	/*
	*	�W�����v��Ԃ��󂯎��
	*
	*	@return �W�����v��Ԃ̃C���X�^���X�̃|�C���^
	*/
	PlayerJump* GetJumpState() { return m_playerJump.get(); }

	/*
	*	�v���C���[�̃X���C�f�B���O��Ԃ��󂯎��
	*
	*	@return �X���C�f�B���O��Ԃ̃C���X�^���X�̃|�C���^
	*/
	PlayerSliding* GetSlidingState() { return m_playerSliding.get(); }

	/*
	*	�v���C���[�̃_�b�V����Ԃ��󂯎��
	*
	*	@return �_�b�V����Ԃ̃C���X�^���X�̃|�C���^
	*/
	PlayerDash* GetDashState() { return m_playerDash.get(); }

	/*
	*	�v���C���[�̒ᑬ��Ԃ��󂯎��
	*
	*	@return �ᑬ��Ԃ̃C���X�^���X�̃|�C���^
	*/
	PlayerSlowTime* GetSlowTimeState() { return m_playerSlowTime.get(); }

	/*
	*	�v���C���[�̕ǂ������Ԃ��󂯎��
	* 
	*	@return �ǂ������Ԃ̃C���X�^���X�̃|�C���^
	*/
	PlayerWallWalk* GetWallWalkState() { return m_playerWallWalk.get(); }

	/*
	*	�v���C���[�̃��C���[��Ԃ��󂯎��
	* 
	*	@return ���C���[��Ԃ̃C���X�^���X���󂯎��
	*/
	PlayerWire* GetWireState() { return m_playerWire.get(); }

	/*
	*	�v���C���[�̕ǃW�����v��Ԃ��󂯎��
	* 
	*	@return �ǃW�����v�̃C���X�^���X���󂯎��
	*/
	PlayerWallJump* GetWallJumpState() { return m_playerWallJump.get(); }

	/*
	*	�v���C���[�̎��S��Ԃ��󂯎��
	* 
	*	@return ���S��Ԃ̃C���X�^���X���󂯎��
	*/
	PlayerDeath* GetDeathState() { return m_playerDeath.get(); }

private:
	//		�����x
	const float STANDING_SPEED = 3.0f;

	//		�������x
	const float WALK_SPEED = 50.0f;

	//		���Ⴊ�ݑ��x 
	const float CROUCHING_SPEED = 30.0f;

	//		�v���C���[�̍���
	const float STANDING_HEIGHT = 7.0f;

	//		�������x
	const float DECELERATION_SPEED = 80.0f;

	//		�ǈړ����̍ō��ړ���
	const float HEAD_MOVE_MAX = 4.0f;

	//		���̈ړ����x
	const float HEAD_MOVE_SPEED = 30.0f;

private:

	//		�����蔻��̏��
	CollitionInformation* m_collitionInformation;

	//		�����蔻��p�v���C���[�̏��
	std::unique_ptr<PlayerInformationCollition> m_playerInformationCollition;

	//		�J�����p�v���C���[���
	std::unique_ptr<PlayerInformationCamera> m_playerInformationCamera;

	//		�v���C���[�̍U��
	std::unique_ptr<PlayerAttack> m_playerAttack;

	//		�v���C���[�̏��
	std::unique_ptr<PlayerInformation> m_information;

	//		�v���C���[���f��
	std::unique_ptr<DirectX::Model> m_playerObject;

public:

	/*
	*	�����̑���
	*
	*	@return ���x
	*/
	float GetWalkSpeed() { return WALK_SPEED; }

	/*
	*	�����̑���
	*
	*	@return ���x
	*/
	float GetDecelerationSpeed() { return DECELERATION_SPEED; }

	/*
	*	���Ⴊ�݂̑���
	*
	*	@return ���x
	*/
	float GetCrouchingSpeed() { return CROUCHING_SPEED; }

	/*
	*	�����Ă���Ƃ��̍���
	*
	*	@return ���x
	*/
	float GetStandingHeight() { return STANDING_HEIGHT; }

	/*
	*	���̍ō��ړ��ʂ��󂯎��
	*
	*	@reutrn �ړ���
	*/
	inline constexpr float GetHeadMoveMAX() const noexcept { return HEAD_MOVE_MAX; }

	/*
	*	���̈ړ����x���󂯎��
	*
	*	@return �ړ����x
	*/
	inline constexpr float GetHeadMoveSpeed() const noexcept { return HEAD_MOVE_SPEED; }

public:

	/*
	*	�����蔻��̏����󂯎��
	* 
	*	@param	(collitionInformation)	�C���X�^���X�̃|�C���^
	*/
	void SetCollitionInformation(CollitionInformation* collitionInformation)
							{ m_collitionInformation = collitionInformation; }

	/*
	*	�����蔻��̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	CollitionInformation* GetCollitionInformation() { return m_collitionInformation; }

	/*
	*	�����蔻��p����ݒ肷��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerInformationCollition* GetPlayerInformationCollition() { return m_playerInformationCollition.get(); }

	/*
	*	�J�����p�v���C���[�����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerInformationCamera* GetPlayerInformationCamera() { return m_playerInformationCamera.get(); }

	/*
	*	�v���C���[�̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerInformation* GetInformation() { return m_information.get(); }
 }; 
