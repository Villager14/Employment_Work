/*
* @file		PlayerGoal.h
* @brief	プレイヤーゴール状態
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "PlayerGoal.h"

#include "../Player.h"

PlayerGoal::PlayerGoal(Player* player)
	:
	m_player(player)
{
}

PlayerGoal::~PlayerGoal()
{
}

void PlayerGoal::Initialize()
{
	m_player->GetGameManager()->SetEndJudgement(true);
}

void PlayerGoal::Update()
{
}

void PlayerGoal::Move()
{
}

void PlayerGoal::Render()
{
}

void PlayerGoal::Finalize()
{
}
