/*
* @file		PlayerDeath.cpp
* @brief	�v���C���[�̎��S���
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "PlayerDeath.h"

#include "../Player.h"

PlayerDeath::PlayerDeath(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f),
	m_slowTime(0.0f),
	m_firstGravity(0.0f)
{
}

PlayerDeath::~PlayerDeath()
{
}

void PlayerDeath::Initialize()
{
	//		�����̎擾
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;

	//		�����x���󂯎��
	m_firstAcceleration = m_player->GetInformation()->GetAcceleration();

	//		�d�͂��󂯎��
	m_firstGravity = m_player->GetInformation()->GetGravity();
}

void PlayerDeath::Update()
{
	//		����
	Deceleration();
}

void PlayerDeath::Move()
{
	//		�ǃ��b�V���̓����蔻��
	m_player->WallMeshHitJudgement();

	//		���ɓ������Ă��邩
	m_player->FloorMeshHitJudgement();
	
	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerDeath::Render()
{
}

void PlayerDeath::Finalize()
{
	m_time = 0.0f;

	m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3::Zero);

	//		�����ϓ����Ԃ̏�����
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		�v���C���[�̍��W�����Z�b�g����
	m_player->GetInformation()->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_player->GetInformation()->SetPlanPosition({ 0.0f, 0.0f, 0.0f });

	//		������
	m_player->GetInformation()->SetPlayerHeight({m_player->GetInformation()->GetPosition().x,
												 m_player->GetInformation()->GetPosition().y + 7.0f,
												 m_player->GetInformation()->GetPosition().z});
	m_player->GetInformation()->SetGravity(0.0f);
	m_player->GetInformation()->SetFallTime(0.0f);
}

void PlayerDeath::Deceleration()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 1.0f;

	if (m_time >= 1.0f) return;

	m_slowTime = 1.0f - pow(1 - m_time, 4.0f);

	DirectX::SimpleMath::Vector3 acceleration = DirectX::SimpleMath::Vector3::Lerp
	(m_firstAcceleration, DirectX::SimpleMath::Vector3::Zero, m_slowTime);

	m_player->GetInformation()->SetAcceleration(acceleration);

	//		���x�ƈړ��ʂ��v�Z����
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration()
		* LibrarySingleton::GetInstance()->GetElpsedTime());

	float gravity = Library::Lerp(m_firstGravity, 0.0f, m_slowTime);

	DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPlanPosition();

	position.y -= gravity * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_player->GetInformation()->SetPlanPosition(position);
}

void PlayerDeath::ChangeStateJudgement()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�}�E�X�̎擾
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Space�܂��͍��N���b�N���������ꍇ��������
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		������Ԃɂ���
		m_player->ChangeState(m_player->GetStayState());
	}
}
