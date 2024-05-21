/*
* @file		PlayerWire.cpp
* @brief	プレイヤーのワイヤー状態
* @author	Morita
* @date		2024/05/13
*/

#include "pch.h"

#include "PlayerWire.h"

#include "../Player.h"

PlayerWire::PlayerWire(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f),
	m_speed(0.0f),
	m_fallJudgement(false),
	m_length(0.0f),
	m_floorHitJudgement(false),
	m_wallHitJudgement(false),
	m_firstSpeed(0.0f)
{
}

PlayerWire::~PlayerWire()
{
}

void PlayerWire::Initialize()
{
	//		高さの取得
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;

	//		移動方向
	m_direction = m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition();

	m_direction.Normalize();

	//		距離
	m_length = (m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition()).Length();

	//		落下時間を０にする
	m_player->GetInformation()->SetFallTime(0.0f);
}

void PlayerWire::Update()
{
	MoveProcessing();

	m_player->Gravity(true);
}

void PlayerWire::Move()
{
	//		壁メッシュの当たり判定
	if (m_player->WallMeshHitJudgement())
	{
		if (m_fallJudgement)m_wallHitJudgement = true;
	}

	//		床に当たっているか
	if (m_player->FloorMeshHitJudgement())
	{
		if (m_fallJudgement)m_floorHitJudgement = true;
	}
	
	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		落下状態にするかどうか
	FallJudgement();

	//		立つ処理
	m_player->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetPosition().y + m_player->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerWire::Render()
{
}

void PlayerWire::Finalize()
{
	m_time = 0.0f;

	m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3::Zero);

	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_wallHitJudgement = false;

	m_floorHitJudgement = false;

	m_fallJudgement = 0.0f;
}

void PlayerWire::MoveProcessing()
{
	//		落下状態か判断する
	if (!m_fallJudgement) AttractProcess();
	else FallProcess();

	DirectX::SimpleMath::Vector3 velocity = m_direction * m_speed;

	m_player->GetInformation()->SetAcceleration(velocity);

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() + m_direction *
		m_speed * LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerWire::ChangeStateJudgement()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		キーボードステートの取得
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift))
	{
		//		ダッシュできるかどうか
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		状態を切り替える(ダッシュ)
			m_player->ChangeState(m_player->GetDashState());
		}
	}

	if (m_floorHitJudgement)
	{
		//		移動キーを押したとき
		if (keyboardState.IsKeyDown(DirectX::Keyboard::W) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::A) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::S) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::D))
		{
			//		状態を切り替える（歩き)
			m_player->ChangeState(m_player->GetWalkState());
		}
		else
		{
			//		状態を切り替える（待機)
			m_player->ChangeState(m_player->GetWalkState());
		}
	}

	if (m_wallHitJudgement)
	{
		DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

		acceleation.Normalize();

		float dot = m_player->GetCollitionInformation()->GetMeshWallNormalize()[0].Dot(acceleation);

		//		プレイヤーが一定の角度を向いている場合処理をする
		if (dot <= -0.2f && dot >= -0.9f)
		{
			//		法線を代入する
			m_player->GetPlayerInformationCollition()->SetWallWalkNormalize(
				(m_player->GetCollitionInformation()->GetMeshWallNormalize()[0]));

			//		状態を切り替える(壁歩き状態)
			m_player->ChangeState(m_player->GetWallWalkState());
		}	
	}
}

void PlayerWire::AttractProcess()
{
	//		現在の距離
	float nowLenght = (m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition()).Length();

	//		割合
	float ratio = nowLenght / m_length;

	m_speed = Library::Lerp(50, 200, ratio);
}

void PlayerWire::FallProcess()
{
	//		キーを押しているかどうか
	bool keyInputJudgement = false;

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	//		移動する方向を受け取る
	direction = m_player->Direction(&keyInputJudgement);

	//		正規化
	direction.Normalize();

	//		移動する方向を追加する
	m_direction += m_player->MoveDirection(direction) * 0.2f * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		正規化
	m_direction.Normalize();
}

void PlayerWire::FallJudgement()
{
	//		プレイヤーから見たワイヤーオブジェクトの方向を求める
	DirectX::SimpleMath::Vector3 direction = m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition();

	//		正規化
	direction.Normalize();

	//		内積
	float dot2 = m_direction.Dot(direction);

	//		プレイヤーの移動方向と現在の方向が別の場合落下処理にする
	if (dot2 < 0.0f)
	{
		m_fallJudgement = true;

		m_time = 0.0f;
	}
}
