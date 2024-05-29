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
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;

	//		速度を受け取る
	m_speed = m_player->GetInformation()->GetAcceleration().Length();
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
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());
	
	//		立つ処理
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetPosition().y + m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerWalk::Render()
{
}

void PlayerWalk::Finalize()
{
	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

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
		m_player->GetInformation()->SetDirection(direction);
	}

	//		加速度を受け取る
	DirectX::SimpleMath::Vector3 accelaration = m_player->GetInformation()->GetAcceleration();

	//		加速度の処理
	accelaration += m_player->MoveDirection(m_player->GetInformation()->GetDirection())
		* ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_speed -= 40.0f * LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_speed < m_player->GetInformation()->GetWalkSpeed())
	{
		m_speed = m_player->GetInformation()->GetWalkSpeed();
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
	m_player->GetInformation()->SetAcceleration(accelaration);

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration() * LibrarySingleton::GetInstance()->GetElpsedTime());
	
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

	//		ゴールをしているかどうか
	if (m_player->GetGameManager()->GetGoalJudgement())
	{
		//		状態を切り替える（ゴール）
		m_player->ChangeState(m_player->GetGoalState());
	}

	//		Controlでしゃがみ
	if (keyState.IsKeyDown(DirectX::Keyboard::LeftControl))
	{
		if (m_player->GetInformation()->GetAcceleration().Length() < m_player->GetInformation()->GetCrouchingSpeed())
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
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		状態を切り替える(ダッシュ)
			m_player->ChangeState(m_player->GetDashState());
		}
	}
}
