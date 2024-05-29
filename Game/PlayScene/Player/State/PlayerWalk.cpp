/*
* @file		PlayerWalk.cpp
* @brief	�v���C���[�̕������
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerWalk.h"

#include "../Player.h"

PlayerWalk::PlayerWalk(Player* player)
	:
	m_player(player),
	m_keyInputJudgement(false),
	m_firstHeight(0.0f),
	m_speed(0.0f)
{
}

PlayerWalk::~PlayerWalk()
{
}

void PlayerWalk::Initialize()
{
	//		�����̎擾
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;

	//		���x���󂯎��
	m_speed = m_player->GetInformation()->GetAcceleration().Length();
}

void PlayerWalk::Update()
{
	//		�ړ�����
	MoveProcessing();

	//		���b�V���Ɠ����������̏���
	m_player->Gravity();
}

void PlayerWalk::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->FloorMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());
	
	//		������
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetPosition().y + m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerWalk::Render()
{
}

void PlayerWalk::Finalize()
{
	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_speed = 0.0f;
}

void PlayerWalk::MoveProcessing()
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
		m_player->GetInformation()->SetDirection(direction);
	}

	//		�����x���󂯎��
	DirectX::SimpleMath::Vector3 accelaration = m_player->GetInformation()->GetAcceleration();

	//		�����x�̏���
	accelaration += m_player->MoveDirection(m_player->GetInformation()->GetDirection())
		* ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_speed -= 40.0f * LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_speed < m_player->GetInformation()->GetWalkSpeed())
	{
		m_speed = m_player->GetInformation()->GetWalkSpeed();
	}

	if (accelaration.Length() > m_speed)
	{
		//		���K��
		accelaration.Normalize();

		//		�����x�ɕ����̑������|����
		accelaration *= m_speed;
	}

	/*
	//		���������̑�����葁���Ȃ����ꍇ
	if (accelaration.Length() > m_player->GetWalkSpeed())
	{
		float speed = accelaration.Length();

		speed -= ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

		accelaration.Normalize();

		accelaration *= speed;

		if (accelaration.Length() < m_player->GetWalkSpeed())
		{
			//		���K��
			accelaration.Normalize();

			//		�����x�ɕ����̑������|����
			accelaration *= m_player->GetWalkSpeed();
		}
	}
	*/

	//		�����x��ݒ肷��
	m_player->GetInformation()->SetAcceleration(accelaration);

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration() * LibrarySingleton::GetInstance()->GetElpsedTime());
	
}

void PlayerWalk::ChangeStateJudgement()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		�L�[��������Ă��Ȃ��ꍇ
	if (!m_keyInputJudgement)
	{
		//		��Ԃ�J�ڂ���(�ҋ@���)
		m_player->ChangeState(m_player->GetStayState());
	}

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	DirectX::Keyboard::State keyState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();
	
	//		space�ŃW�����v
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space))
	{
		//		��Ԃ�؂�ւ���(�W�����v)
		m_player->ChangeState(m_player->GetJumpState());
	}

	//		�S�[�������Ă��邩�ǂ���
	if (m_player->GetGameManager()->GetGoalJudgement())
	{
		//		��Ԃ�؂�ւ���i�S�[���j
		m_player->ChangeState(m_player->GetGoalState());
	}

	//		Control�ł��Ⴊ��
	if (keyState.IsKeyDown(DirectX::Keyboard::LeftControl))
	{
		if (m_player->GetInformation()->GetAcceleration().Length() < m_player->GetInformation()->GetCrouchingSpeed())
		{
			//		��Ԃ�؂�ւ���(����)
			m_player->ChangeState(m_player->GetCrouchingState());
		}
		else
		{
			//		��Ԃ�؂�ւ���(�X���C�f�B���O)
			m_player->ChangeState(m_player->GetSlidingState());
		}
	}

	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift))
	{
		//		�_�b�V���ł��邩�ǂ���
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		��Ԃ�؂�ւ���(�_�b�V��)
			m_player->ChangeState(m_player->GetDashState());
		}
	}
}
