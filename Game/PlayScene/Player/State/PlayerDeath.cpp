/*
* @file		PlayerDeath.cpp
* @brief	プレイヤーの死亡状態
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
	//		高さの取得
	m_firstHeight = m_player->GetPlayerHeight().y;

	//		加速度を受け取る
	m_firstAcceleration = m_player->GetAcceleration();

	//		重力を受け取る
	m_firstGravity = m_player->GetGravity();
}

void PlayerDeath::Update()
{
	//		減速
	Deceleration();
}

void PlayerDeath::Move()
{
	//		壁メッシュの当たり判定
	m_player->WallMeshHitJudgement();

	//		床に当たっているか
	m_player->FloorMeshHitJudgement();
	
	//		移動予定座標からプレイヤー座標に代入する
	m_player->SetPosition(m_player->GetPlanPosition());

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerDeath::Render()
{
}

void PlayerDeath::Finalize()
{
	m_time = 0.0f;

	m_player->SetDirection(DirectX::SimpleMath::Vector3::Zero);

	//		高さ変動時間の初期化
	m_player->SetHeightTime(0.0f);

	//		プレイヤーの座標をリセットする
	m_player->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_player->SetPlanPosition({ 0.0f, 0.0f, 0.0f });

	//		立つ処理
	m_player->SetPlayerHeight({m_player->GetPosition().x, m_player->GetPosition().y + 7.0f, m_player->GetPosition().z});
	m_player->SetGravity(0.0f);
	m_player->SetFallTime(0.0f);
}

void PlayerDeath::Deceleration()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 1.0f;

	if (m_time >= 1.0f) return;

	m_slowTime = 1.0f - pow(1 - m_time, 4.0f);

	DirectX::SimpleMath::Vector3 acceleration = DirectX::SimpleMath::Vector3::Lerp
	(m_firstAcceleration, DirectX::SimpleMath::Vector3::Zero, m_slowTime);

	m_player->SetAcceleration(acceleration);

	//		速度と移動量を計算する
	m_player->SetPlanPosition(m_player->GetPosition() +
		m_player->GetAcceleration()
		* LibrarySingleton::GetInstance()->GetElpsedTime());

	float gravity = Library::Lerp(m_firstGravity, 0.0f, m_slowTime);

	DirectX::SimpleMath::Vector3 position = m_player->GetPlanPosition();

	position.y -= gravity * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_player->SetPlanPosition(position);
}

void PlayerDeath::ChangeStateJudgement()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		マウスの取得
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Spaceまたは左クリックを押した場合復活する
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		復活状態にする
		m_player->ChangeState(m_player->GetStayState());
	}
}
