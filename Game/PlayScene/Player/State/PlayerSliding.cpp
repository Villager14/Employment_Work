/*
* @file		PlayerSliding.cpp
* @brief	�v���C���[�̃X���C�f�B���O
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerSliding.h"

#include "../Player.h"

PlayerSliding::PlayerSliding(Player* player)
	:
	m_player(player),
	m_keyInputJudgement(false),
	m_firstSpeed(0.0f),
	m_speed(0.0f),
	m_slopeJudgement(false),
	m_decelerationSpeed(0.0f)
{
}

PlayerSliding::~PlayerSliding()
{
}

void PlayerSliding::Initialize()
{
	//		�����̎擾
	m_firstHeight = m_player->GetPlayerHeight().y;

	//		�����̑��x
	m_speed = m_player->GetAcceleration().Length() + INTIAL_VELOCITY;

	//		�������x
	m_decelerationSpeed = m_player->GetAcceleration().Length() / 3.0f * 2.0f;

	//		
	SlopeJudgement();

	//		�X���C�f�B���O�����Ă����Ԃɂ���
	m_player->GetPlayerInformationCollition()->SetSlidingJudgement(true);
}

void PlayerSliding::Update()
{

	//		�ړ�����
	MoveProcessing();

	//		���b�V���Ɠ����������̏���
	m_player->Gravity();

}

void PlayerSliding::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->FloorMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->SetPosition(m_player->GetPlanPosition());

	//		������
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetPosition().y + COURCHING_HEIGHT, 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerSliding::Render()
{
	//		���x
	LibrarySingleton::GetInstance()->DebugFont(L"Speed", m_slopeJudgement, 0, 150);
}

void PlayerSliding::Finalize()
{
	//		�����ϓ����Ԃ̏�����
	m_player->SetHeightTime(0.0f);

	m_firstSpeed = 0.0f;

	m_speed = 0.0f;

	m_slopeJudgement = false;

	//		�X���C�f�B���O�����Ă����Ԃɂ���
	m_player->GetPlayerInformationCollition()->SetSlidingJudgement(false);
}

void PlayerSliding::MoveProcessing()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		���ݍ₩�ǂ���
	SlopeJudgement();

	if (m_slopeJudgement)
	{
		//		�����x���󂯎��
		DirectX::SimpleMath::Vector3 m_acceleration = m_player->GetAcceleration();

		m_acceleration.x += m_slidingVelocity.x * SLIDING_ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();
		m_acceleration.z += m_slidingVelocity.y * SLIDING_ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

		m_player->SetAcceleration(m_acceleration);

		//		���x��ݒ肷��
		m_speed = m_player->GetAcceleration().Length();

		//		�������x
		m_decelerationSpeed = m_player->GetAcceleration().Length() * 1.5f;

		//		���W�ɐݒ肷��
		m_player->SetPlanPosition(m_player->GetPosition() +
			m_player->GetAcceleration() *
			LibrarySingleton::GetInstance()->GetElpsedTime());

	}
	else
	{
		//		���x��x������
		m_speed -= m_decelerationSpeed *
			LibrarySingleton::GetInstance()->GetElpsedTime();

		//		�����x���󂯎��
		DirectX::SimpleMath::Vector3 m_acceleration = m_player->GetAcceleration();

		//		���������𐳋K��
		m_acceleration.Normalize();

		//		���x���|����
		m_acceleration *= m_speed;

		//		�����x��ݒ肷��
		m_player->SetAcceleration(m_acceleration);

		//		���W�ɐݒ肷��
		m_player->SetPlanPosition(m_player->GetPosition() +
			m_player->GetAcceleration() *
			LibrarySingleton::GetInstance()->GetElpsedTime());
	}
}

void PlayerSliding::ChangeStateJudgement()
{
	DirectX::Keyboard::State keyState =
		LibrarySingleton::GetInstance()->
		GetKeyboardStateTracker()->GetLastState();

	if (m_player->GetAcceleration().Length() <= 10.0f)
	{
		//		��Ԃ�J�ڂ���(���Ⴊ�ݏ��)
		m_player->ChangeState(m_player->GetCrouchingState());
	}

	//		Lcontrol�𗣂����ꍇ
	if (keyState.IsKeyUp(DirectX::Keyboard::LeftControl))
	{
		//		��Ԃ�J�ڂ���(�ړ����)
		m_player->ChangeState(m_player->GetWalkState());
	}

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		space�ŃW�����v
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space))
	{
		//		��Ԃ�؂�ւ���(���Ⴊ��)
		m_player->ChangeState(m_player->GetJumpState());
	}
}

void PlayerSliding::SlopeJudgement()
{
	//		�������Ă��鏰�̖@�������邩�ǂ���
	if (m_player->GetCollitionInformation()->GetFloorMeshHitNormalize().size() != 1)
	{
		m_slopeJudgement = false;

		return;
	}

	//		������̃x�N�g���Ə��̖@���̓��ς����
	float dot = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).
		Dot(m_player->GetCollitionInformation()->GetFloorMeshHitNormalize()[0]);

	//		��Ɣ��肷��p�x���ǂ������f����
	if (dot >= 1.0f && dot < 0.2f)
	{
		m_slopeJudgement = false;

		return;
	}

	//		�ړ��������󂯎��
	DirectX::SimpleMath::Vector2 acc2 = { m_player->GetAcceleration().x, m_player->GetAcceleration().z };

	//		��̕������v�Z����
	DirectX::SimpleMath::Vector3 downhill = m_player->GetCollitionInformation()->GetFloorMeshHitNormalize()[0]
											- DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

	//		���������񎟌��ɂ���
	m_slidingVelocity = { downhill.x, downhill.z };

	//		���K��
	m_slidingVelocity.Normalize();

	//		���ς�
	if (m_slidingVelocity.Dot(acc2) > 0.8f)
	{
		//		���菈��
		m_slopeJudgement = true;

		return;
	}

	m_slopeJudgement = false;
}
