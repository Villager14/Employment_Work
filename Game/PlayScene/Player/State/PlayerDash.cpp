/*
* @file		PlayerDash.cpp
* @brief	プレイヤーのダッシュ
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
	//		移動方向
	m_direction = m_player->MoveDirection(m_player->GetInformation()->GetDirection());

	//		高さの取得
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;

	//		落下時間
	m_player->GetInformation()->SetFallTime(0.0f);

	//		ダッシュをできない状態にする
	m_player->GetInformation()->SetDashJudgement(false);
}

void PlayerDash::Update()
{
	//		移動処理
	MoveProcessing();

	//		重力処理
	m_player->Gravity();
}

void PlayerDash::Move()
{
	//		壁メッシュの当たり判定
	m_player->WallMeshHitJudgement();

	//		床に当たっているか
	m_player->FloorMeshHitJudgement();

	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());


	//		立つ処理
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetPosition().y + m_player->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerDash::Render()
{
}

void PlayerDash::Finalize()
{
	m_acceraration = 0.0f;

	m_deceleration = 0.0f;

	//		高さ変動時間の初期化
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

	//		初期速度からLerpを使い加速していく
	float speed = Library::Lerp(m_player->GetInformation()->GetAcceleration().Length(), DASH_MAX_SPEED, move);

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		(m_direction * speed) *
		LibrarySingleton::GetInstance()->GetElpsedTime());

	//		加速度の設定
	m_player->GetInformation()->SetAcceleration(m_direction * speed);
}

void PlayerDash::Deceleration()
{
	//		経過時間　＊　1.5倍速
	m_deceleration += LibrarySingleton::GetInstance()->GetElpsedTime()
		* 3.0f;

	//		一以上にならないようにする
	m_deceleration = Library::Clamp(m_deceleration, 0.0f, 1.0f);

	//		イージング関数(easeInExpo)
	float move = 0.0f;

	if (m_deceleration != 0)
	{
		move = pow(2.0f, 10.0f * m_deceleration - 10.0f);
	}

	//		初期速度からLerpを使い加速していく
	float speed = Library::Lerp(DASH_MAX_SPEED, m_player->GetWalkSpeed(), move);

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		(m_direction * speed) *
		LibrarySingleton::GetInstance()->GetElpsedTime());

	//		加速度の設定
	m_player->GetInformation()->SetAcceleration(m_direction * speed);
}

void PlayerDash::ChangeStateJudgement()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		壁歩き状態かどうか
	m_player->WallWalkJudgement();

	if (m_deceleration >= 1.0f)
	{
		//		状態を遷移する(歩き)
		m_player->ChangeState(m_player->GetWalkState());
	}
}
