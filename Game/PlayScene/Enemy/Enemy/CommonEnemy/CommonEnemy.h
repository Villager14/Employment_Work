/*
* @file		CommonEnemy.h
* @brief	��ʓI�ȓG
* @author	Morita
* @date		2024/05/01
*/

#pragma once

#include "State/CommonEnemyStay.h"
#include "State/CommonEnemyVigilance.h"
#include "State/CommonEnemyCharge.h"
#include "State/CommonEnemyAttack.h"

#include "Library/Animation/AnimationManager.h"

class CommonEnemy
{
public:

	//		�R���X�g���N�^
	CommonEnemy();

	//		�f�X�g���N�^
	~CommonEnemy();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(playerPosition)	�v���C���[�̍��W
	*	@param	(timeSpeed)			���Ԃ̑��x
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition,
				float timeSpeed);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();


public:

	enum State
	{
		Stay,
		Vigilance,
		Charge,
		Attack,
	};

private:

	//		���
	ICommonEnemy* m_istate;

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		���W
	DirectX::SimpleMath::Vector3 m_position;

	//		�p�x
	float m_rotation;

	//		�U�����邩�ǂ���
	bool m_attackJudgement;

	//		���Ԃ̑��x
	float m_timeSpeed;

	//		�U���������
	DirectX::SimpleMath::Vector3 m_attakDirection;

	//		��Ԃ̏��
	std::unordered_map<State, std::unique_ptr<ICommonEnemy>> m_stateintarface;

	State m_state;

	//		�v���C���[�A�j���[�V����
	std::unique_ptr<AnimationManager> m_playerAnimation;

public:

	/*
	*	��Ԃ�؂�ւ���
	*
	*	@param	(nextState)	���̏��
	*/
	void ChangeState(State nextState)
	{
		//		������Ԃ̏ꍇ���������Ȃ�
		if (m_state == nextState) return;

		//���݂̏�Ԃ̏I������
		m_istate->Finalize();

		//���̏�Ԃ�؂�ւ���
		m_state = nextState;

		//���̏�Ԃ�؂�ւ���
		m_istate = m_stateintarface[m_state].get();

		//���̏�Ԃ̏���������
		m_istate->Initialize();
	}

	/*
	*	�v���C���[�A�j���[�V����
	* 
	*	@return �v���C���[�A�j���[�V����
	*/
	AnimationManager* GetPlayerAnimation() { return m_playerAnimation.get(); }

	/*
	*	�v���C���[�̍��W���󂯎��
	* 
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerPosition() { return m_playerPosition; }

	/*
	*	���W���󂯎��
	*
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

	/*
	*	���W��ݒ肷��
	* 
	*/
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	/*
	*	�U�����W���󂯎��
	* 
	*	@return ���W
	*/
	DirectX::SimpleMath::Vector3 GetAttackPosition() 
	{
		DirectX::SimpleMath::Vector3 attackPosition = m_position;

		attackPosition.y += 5.0f;

		return attackPosition;
	}

	/*
	*	�p�x��ݒ肷��
	* 
	*	@param	(rotation)	�p�x
	*/
	void SetRotation(float rotation) { m_rotation = rotation; }

	/*
	*	�p�x���󂯎��
	* 
	*	@return �p�x
	*/
	float GetRotation() { return m_rotation; }

	/*
	*	�U�����邩�ǂ������󂯎��
	* 
	*	@return true : �U������ false : �U�����Ȃ�
	*/
	bool GetAttackJudgement() { return m_attackJudgement; }

	/*
	*	�U�����邩�ǂ����ݒ肷��
	* 
	*	@param	(judgement)	true : �U������ false : �U�����Ȃ�
	*/
	void SetAttackJudgement(bool judgement) { m_attackJudgement = judgement; }

	/*
	*	�U�����������ݒ肷��
	* 
	*	@param	(direction)	����
	*/
	void SetAttackDirection(const DirectX::SimpleMath::Vector3& direction) { m_attakDirection = direction; }

	/*
	*	�U������������󂯎��
	* 
	*	@return ����
	*/
	const DirectX::SimpleMath::Vector3& GetAttackDirection() { return m_attakDirection; }

	/*
	*	���Ԃ̑��x���󂯎��
	* 
	*	@return ���x
	*/
	float GetTimeSpeed() { return m_timeSpeed; }
};