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
#include "AnimationState/UprightAnimationState.h"

#include <unordered_map>

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
class UprightAnimationState;

class PlayerAnimation
{
public:

	//		�R���X�g���N�^
	PlayerAnimation();

	//		�f�X�g���N�^
	~PlayerAnimation();

	//		����������
	void Initialize(bool createHead = false);

	//		���s����
	void Execute(
		float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle,
		float height);

	//		�`�揈��
	void Render(bool wireJudgement = false);

	//		�I������
	void Finalize();

	//		���f���̍쐻
	void CreateModel(bool createHead);

	/*
	*	���f���̓ǂݍ���
	*
	*	@param	(path)		�t�@�C���p�X
	*	@param	(effect)	�G�t�F�N�g�t�@�N�g���[�̃|�C���^
	*	@param	(modelType)	���f���̎��
	*/
	void LoadModel(const wchar_t* path,
		DirectX::EffectFactory* effect);

	void AnimationMovement(BonsType type,
		std::vector<PlayerBonsInformation>* m_bonesInformation,
		DirectX::SimpleMath::Quaternion firstVal,
		DirectX::SimpleMath::Quaternion endVal,
		float transrationSpeed);

	//		�����g�̒l�������̒l�ɂ���
	void AnimationLegInitialValue(std::vector<PlayerBonsInformation>* m_bonesInformation, float transrationSpeed);
public:

	enum AnimationState
	{
		Stay,
		Walk,
		CrouchingStay,
		CrouchingWalk,
		Jump,
		Sliding,
		Dash,
		WallWalk,
		WallJump,
		Wire,
		Start,
		Upright
	};

public:

	/*
	*	�A�j���[�V�����̐؂�ւ�
	*
	*	@param	(IState)
	*/
	void ChangeState(AnimationState State);

private:

	//		�A�j���[�V�����̏��
	std::unordered_map<AnimationState, std::unique_ptr<IPlayerAnimationState>> m_animationStateInformation;

	AnimationState m_animationState;

private:

	//		���f��
	std::vector<std::unique_ptr<DirectX::Model>> m_playerModel;

	//		�v���C���[�̃{�[��
	std::unique_ptr<PlayerBons> m_playerBons;

	//		�A�j���[�V�����̏��
	IPlayerAnimationState* m_IState;

	//		���[���h���W
	std::vector<DirectX::SimpleMath::Matrix> m_world;
};

