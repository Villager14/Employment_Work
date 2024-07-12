/*
* @file		Player.h
* @brief	�v���C���[�̏���
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "Game/PlayScene/CollitionManager/CollitionInformation.h"

#include "Game/PlayScene/Player/PlayerInformationCollition.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Game/PlayScene/Shadow/ShadowInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "PlayerInformation.h"

#include "Bons/PlayerAnimation.h"

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
#include "State/PlayerStart.h"
#include "State/PlayerGoal.h"

#include "State/PlayerAttack.h"

#include "Game/PlayScene/Shadow/Shadow.h"

#include "../ObjectManager/WireObject/WireObjectInformation.h"

#include <unordered_map>

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
class PlayerStart;
class PlayerGoal;

class Player
{
public:

	//		�R���X�g���N�^
	Player(GameManager* gameManager);

	//		�f�X�g���N�^
	~Player();

	//		����������
	void Initialize();

	//		�X�V����
	void Update(PlayerCameraInformation* cameraInformation);

	//		���b�V���̍X�V
	void MeshUpdate();

	//		�A�j���[�V�����̍X�V
	void AnimationUpdate();

	//		�`�揈��
	void Render(Shadow* hontai);

	//		���f���̕`��
	void ModelRender();

	//		�f�o�b�N�`��
	void DebugRender();


	//		�I������
	void Finalize();

	//		���S���������f����
	void DeathJudgement();

	//		�_�b�V���̃N�[���^�C��
	void DashCoolTime();

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

	//		���x���
	void SpeedUpperLimit();

public:

	//		�v���C���[�̏��
	enum PlayerState
	{
		Stay,
		Walk,
		Crouching,
		Jump,
		Sliding,
		Dash,
		WallWalk,
		WallJump,
		Wire,
		Death,
		Start,
		Goal,
	};

public:

	/*
	*	��Ԃ�ύX����
	*
	*	@param	(state)	���
	*/
	void ChangeState(PlayerState state);


private:

	//		�v���C���[�̏�Ԃ̏��
	std::unordered_map<PlayerState, std::unique_ptr<IPlayer>> m_stateInformation;

	//		���݂̏��
	PlayerState m_playerState;

	//		���݂̏��
	IPlayer* m_state;

	//		�v���C���[�̃A�j���[�V�����̏���
	std::unique_ptr<PlayerAnimation> m_playerAnimation;

	//		�����蔻��̏��
	CollitionInformation* m_collitionInformation;

	//		�����蔻��p�v���C���[�̏��
	std::unique_ptr<PlayerInformationCollition> m_playerInformationCollition;

	//		�v���C���[�̍U��
	std::unique_ptr<PlayerAttack> m_playerAttack;

	//		�v���C���[�̏��
	std::unique_ptr<PlayerInformation> m_information;

	//		�v���C���[���f��
	std::unique_ptr<DirectX::Model> m_playerObject;

	//		�J�����̏��
	PlayerCameraInformation* m_cameraInformation;

	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;

	//		���C���[�̏��
	std::vector<WireObjectInformation*> m_wireInformation;

	//		���j���[���g���邩�ǂ���
	bool m_menuUseJudgement;

public:

	/*
	*	�Q�[���}�l�[�W���[���󂯎��
	* 
	*	@return �Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	/*
	*	�v���C���[�J�����̏��
	* 
	*	@return �J�����̏��
	*/
	PlayerCameraInformation* GetCameraInformation() { return m_cameraInformation; }

	/*
	*	�v���C���[�J�����̏��
	*
	*	@return �J�����̏��
	*/
	void SetCameraInformation(PlayerCameraInformation* information) { m_cameraInformation = information; }


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
	*	�v���C���[�̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerInformation* GetInformation() { return m_information.get(); }

	/*
	*	�v���C���[�A�j���[�V�����̃C���X�^���X�̃|�C���^
	* 
	*	@return �|�C���^�̃C���X�^���X
	*/
	PlayerAnimation* GetAnimation() { return m_playerAnimation.get(); }

	/*
	*	���C���[�̏���ݒ肷��
	* 
	*	@param	(wireInformation)	���C���[�̏��
	*/
	void SetWireInformation(std::vector<WireObjectInformation*> wireInformation) { m_wireInformation = wireInformation; }

	/*
	*	���C���[�����󂯎��
	* 
	*	@return ���C���[�̏��
	*/
	std::vector<WireObjectInformation*> GetWireObjectInformation() { return m_wireInformation; }

	/*
	*	���j���[���g�����Ƃ��ł��邩�ǂ����󂯎��
	*	
	*	return true : �g�����Ƃ��ł���@false : �g�����Ƃ��ł��Ȃ�
	*/
	bool GetMenuUseJugement() { return m_menuUseJudgement; }

	/*
	*	���j���[���g�����Ƃ��ł��邩�ǂ����ݒ肷��
	*
	*	@param	(judgement) true : �g�����Ƃ��ł���@false : �g�����Ƃ��ł��Ȃ�
	*/
	void SetMenuUiseJudgement(bool judgement) { m_menuUseJudgement = judgement; }
 }; 
