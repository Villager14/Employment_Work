/*
* @file		PlayerWalk.cpp
* @brief	プレイヤーの歩き状態
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerJump.h"

#include "../Player.h"

PlayerJump::PlayerJump(Player* player)
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

PlayerJump::~PlayerJump()
{
}

void PlayerJump::Initialize()
{
	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetPlayerHeight().y;

	//		現在の速度を受け取る
	m_nowSpeed = m_player->GetAcceleration().Length();

	//		カメラの回転量を受け取る
	m_cameraMatrix = DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(m_player->GetCameraAngle().x));

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

void PlayerJump::Update()
{
	//		ジャンプの処理
	Jump();

	//		移動処理
	MoveProcessing();

	//		重力処理
	m_player->Gravity();
}

void PlayerJump::Move()
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

void PlayerJump::Render()
{
}

void PlayerJump::Finalize()
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

void PlayerJump::MoveProcessing()
{
	
	//		キーを押しているかどうか
	m_keyInputJudgement = false;

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction = 
		DirectX::SimpleMath::Vector3::Zero;

	//		移動する方向を受け取る
	direction = m_player->Direction(&m_keyInputJudgement);

	if (m_keyInputJudgement && m_stopJump)
	{
		//		移動する方向を設定する
		m_player->SetDirection(direction);

		DirectX::SimpleMath::Vector3 acceleation = m_player->GetAcceleration();

		acceleation += DirectX::SimpleMath::Vector3::Transform(
			direction, m_cameraMatrix.Invert()) * 40.0f * LibrarySingleton::GetInstance()->GetElpsedTime();

		m_player->SetAcceleration(acceleation);

	}
	else if (!m_stopJump && m_keyInputJudgement)
	{
		//		移動する方向を設定する
		m_player->SetDirection(direction);

		DirectX::SimpleMath::Vector3 acceleation = m_player->GetAcceleration();

		acceleation += DirectX::SimpleMath::Vector3::Transform(
			direction, m_cameraMatrix.Invert()) * 60.0f * LibrarySingleton::GetInstance()->GetElpsedTime();
		
		if (acceleation.Length() > m_nowSpeed)
		{
			acceleation.Normalize();

			acceleation *= m_nowSpeed;
		}

		m_player->SetAcceleration(acceleation);
	}

	DirectX::SimpleMath::Vector3 position = m_player->GetPosition();

	position.y = m_player->GetPlanPosition().y;

	//		座標に設定する
	m_player->SetPlanPosition(position +
		m_player->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerJump::Jump()
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

void PlayerJump::ChangeStateJudgement()
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