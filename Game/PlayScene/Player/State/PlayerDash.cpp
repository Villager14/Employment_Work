/*
* @file		PlayerDash.cpp
* @brief	�v���C���[�̃_�b�V��
* @author	Morita
* @date		2024/04/29
*/

#include "pch.h"

#include "PlayerDash.h"

#include "../Player.h"

PlayerDash::PlayerDash(Player* player)
	:
	m_player(player),
	m_acceraration(0.0f),
	m_keyInputJudgement(false),
	m_firstHeight(0.0f),
	m_deceleration(0.0f)
{
}

PlayerDash::~PlayerDash()
{
}

void PlayerDash::Initialize()
{
	//		�ړ�����
	m_direction = m_player->MoveDirection(m_player->GetInformation()->GetDirection());

	//		�����̎擾
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;

	//		��������
	m_player->GetInformation()->SetFallTime(0.0f);

	//		�_�b�V�����ł��Ȃ���Ԃɂ���
	m_player->GetInformation()->SetDashJudgement(false);
}

void PlayerDash::Update()
{
	//		�ړ�����
	MoveProcessing();

	//		�d�͏���
	m_player->Gravity();
}

void PlayerDash::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->FloorMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());


	//		������
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetPosition().y + m_player->GetStandingHeight(), 3.0f);

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerDash::Render()
{
}

void PlayerDash::Finalize()
{
	m_acceraration = 0.0f;

	m_deceleration = 0.0f;

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);
}

void PlayerDash::MoveProcessing()
{
	if (m_acceraration < 1.0f) Acceratation();
	else Deceleration();
}

void PlayerDash::Acceratation()
{
	m_acceraration += LibrarySingleton::GetInstance()->GetElpsedTime()
		* 10.0f;

	float move = m_acceraration;

	//		�������x����Lerp���g���������Ă���
	float speed = Library::Lerp(m_player->GetInformation()->GetAcceleration().Length(), DASH_MAX_SPEED, move);

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		(m_direction * speed) *
		LibrarySingleton::GetInstance()->GetElpsedTime());

	//		�����x�̐ݒ�
	m_player->GetInformation()->SetAcceleration(m_direction * speed);
}

void PlayerDash::Deceleration()
{
	//		�o�ߎ��ԁ@���@1.5�{��
	m_deceleration += LibrarySingleton::GetInstance()->GetElpsedTime()
		* 3.0f;

	//		��ȏ�ɂȂ�Ȃ��悤�ɂ���
	m_deceleration = Library::Clamp(m_deceleration, 0.0f, 1.0f);

	//		�C�[�W���O�֐�(easeInExpo)
	float move = 0.0f;

	if (m_deceleration != 0)
	{
		move = pow(2.0f, 10.0f * m_deceleration - 10.0f);
	}

	//		�������x����Lerp���g���������Ă���
	float speed = Library::Lerp(DASH_MAX_SPEED, m_player->GetWalkSpeed(), move);

	//		���W�ɐݒ肷��
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		(m_direction * speed) *
		LibrarySingleton::GetInstance()->GetElpsedTime());

	//		�����x�̐ݒ�
	m_player->GetInformation()->SetAcceleration(m_direction * speed);
}

void PlayerDash::ChangeStateJudgement()
{
	//		���S���Ă��邩���f����
	m_player->DeathJudgement();

	//		�Ǖ�����Ԃ��ǂ���
	m_player->WallWalkJudgement();

	if (m_deceleration >= 1.0f)
	{
		//		��Ԃ�J�ڂ���(����)
		m_player->ChangeState(m_player->GetWalkState());
	}
}
