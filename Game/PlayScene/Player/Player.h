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

	/*
	*	�v���C���[�̍���
	*
	*	@param	(height)	����
	*/
	void PlayerHeight(const float& height);

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

	//		�v���C���[�̍U�������Ă��邩�ǂ���
	bool m_playerAttackJudgement;

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_position;

	//		�ړ�����\��̍��W
	DirectX::SimpleMath::Vector3 m_planPosition;

	//		�v���C���[�̍���
	DirectX::SimpleMath::Vector3 m_playerHeight;

	//		�J�����̌����Ă���p�x
	DirectX::SimpleMath::Vector2 m_cameraAngle;

	//		�d�͂̉����x
	float m_gravitationalAcceleration;

	//		��������
	float m_fallTime;

	//		�d��
	float m_gravity;

	//		���Ԃ̑��x
	float m_timeSpeed;

	//		�����x
	DirectX::SimpleMath::Vector3 m_acceleration;

	//		���b�V���ɓ������Ă��邩�ǂ���
	bool m_meshHitJudgement;

	//		�����ϓ�����
	float m_heightTime;

	//		�v���C���[�̃��[���h���W
	DirectX::SimpleMath::Matrix m_world;

	//		�ړ��������
	DirectX::SimpleMath::Vector3 m_direction;

	//		�����f��
	std::unique_ptr<DirectX::Model> m_playerObject;

	//		���C���[�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wirePosition;

	//		�����x�N�g��
	DirectX::SimpleMath::Vector3 m_viewVelocity;

	//		�ړ����郏�C���[�̍��W
	DirectX::SimpleMath::Vector3 m_wireMovePosition;

	//		�_�b�V���̃N�[���^�C��
	float m_dashCoolTime;

	//		�_�b�V�����ł��邩�ǂ���
	bool m_dashJudgement;

	//		�W�����v�ł��邩�ǂ���
	bool m_jumpJudgement;

	//		���X�|�[�����邩�ǂ���
	bool m_respownJudgement;

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
	*	���[���h���W���󂯎��
	*
	*	@return ���[���h���W
	*/
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }

	/*
	*	���[���h���W��ݒ肷��
	*
	*	@param	(world)	���[���h���W
	*/
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	/*
	*	���W���󂯎��
	*
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

	/*
	*	���W��ݒ肷��
	*
	*	@param	(position)	���W
	*/
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	/*
	*	�ړ��\����W���󂯎��
	*
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPlanPosition() { return m_planPosition; }

	/*
	*	�ړ��\����W��ݒ肷��
	*
	*	@param	(position)	���W
	*/
	void SetPlanPosition(const DirectX::SimpleMath::Vector3& position) { m_planPosition = position; }

	/*
	*	�J�����̊p�x��ݒ肷��
	*
	*	@param	(angle)	�p�x
	*/
	void SetCameraAngle(DirectX::SimpleMath::Vector2 angle) { m_cameraAngle = angle; }

	/*
	*	�J�����̊p�x���󂯎��
	*
	*	@return �p�x
	*/
	const DirectX::SimpleMath::Vector2& GetCameraAngle() { return m_cameraAngle; }

	/*
	*	�v���C���[�̍�����ݒ肷��
	*
	*	@param	(position)	����
	*/
	void SetPlayerHeight(const DirectX::SimpleMath::Vector3& position) { m_playerHeight = position; }

	/*
	*	�v���C���[�̍������󂯎��
	*
	*	@return ����
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerHeight() { return m_playerHeight; }

	/*
	*	�ړ�����������󂯎��
	*
	*	@return ����
	*/
	const DirectX::SimpleMath::Vector3& GetDirection() { return m_direction; }

	/*
	*	�ړ����������ݒ肷��
	*
	*	@param	(direction)	����
	*/
	void SetDirection(const DirectX::SimpleMath::Vector3& direction) { m_direction = direction; }

	/*
	*	�������Ԃ�ݒ肷��
	*
	*	@param	(time)	����
	*/
	void SetFallTime(const float& time) { m_fallTime = time; }

	/*
	*	���Ԃ̑��x���󂯎��
	*
	*	@return ���Ԃ̑��x
	*/
	const float& GetTimeSpeed() { return m_timeSpeed; }

	/*
	*	���Ԃ̑��x��ݒ肷��
	*
	*	@param	(speed)	���x
	*/
	void SetTimeSpeed(const float& speed) { m_timeSpeed = speed; }

	/*
	*	�v���C���[���U�����Ă��邩���󂯎��
	*
	*	@return	true : �U�����Ă��� false : �U�����Ă��Ȃ�
	*/
	const bool& GetAttackJudgement() { return m_playerAttackJudgement; }

	/*
	*	�v���C���[���U�����Ă��邩�ݒ肷��
	* 
	*	@param	(judgement)	true : �U������ false : �U�����Ȃ�
	*/
	void SetAttackJudgement(const bool& judgement) { m_playerAttackJudgement = judgement; }
	
	/*
	*	�����ϓ����Ԃ�ݒ肷��
	* 
	*	@param	(time)	����
	*/
	void SetHeightTime(const float& time) { m_heightTime = time; }

	/*
	*	�����x���󂯎��
	* 
	*	@return �����x
	*/
	const DirectX::SimpleMath::Vector3& GetAcceleration() { return m_acceleration; }

	/*
	*	�����x��ݒ肷��
	* 
	*	@param	(acceleration)	�����x
	*/
	void SetAcceleration(const DirectX::SimpleMath::Vector3& acceleration) { m_acceleration = acceleration; }

	/*
	*	�d�͂�ݒ肷��
	* 
	*	@param	(gravity)	�d��
	*/
	void SetGravity(float gravity) { m_gravity = gravity; }

	/*
	*	�d�͂��󂯎��
	* 
	*	@return �d��
	*/
	float GetGravity() { return m_gravity; }

	/*
	*	���C���[�̍��W���󂯎��
	* 
	*	@return ���W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWirePosition() { return m_wirePosition; }

	/*
	*	���C���[�̍��W��ݒ肷��
	* 
	*	@param	(position)	���W
	*/
	void SetWirePosition(const std::vector<DirectX::SimpleMath::Vector3>& position) { m_wirePosition = position; }

	/*
	*	�����x�N�g����ݒ肷��
	* 
	*	@param	(velocity)
	*/
	void SetViewVelocity(const DirectX::SimpleMath::Vector3& veloicty) { m_viewVelocity = veloicty; }

	/*
	*	���C���[�̈ړ����W���󂯎��
	*
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetWireMovePosition() { return m_wireMovePosition; }

	/*
	*	�����蔻��p����ݒ肷��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerInformationCollition* GetPlayerInformationCollition() { return m_playerInformationCollition.get(); }

	/*
	*	�_�b�V�������邩�ǂ������f����
	* 
	*	@return true : �_�b�V�������� �ł��� : �_�b�V�����ł��Ȃ�
	*/
	bool GetDashJudgement() { return m_dashJudgement; }

	/*
	*	�_�b�V�������Ă��邩�ݒ肷��
	* 
	*	@param	(judgemnet)	true : �_�b�V���ł��� false : �_�b�V�����ł��Ȃ�
	*/
	void SetDashJudgement(bool judgement) { m_dashJudgement = judgement; }

	/*
	*	�W�����v�����邩�ǂ������f����
	*
	*	@return true : �W�����v�ł��� false : �W�����v�ł��Ȃ�
	*/
	bool GetJumpJudgement() { return m_jumpJudgement; }

	/*
	*	�W�����v�����Ă��邩�ݒ肷��
	*
	*	@param	(judgemnet)	true : �W�����v�ł��� false : �W�����v�ł��Ȃ�
	*/
	void SetJumpJudgement(bool judgement) { m_jumpJudgement = judgement; }

	/*
	*	�J�����p�v���C���[�����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerInformationCamera* GetPlayerInformationCamera() { return m_playerInformationCamera.get(); }

	/*
	*	���X�|�[�����邩�ǂ�����ݒ肷��
	* 
	*	@param	(judgement)	true : ���X�|�[����ԁ@false : ���X�|�[����Ԃł͂Ȃ�
	*/
	void SetRespownJudgement(bool judgement) { m_respownJudgement = judgement; }

	/*
	*	���X�|�[�����邩�ǂ����󂯎��
	* 
	*	@return true : ���X�|�[����ԁ@false : ���X�|�[����Ԃł͂Ȃ�
	*/
	bool GetRespownJugement() { return m_respownJudgement; }
 }; 
