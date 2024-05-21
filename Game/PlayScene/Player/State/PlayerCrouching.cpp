/*
* @file		PlayerCrouching.cpp
* @brief	�v���C���[�̂��Ⴊ�ݏ��
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerCrouching.h"

#include "../Player.h"

PlayerCrouching::PlayerCrouching(Player* player)
	:
	m_player(player),
	m_firstHeight(0.0f),
	m_keyInputJudgement(false)
{
}

PlayerCrouching::~PlayerCrouching()
{
}

void PlayerCrouching::Initialize()
{
	//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetPlayerHeight().y;
}

void PlayerCrouching::Update()
{
	//		�ړ�����
	MoveProcessing();

	//		���b�V���Ɠ����������̏���
	m_player->Gravity();

}

void PlayerCrouching::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->FloorMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->SetPosition(m_player->GetPlanPosition());

	//		���Ⴊ�ݏ���
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetPosition().y + COURCHING_HEIGHT, 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerCrouching::Render()
{
}

void PlayerCrouching::Finalize()
{
	//		�����ϓ����Ԃ̏�����
	m_player->SetHeightTime(0.0f);
}

void PlayerCrouching::MoveProcessing()
{
	//		�L�[�������Ă��邩�ǂ���
	m_keyInputJudgement = false;

	//		�ړ��������
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	//		�ړ�����������󂯎��
	direction = m_player->Direction(&m_keyInputJudgement);

	//		���K��
	direction.Normalize();

	//		�L�[��������Ă����Ԃ̏ꍇ
	if (m_keyInputJudgement)
	{
		//		�ړ����������ݒ肷��
		m_player->SetDirection(direction);

		//		���x����
		SpeedProcessing();
	}
	else
	{
		m_player->SetAcceleration(m_player->GetAcceleration() * 0.8f);
	}

	//		���W�ɐݒ肷��
	m_player->SetPlanPosition(m_player->GetPosition() +
		m_player->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerCrouching::ChangeStateJudgement()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�L�[�{�[�h�X�e�[�g�̎擾
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		�L�[�𗣂����ꍇ
	if (keyboard.IsKeyReleased(DirectX::Keyboard::LeftControl))
	{
		//		�ړ��L�[��������Ă���ꍇ
		if (keyboardState.IsKeyDown(DirectX::Keyboard::W) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::A) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::S) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::D))
		{
			//		��Ԃ�J�ڂ���(�������)
			m_player->ChangeState(m_player->GetWalkState());
		}
		else
		{
			//		��Ԃ�J�ڂ���(�ҋ@���)
			m_player->ChangeState(m_player->GetStayState());
		}
	}
}

void PlayerCrouching::SpeedProcessing()
{
	//		�����x���󂯎��
	DirectX::SimpleMath::Vector3 accelaration = m_player->GetAcceleration();

	//		�����x�̏���
	accelaration += m_player->MoveDirection(m_player->GetDirection())
		* 2000.0f * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		���������̑�����葁���Ȃ����ꍇ
	if (accelaration.Length() > m_player->GetCrouchingSpeed())
	{
		//		���K��
		accelaration.Normalize();

		//		�����x�ɕ����̑������|����
		accelaration *= m_player->GetCrouchingSpeed();
	}

	//		�����x��ݒ肷��
	m_player->SetAcceleration(accelaration);

	//		���W�ɐݒ肷��
	m_player->SetPlanPosition(m_player->GetPosition() +
		m_player->GetAcceleration() * LibrarySingleton::GetInstance()->GetElpsedTime());

}