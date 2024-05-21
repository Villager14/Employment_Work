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

class CommonEnemyStaty;
class CommonEnemyVigilance;
class CommonEnemyCharge;
class CommonEnemyAttack;

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

	/*
	*	��Ԃ�؂�ւ���
	*
	*	@param	(nextState)	���̏��
	*/
	void ChangeState(ICommonEnemy* nextState)
	{
		//���݂̏�Ԃ̏I������
		m_state->Finalize();

		//���̏�Ԃ�؂�ւ���
		m_state = nextState;

		//���̏�Ԃ̏���������
		m_state->Initialize();
	}

private:

	//		���
	ICommonEnemy* m_state;

	//		�ҋ@���
	std::unique_ptr<CommonEnemyStay> m_stay;

	//		�x�����
	std::unique_ptr<CommonEnemyVigilance> m_vigilance;

	//		�`���[�W���
	std::unique_ptr<CommonEnemyCharge> m_charge;

	//		�U�����
	std::unique_ptr<CommonEnemyAttack> m_attack;
public:

	/*
	*	�ҋ@��Ԃ��󂯎��
	*
	*	@return �ҋ@��Ԃ̃C���X�^���X�̃|�C���^
	*/
	CommonEnemyStay* GetStay() { return m_stay.get(); }

	/*
	*	�x����Ԃ��󂯎��
	*
	*	@return �ҋ@��Ԃ̃C���X�^���X�̃|�C���^
	*/
	CommonEnemyVigilance* GetVigilance() { return m_vigilance.get(); }

	/*
	*	�`���[�W��Ԃ��󂯎��
	*
	*	@return �`���[�W��Ԃ̃C���X�^���X�̃|�C���^
	*/
	CommonEnemyCharge* GetCharge() { return m_charge.get(); }

	/*
	*	�U����Ԃ��󂯎��
	*
	*	@return �U����Ԃ̃C���X�^���X�̃|�C���^
	*/
	CommonEnemyAttack* GetAttack() { return m_attack.get(); }

private:

	//		���f��
	std::unique_ptr<DirectX::Model> m_model;

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
public:

	/*
	*	���f�����󂯎��
	*
	*	@return ���f��
	*/
	DirectX::Model* GetModel() { return m_model.get(); }

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