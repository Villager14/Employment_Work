/*
* @file		PlayerWire.cpp
* @brief	�v���C���[�̃��C���[���
* @author	Morita
* @date		2024/05/13
*/

#include "pch.h"

#include "PlayerWire.h"

#include "../Player.h"

PlayerWire::PlayerWire(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f),
	m_speed(0.0f),
	m_fallJudgement(false),
	m_length(0.0f),
	m_floorHitJudgement(false),
	m_wallHitJudgement(false),
	m_firstSpeed(0.0f)
{
}

PlayerWire::~PlayerWire()
{
}

void PlayerWire::Initialize()
{
	//		�����̎擾
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;

	//		�ړ�����
	m_direction = m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition();

	m_direction.Normalize();

	//		����
	m_length = (m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition()).Length();

	//		�������Ԃ��O�ɂ���
	m_player->GetInformation()->SetFallTime(0.0f);
}

void PlayerWire::Update()
{
	MoveProcessing();

	m_player->Gravity(true);
}

void PlayerWire::Move()
{
	//		�ǃ��b�V���̓����蔻��
	if (m_player->WallMeshHitJudgement())
	{
		if (m_fallJudgement)m_wallHitJudgement = true;
	}

	//		���ɓ������Ă��邩
	if (m_player->FloorMeshHitJudgement())
	{
		if (m_fallJudgement)m_floorHitJudgement = true;
	}
	
	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		������Ԃɂ��邩�ǂ���
	FallJudgement();

	//		������
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetPosition().y + m_player->GetStandingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerWire::Render()
{
}

void PlayerWire::Finalize()
{
	m_time = 0.0f;

	m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3::Zero);

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_wallHitJudgement = false;

	m_floorHitJudgement = false;

	m_fallJudgement = 0.0f;
}

void PlayerWire::MoveProcessing()
{
	//		������Ԃ����f����
	if (!m_fallJudgement) AttractProcess();
	else FallProcess();

	DirectX::SimpleMath::Vector3 velocity = m_direction * m_speed;

	m_player->GetInformation()->SetAcceleration(velocity);

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() + m_direction *
		m_speed * LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerWire::ChangeStateJudgement()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�L�[�{�[�h�X�e�[�g�̎擾
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift))
	{
		//		�_�b�V���ł��邩�ǂ���
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		��Ԃ�؂�ւ���(�_�b�V��)
			m_player->ChangeState(m_player->GetDashState());
		}
	}

	if (m_floorHitJudgement)
	{
		//		�ړ��L�[���������Ƃ�
		if (keyboardState.IsKeyDown(DirectX::Keyboard::W) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::A) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::S) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::D))
		{
			//		��Ԃ�؂�ւ���i����)
			m_player->ChangeState(m_player->GetWalkState());
		}
		else
		{
			//		��Ԃ�؂�ւ���i�ҋ@)
			m_player->ChangeState(m_player->GetWalkState());
		}
	}

	if (m_wallHitJudgement)
	{
		DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

		acceleation.Normalize();

		float dot = m_player->GetCollitionInformation()->GetMeshWallNormalize()[0].Dot(acceleation);

		//		�v���C���[�����̊p�x�������Ă���ꍇ����������
		if (dot <= -0.2f && dot >= -0.9f)
		{
			//		�@����������
			m_player->GetPlayerInformationCollition()->SetWallWalkNormalize(
				(m_player->GetCollitionInformation()->GetMeshWallNormalize()[0]));

			//		��Ԃ�؂�ւ���(�Ǖ������)
			m_player->ChangeState(m_player->GetWallWalkState());
		}	
	}
}

void PlayerWire::AttractProcess()
{
	//		���݂̋���
	float nowLenght = (m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition()).Length();

	//		����
	float ratio = nowLenght / m_length;

	m_speed = Library::Lerp(50, 200, ratio);
}

void PlayerWire::FallProcess()
{
	//		�L�[�������Ă��邩�ǂ���
	bool keyInputJudgement = false;

	//		�ړ��������
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	//		�ړ�����������󂯎��
	direction = m_player->Direction(&keyInputJudgement);

	//		���K��
	direction.Normalize();

	//		�ړ����������ǉ�����
	m_direction += m_player->MoveDirection(direction) * 0.2f * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		���K��
	m_direction.Normalize();
}

void PlayerWire::FallJudgement()
{
	//		�v���C���[���猩�����C���[�I�u�W�F�N�g�̕��������߂�
	DirectX::SimpleMath::Vector3 direction = m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition();

	//		���K��
	direction.Normalize();

	//		����
	float dot2 = m_direction.Dot(direction);

	//		�v���C���[�̈ړ������ƌ��݂̕������ʂ̏ꍇ���������ɂ���
	if (dot2 < 0.0f)
	{
		m_fallJudgement = true;

		m_time = 0.0f;
	}
}
