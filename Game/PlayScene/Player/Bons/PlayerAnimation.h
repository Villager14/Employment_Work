/*
* @file		PlayerAnimation.h
* @brief	�v���C���[�̃A�j���[�V����
* @author	Morita
* @date		2024/06/20
*/

#pragma once

#include "IPlayerAnimationState.h"

#include "PlayerBons.h"

#include "AnimationState/WalkAnimationState.h"
#include "AnimationState/StayAnimationState.h"
#include "AnimationState/CrouchingStayAnimationState.h"
#include "AnimationState/CrouchingWalkAnimationState.h"
#include "AnimationState/DashAnimationState.h"
#include "AnimationState/JumpAnimationState.h"
#include "AnimationState/SlidingAnimationState.h"
#include "AnimationState/StartAnimationState.h"
#include "AnimationState/WireJumpAnimationState.h"
#include "AnimationState/WallJumpAnimationState.h"
#include "AnimationState/WallWalkAnimationState.h"

class WalkAnimationState;
class StayAnimationState;
class CrouchingStayAnimationState;
class CrouchingWalkAnimationState;
class DashAnimationState;
class JumpAnimationState;
class SlidingAnimationState;
class StartAnimationState;
class WireJumpAnimationState;
class WallJumpAnimationState;
class WallWalkAnimationState;

class PlayerAnimation
{
public:

	//		�R���X�g���N�^
	PlayerAnimation();

	//		�f�X�g���N�^
	~PlayerAnimation();

	//		����������
	void Initialize();

	//		���s����
	void Execute(
		float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle,
		float height);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		���f���̍쐻
	void CreateModel();

	/*
	*	���f���̓ǂݍ���
	*
	*	@param	(path)		�t�@�C���p�X
	*	@param	(effect)	�G�t�F�N�g�t�@�N�g���[�̃|�C���^
	*	@param	(modelType)	���f���̎��
	*/
	void LoadModel(const wchar_t* path,
		DirectX::EffectFactory* effect);


	/*
	//		�A�j���[�V�����̒l�̃��Z�b�g
	void AnimationValuReset();

	//		�Q�[���X�^�[�g���̃A�j���[�V����
	void Start(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		��������
	void Walk(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		��~
	void Stop(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		�W�����v
	void Jump(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		�_�b�V��
	void Dash(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		���Ⴊ�ݒ�~
	void CrouchingStop(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		���Ⴊ�ݕ���
	void CrouchingWalk(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		���Ⴊ�ݕ���
	void Sliding(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		�Ǖ���
	void WallWalk(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		�ǃW�����v
	void WallJump(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		���C���[�W�����v
	void WireJump(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);
	*/

	void AnimationMovement(BonsType type,
		std::vector<PlayerBonsInformation>* m_bonesInformation,
		DirectX::SimpleMath::Quaternion firstVal,
		DirectX::SimpleMath::Quaternion endVal,
		float transrationSpeed);

	//		�����g�̒l�������̒l�ɂ���
	void AnimationLegInitialValue(std::vector<PlayerBonsInformation>* m_bonesInformation, float transrationSpeed);

	/*
	*	�A�j���[�V�����̐؂�ւ�
	*
	*	@param	(IState)
	*/
	void ChangeState(IPlayerAnimationState* IState);

private:

	//		�����A�j���[�V����
	std::unique_ptr<WalkAnimationState> m_walk;

	//		�ҋ@�A�j���[�V����
	std::unique_ptr<StayAnimationState> m_stay;

	//		���Ⴊ�ݑҋ@�A�j���[�V����
	std::unique_ptr<CrouchingStayAnimationState> m_crouchingStay;

	//		���Ⴊ�ݕ����A�j���[�V����
	std::unique_ptr<CrouchingWalkAnimationState> m_crouchingWalk;

	//		�_�b�V���A�j���[�V����
	std::unique_ptr<DashAnimationState> m_dash;

	//		�W�����v�A�j���[�V����
	std::unique_ptr<JumpAnimationState> m_jump;

	//		�X���C�f�B���O�A�j���[�V����
	std::unique_ptr<SlidingAnimationState> m_sliding;

	//		�X�^�[�g�A�j���[�V����
	std::unique_ptr<StartAnimationState> m_start;

	//		���C���[�W�����v�A�j���[�V����
	std::unique_ptr<WireJumpAnimationState> m_wireJump;

	//		�ǃW�����v�A�j���[�V����
	std::unique_ptr<WallJumpAnimationState> m_wallJump;

	//		�Ǖ����A�j���[�V����
	std::unique_ptr<WallWalkAnimationState> m_wallWalk;
public:

	/*
	*	�����A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	WalkAnimationState* GetWalkState() { return m_walk.get(); }

	/*
	*	�����A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	StayAnimationState* GetStayState() { return m_stay.get(); }

	/*
	*	���Ⴊ�ݑҋ@�A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	CrouchingStayAnimationState* GetCrouchingStay() { return m_crouchingStay.get(); }

	/*
	*	���Ⴊ�ݕ����A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	CrouchingWalkAnimationState* GetCrouchingWalk() { return m_crouchingWalk.get(); }

	/*
	*	�_�b�V���A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	DashAnimationState* GetDash() { return m_dash.get(); }

	/*
	*	�W�����v�A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	JumpAnimationState* GetJump() { return m_jump.get(); }

	/*
	*	�X���C�f�B���O�A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	SlidingAnimationState* GetSliding() { return m_sliding.get(); }

	/*
	*	�X�^�[�g�A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	StartAnimationState* GetStart() { return m_start.get(); }

	/*
	*	���C���[�W�����v�A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	WireJumpAnimationState* GetWireJump() { return m_wireJump.get(); }

	/*
	*	�ǃW�����v�A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	WallJumpAnimationState* GetWallJump() { return m_wallJump.get(); }

	/*
	*	�Ǖ����A�j���[�V�������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	WallWalkAnimationState* GetWallWalk() { return m_wallWalk.get(); }
private:

	//		���f��
	std::vector<std::unique_ptr<DirectX::Model>> m_playerModel;

	//		�v���C���[�̃{�[��
	std::unique_ptr<PlayerBons> m_playerBons;

	//		�A�j���[�V�����̏��
	IPlayerAnimationState* m_IState;


};

