/*
* @file		PlayerWalk.cpp
* @brief	プレイヤーの歩き状態
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerWalk.h"

#include "../Player.h"

PlayerWalk::PlayerWalk(Player* player)
	:
	m_player(player),
	m_keyInputJudgement(false),
	m_firstHeight(0.0f),
	m_speed(0.0f)
{
}

PlayerWalk::~PlayerWalk()
{
}

void PlayerWalk::Initialize()
{
	//		高さの取得
	m_firstHeight = m_player->GetPlayerHeight().y;

	//		速度を受け取る
	m_speed = m_player->GetAcceleration().Length();
}

void PlayerWalk::Update()
{
	//		移動処理
	MoveProcessing();

	//		メッシュと当たった時の処理
	m_player->Gravity();
}

void PlayerWalk::Move()
{
	//		壁メッシュの当たり判定
	m_player->WallMeshHitJudgement();

	//		床に当たっているか
	m_player->FloorMeshHitJudgement();

	//		移動予定座標からプレイヤー座標に代入する
	m_player->SetPosition(m_player->GetPlanPosition());
	
	//		立つ処理
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetPosition().y + m_player->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerWalk::Render()
{
}

void PlayerWalk::Finalize()
{
	//		高さ変動時間の初期化
	m_player->SetHeightTime(0.0f);

	m_speed = 0.0f;
}

void PlayerWalk::MoveProcessing()
{
	//		キーを押しているかどうか
	m_keyInputJudgement = false;

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	//		移動する方向を受け取る
	direction = m_player->Direction(&m_keyInputJudgement);

	//		正規化
	direction.Normalize();

	//		キーが押されている状態の場合
	if (m_keyInputJudgement)
	{
		//		移動する方向を設定する
		m_player->SetDirection(direction);
	}

	//		加速度を受け取る
	DirectX::SimpleMath::Vector3 accelaration = m_player->GetAcceleration();

	//		加速度の処理
	accelaration += m_player->MoveDirection(m_player->GetDirection())
		* ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_speed -= 40.0f * LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_speed < m_player->GetWalkSpeed())
	{
		m_speed = m_player->GetWalkSpeed();
	}

	if (accelaration.Length() > m_speed)
	{
		//		正規化
		accelaration.Normalize();

		//		加速度に歩きの速さを掛ける
		accelaration *= m_speed;
	}

	/*
	//		もし歩きの速さより早くなった場合
	if (accelaration.Length() > m_player->GetWalkSpeed())
	{
		float speed = accelaration.Length();

		speed -= ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

		accelaration.Normalize();

		accelaration *= speed;

		if (accelaration.Length() < m_player->GetWalkSpeed())
		{
			//		正規化
			accelaration.Normalize();

			//		加速度に歩きの速さを掛ける
			accelaration *= m_player->GetWalkSpeed();
		}
	}
	*/

	//		加速度を設定する
	m_player->SetAcceleration(accelaration);

	//		座標に設定する
	m_player->SetPlanPosition(m_player->GetPosition() + 
		m_player->GetAcceleration() * LibrarySingleton::GetInstance()->GetElpsedTime());
	
}

void PlayerWalk::ChangeStateJudgement()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		キーが押されていない場合
	if (!m_keyInputJudgement)
	{
		//		状態を遷移する(待機状態)
		m_player->ChangeState(m_player->GetStayState());
	}

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	DirectX::Keyboard::State keyState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();
	
	//		spaceでジャンプ
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space))
	{
		//		状態を切り替える(ジャンプ)
		m_player->ChangeState(m_player->GetJumpState());
	}

	//		Controlでしゃがみ
	if (keyState.IsKeyDown(DirectX::Keyboard::LeftControl))
	{
		if (m_player->GetAcceleration().Length() < m_player->GetCrouchingSpeed())
		{
			//		状態を切り替える(歩き)
			m_player->ChangeState(m_player->GetCrouchingState());
		}
		else
		{
			//		状態を切り替える(スライディング)
			m_player->ChangeState(m_player->GetSlidingState());
		}
	}

	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift))
	{
		//		ダッシュできるかどうか
		if (m_player->GetDashJudgement())
		{
			//		状態を切り替える(ダッシュ)
			m_player->ChangeState(m_player->GetDashState());
		}
	}
}
