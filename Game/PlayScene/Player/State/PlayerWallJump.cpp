/*
* @file		PlayerWallJump.cpp
* @brief	プレイヤーの壁ジャンプ
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "PlayerWallJump.h"

#include "../Player.h"

PlayerWallJump::PlayerWallJump(Player* player)
	:
	m_player(player),
	m_elapsedTime(0.0f),
	m_keyInputJudgement(false),
	m_firstHeight(0.0f),
	m_stopJump(false),
	m_rayprocessJudgement(false),
	m_rayHitJudgement(false),
	m_nowSpeed(0.0f)
{


}

PlayerWallJump::~PlayerWallJump()
{
}

void PlayerWallJump::Initialize()
{
	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetPlayerHeight().y;

	//		現在の速度を受け取る
	m_nowSpeed = m_player->GetAcceleration().Length();

	//		移動していないかどうか
	if (m_player->GetDirection().Length() < FLT_EPSILON)
	{
		//		移動していない
		m_stopJump = true;
	}
	//		移動している
	else m_stopJump = false;

	m_player->SetGravity(0.0f);
	m_player->SetFallTime(0.0f);

	//		ジャンプできない状態にする
	m_player->SetJumpJudgement(false);
}

void PlayerWallJump::Update()
{
	//		ジャンプの処理
	Jump();

	//		移動処理
	MoveProcessing();

	//		重力処理
	m_player->Gravity();
}

void PlayerWallJump::Move()
{
	//		壁メッシュの当たり判定
	m_player->WallMeshHitJudgement();

	//		レイの処理を行うかどうか
	if (m_rayprocessJudgement)
	{
		//		当たった場所がなければ処理をしない
		if (m_player->GetCollitionInformation()->GetFloorMeshHitPoint().size() != 0)
		{
			if (abs(m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y -
				m_player->GetPlanPosition().y) < 1.0f)
			{
				DirectX::SimpleMath::Vector3 position = m_player->GetPlanPosition();

				position.y = m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y;

				m_player->SetPlanPosition(position);

				m_player->SetFallTime(0.0f);

				m_rayHitJudgement = true;
			}
		}
	}

	m_player->SetPosition(m_player->GetPlanPosition());

	//		立つ処理
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetPosition().y + m_player->GetStandingHeight(), 3.0f);

	//		状態を遷移するかどうか
	ChangeStateJudgement();
}

void PlayerWallJump::Render()
{
}

void PlayerWallJump::Finalize()
{
	m_elapsedTime = 0.0f;

	//		高さ変動時間の初期化
	m_player->SetHeightTime(0.0f);

	//		高さ変動時間の初期化
	m_player->SetHeightTime(0.0f);

	m_rayprocessJudgement = false;

	m_rayHitJudgement = false;

	m_nowSpeed = 0.0f;
}

void PlayerWallJump::MoveProcessing()
{
	
	//		キーを押しているかどうか
	m_keyInputJudgement = false;

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction = 
		DirectX::SimpleMath::Vector3::Zero;

	//		移動する方向を受け取る
	direction = m_player->Direction(&m_keyInputJudgement);

	DirectX::SimpleMath::Vector3 position = m_player->GetPosition();

	position.y = m_player->GetPlanPosition().y;

	//		座標に設定する
	m_player->SetPlanPosition(position +
		m_player->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerWallJump::Jump()
{
	//		一秒以上は処理をしない
	if (m_elapsedTime >= 1.0f)
	{
		return;
	}

	//		ジャンプする時間
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * JUMP_SPEED;

	//		一以上にならないようにする
	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	//		プレイヤーの座標を受け取る
	DirectX::SimpleMath::Vector3 m_jumpPosition = m_player->GetPosition();

	//		easeInCirc
	float move = 1.0f - std::sqrt(1.0f - pow(m_elapsedTime, 2.0f));

	//		勢いを少しずつなくす
	float speed = Library::Lerp(JUMP_MAX_SPEED, JUMP_MIN_SPEED, move);

	//		移動量を計算する
	m_jumpPosition.y += speed * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		座標にセットする
	m_player->SetPlanPosition(m_jumpPosition);
}

void PlayerWallJump::ChangeStateJudgement()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		壁歩き状態かどうか
	m_player->WallWalkJudgement();

	//		一秒経過後処理をする
	if (m_elapsedTime >= 1.0f) { m_rayprocessJudgement = true; }

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		キーボードステートの取得
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		Shiftを押した場合
	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift))
	{		
		//		ダッシュできるかどうか
		if (m_player->GetDashJudgement())
		{
			//		状態を切り替える(ダッシュ)
			m_player->ChangeState(m_player->GetDashState());
		}
	}

	//		床に当たったら別の状態にする
	if (m_rayHitJudgement)
	{
		//		キーが押されていない場合
		if (!m_keyInputJudgement)
		{
			//		状態を遷移する(待機状態)
			m_player->ChangeState(m_player->GetStayState());
		}
		else if (keyboardState.IsKeyDown(DirectX::Keyboard::LeftControl))
		{
			//		状態を遷移する(スライディング)
			m_player->ChangeState(m_player->GetSlidingState());
		}
		else
		{
			//		状態を切り替える(歩き状態)
			m_player->ChangeState(m_player->GetWalkState());
		}

		return;
	}
}