/*
* @file		CrouchingWalkAnimationState.h
* @brief	���Ⴊ�ݕ����̃A�j���[�V����
* @author	Morita
* @date		2024/06/25
*/

#pragma once

#include "../IPlayerAnimationState.h"

#include "../BonInformation.h"

class PlayerAnimation;

class CrouchingWalkAnimationState : public IPlayerAnimationState
{
public:

	//		�R���X�g���N�^
	/*
	*	�R���X�g���N�^
	* 
	*	@param	(playerBons) �v���C���[�A�j���[�V�����̃C���X�^���X�̃|�C���^
	*/
	CrouchingWalkAnimationState(PlayerAnimation* PlayerAnimation);
	
	//		�f�X�g���N�^
	~CrouchingWalkAnimationState();

	//		����������
	void Initialize() override;

	/*
	*	�X�V����
	*
	*	@param	(speed)		���x
	*	@param	(position)	���W
	*	@param	(angle)		�p�x
	*	@param	(height)	���̍���
	*/
	void Update(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height,
		std::vector<PlayerBonsInformation>* bonesInformation) override;

	//		�I������
	void Finalize() override;

private:

	//		�v���C���[�̃A�j���[�V����
	PlayerAnimation* m_playerAnimation;

	//		�o�ߎ���
	float m_elapsedTime;

	//		�A�j���[�V�����J��
	float m_animationTransration;
};