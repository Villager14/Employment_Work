/*
* @file		PlayerStart.cpp
* @brief	プレイヤーのスタート状態
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "PlayerStart.h"

#include "../Player.h"

PlayerStart::PlayerStart(Player* player)
	:
	m_player(player)
{
}

PlayerStart::~PlayerStart()
{
}

void PlayerStart::Initialize()
{
}

void PlayerStart::Update()
{
}

void PlayerStart::Move()
{
	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerStart::Render()
{
}

void PlayerStart::Finalize()
{
}

void PlayerStart::ChangeStateJudgement()
{
	//		カメラの演出が終わったら
	if (m_player->GetCameraInformation()->GetStartJudgement())
	{
		//		状態を遷移する（待機状態）
		m_player->ChangeState(m_player->GetStayState());
	}
}
