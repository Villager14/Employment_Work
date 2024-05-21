/*
* @file		PlayerSliding.cpp
* @brief	プレイヤーのスライディング
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerSliding.h"

#include "../Player.h"

PlayerSliding::PlayerSliding(Player* player)
	:
	m_player(player),
	m_keyInputJudgement(false),
	m_firstSpeed(0.0f),
	m_speed(0.0f),
	m_slopeJudgement(false),
	m_decelerationSpeed(0.0f)
{
}

PlayerSliding::~PlayerSliding()
{
}

void PlayerSliding::Initialize()
{
	//		高さの取得
	m_firstHeight = m_player->GetPlayerHeight().y;

	//		初期の速度
	m_speed = m_player->GetAcceleration().Length() + INTIAL_VELOCITY;

	//		減速速度
	m_decelerationSpeed = m_player->GetAcceleration().Length() / 3.0f * 2.0f;

	//		
	SlopeJudgement();

	//		スライディングをしている状態にする
	m_player->GetPlayerInformationCollition()->SetSlidingJudgement(true);
}

void PlayerSliding::Update()
{

	//		移動処理
	MoveProcessing();

	//		メッシュと当たった時の処理
	m_player->Gravity();

}

void PlayerSliding::Move()
{
	//		壁メッシュの当たり判定
	m_player->WallMeshHitJudgement();

	//		床に当たっているか
	m_player->FloorMeshHitJudgement();

	//		移動予定座標からプレイヤー座標に代入する
	m_player->SetPosition(m_player->GetPlanPosition());

	//		立つ処理
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetPosition().y + COURCHING_HEIGHT, 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerSliding::Render()
{
	//		速度
	LibrarySingleton::GetInstance()->DebugFont(L"Speed", m_slopeJudgement, 0, 150);
}

void PlayerSliding::Finalize()
{
	//		高さ変動時間の初期化
	m_player->SetHeightTime(0.0f);

	m_firstSpeed = 0.0f;

	m_speed = 0.0f;

	m_slopeJudgement = false;

	//		スライディングをしている状態にする
	m_player->GetPlayerInformationCollition()->SetSlidingJudgement(false);
}

void PlayerSliding::MoveProcessing()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		現在坂かどうか
	SlopeJudgement();

	if (m_slopeJudgement)
	{
		//		加速度を受け取る
		DirectX::SimpleMath::Vector3 m_acceleration = m_player->GetAcceleration();

		m_acceleration.x += m_slidingVelocity.x * SLIDING_ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();
		m_acceleration.z += m_slidingVelocity.y * SLIDING_ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

		m_player->SetAcceleration(m_acceleration);

		//		速度を設定する
		m_speed = m_player->GetAcceleration().Length();

		//		減速速度
		m_decelerationSpeed = m_player->GetAcceleration().Length() * 1.5f;

		//		座標に設定する
		m_player->SetPlanPosition(m_player->GetPosition() +
			m_player->GetAcceleration() *
			LibrarySingleton::GetInstance()->GetElpsedTime());

	}
	else
	{
		//		速度を遅くする
		m_speed -= m_decelerationSpeed *
			LibrarySingleton::GetInstance()->GetElpsedTime();

		//		加速度を受け取る
		DirectX::SimpleMath::Vector3 m_acceleration = m_player->GetAcceleration();

		//		加速方向を正規化
		m_acceleration.Normalize();

		//		速度を掛ける
		m_acceleration *= m_speed;

		//		加速度を設定する
		m_player->SetAcceleration(m_acceleration);

		//		座標に設定する
		m_player->SetPlanPosition(m_player->GetPosition() +
			m_player->GetAcceleration() *
			LibrarySingleton::GetInstance()->GetElpsedTime());
	}
}

void PlayerSliding::ChangeStateJudgement()
{
	DirectX::Keyboard::State keyState =
		LibrarySingleton::GetInstance()->
		GetKeyboardStateTracker()->GetLastState();

	if (m_player->GetAcceleration().Length() <= 10.0f)
	{
		//		状態を遷移する(しゃがみ状態)
		m_player->ChangeState(m_player->GetCrouchingState());
	}

	//		Lcontrolを離した場合
	if (keyState.IsKeyUp(DirectX::Keyboard::LeftControl))
	{
		//		状態を遷移する(移動状態)
		m_player->ChangeState(m_player->GetWalkState());
	}

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		spaceでジャンプ
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space))
	{
		//		状態を切り替える(しゃがみ)
		m_player->ChangeState(m_player->GetJumpState());
	}
}

void PlayerSliding::SlopeJudgement()
{
	//		当たっている床の法線があるかどうか
	if (m_player->GetCollitionInformation()->GetFloorMeshHitNormalize().size() != 1)
	{
		m_slopeJudgement = false;

		return;
	}

	//		上向きのベクトルと床の法線の内積を取る
	float dot = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).
		Dot(m_player->GetCollitionInformation()->GetFloorMeshHitNormalize()[0]);

	//		坂と判定する角度かどうか判断する
	if (dot >= 1.0f && dot < 0.2f)
	{
		m_slopeJudgement = false;

		return;
	}

	//		移動方向を受け取る
	DirectX::SimpleMath::Vector2 acc2 = { m_player->GetAcceleration().x, m_player->GetAcceleration().z };

	//		坂の方向を計算する
	DirectX::SimpleMath::Vector3 downhill = m_player->GetCollitionInformation()->GetFloorMeshHitNormalize()[0]
											- DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

	//		下り方向を二次元にする
	m_slidingVelocity = { downhill.x, downhill.z };

	//		正規化
	m_slidingVelocity.Normalize();

	//		内積が
	if (m_slidingVelocity.Dot(acc2) > 0.8f)
	{
		//		下り処理
		m_slopeJudgement = true;

		return;
	}

	m_slopeJudgement = false;
}
