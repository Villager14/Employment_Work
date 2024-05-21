/*
* @file		PlayerAttack.cpp
* @brief	�v���C���[�̍U�����
* @author	Morita
* @date		2024/04/30
*/

#include "pch.h"

#include "PlayerAttack.h"

#include "../Player.h"

PlayerAttack::PlayerAttack(Player* player)
	:
	m_player(player),
	m_time(0.0f)
{
}

PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Initialize()
{
}

void PlayerAttack::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();
}

void PlayerAttack::Move()
{

	if (m_time > 1.0f)
	{
		//		�U�����I������
		m_player->SetAttackJudgement(false);
	}
}

void PlayerAttack::Render()
{
}

void PlayerAttack::Finalize()
{
	m_player->SetDirection(DirectX::SimpleMath::Vector3::Zero);
}

void PlayerAttack::Deceleration()
{

}