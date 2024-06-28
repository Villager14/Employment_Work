/*
* @file		PlayerWallWalk.cpp
* @brief	プレイヤーの壁歩き状態
* @author	Morita
* @date		2024/04/30
*/

#include "pch.h"

#include "PlayerWallWalk.h"

#include "../Player.h"

PlayerWallWalk::PlayerWallWalk(Player* player)
	:
	m_player(player),
	m_heightMove(7.0f),
	m_moveAngle(0.0f)
{
}

PlayerWallWalk::~PlayerWallWalk()
{
}

void PlayerWallWalk::Initialize()
{
	//		移動方向
	float moveRadian = DirectX::XMConvertToRadians(90.0f);
	m_moveAngle.y = 1.0f;

	DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

	acceleation.Normalize();

	//		壁に入った方向から移動方向を出す
	DirectX::SimpleMath::Vector3 corss =
		m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().Cross(acceleation);

	//		外積が０以上の場合反対の方に進む
	if (corss.y > 0)
	{
		moveRadian *= -1.0f;
		m_moveAngle.y *= -1.0f;
	}

	//		最初に当たった壁の法線を受け取る
	DirectX::SimpleMath::Vector2 normalize =
	{ m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().x,
	 m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().z };

	normalize.Normalize();

	float radian = atan2(normalize.y, normalize.x);

	m_moveAngle.x = radian + moveRadian;

	//		ベクトルを出す
	m_velocity = DirectX::SimpleMath::Vector3(cosf(radian + moveRadian),
		0.0f, sinf(radian + moveRadian));

	m_velocity.Normalize();

	float speed = m_player->GetInformation()->GetAcceleration().Length();

	//		歩く速度より遅かった場合
	if (speed < m_player->GetInformation()->GetWalkSpeed())
	{
		//		歩く速度にする
		speed = m_player->GetInformation()->GetWalkSpeed();
	}

	//		移動速度
	m_player->GetInformation()->SetAcceleration(m_velocity * speed);

	//		移動方向
	m_player->GetInformation()->SetDirection(m_velocity);

	//		アニメーション壁歩き
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->WallWalk);
}

void PlayerWallWalk::Update()
{
	MoveProcessing();
}

void PlayerWallWalk::Move()
{
	if (m_player->GetCollitionInformation()->GetWallWalkPlayerPosition().size() != 0)
	{
		m_player->GetInformation()->SetPlanPosition(m_player->GetCollitionInformation()
			->GetWallWalkPlayerPosition()[0]);
	}

	//		壁メッシュの当たり判定
	m_player->WallMeshHitJudgement();

	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		頭の動き
	HeadMove();

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerWallWalk::Animation()
{
	//		壁歩き
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_moveAngle,
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerWallWalk::Render()
{
}

void PlayerWallWalk::Finalize()
{
	//		落下時間を初期化する
	m_player->GetInformation()->SetFallTime(0.0f);

	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	//		立っているときの高さ
	m_heightMove = m_player->GetInformation()->GetStandingHeight();
}

void PlayerWallWalk::MoveProcessing()
{
	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition()
		+ (m_velocity * m_player->GetInformation()->GetAcceleration().Length()) *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerWallWalk::ChangeStateJudgement()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = 
		*LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		spaceでジャンプ
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) || 
		m_player->GetCollitionInformation()->GetWallWalkPlayerPosition().size() == 0)
	{
		DirectX::SimpleMath::Vector3 velo = DirectX::SimpleMath::Vector3
		(cosf(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x)),
			0.0f, sinf(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x)));

		velo.Normalize();

		float dot = m_velocity.Dot(velo);

		if (dot < 0.3f)
		{
			//		移動方向を計算する
			DirectX::SimpleMath::Vector3 velocity =
				DirectX::SimpleMath::Vector3::Lerp(m_velocity,
					m_player->GetPlayerInformationCollition()->GetWallWalkNormalize(), 0.3f);

			velocity.Normalize();

			float speed = m_player->GetInformation()->GetAcceleration().Length();

			//		ジャンプする方向
			m_player->GetInformation()->SetAcceleration(velocity * speed);

			//		状態を切り替える(ジャンプ)
			m_player->ChangeState(m_player->PlayerState::Jump);
		}
		else
		{
			//		ジャンプする方向
			m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f));

			//		ジャンプする方向
			m_player->GetInformation()->SetAcceleration(m_player->MoveDirection(m_player->GetInformation()->GetDirection()) * m_player->GetInformation()->GetAcceleration().Length());

			//		状態を切り替える(ジャンプ)
			m_player->ChangeState(m_player->PlayerState::Jump);
		}
	}

	DirectX::SimpleMath::Vector3 velo = DirectX::SimpleMath::Vector3
	(cosf(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x + 90.0f)),
		0.0f, sinf(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x + 90.0f)));

	velo.Normalize();

	float dot = m_velocity.Dot(velo);

	//		プレイヤーが進行方向からだいぶそれた場所を見た場合
	if (dot < 0.0f)
	{
		//		歩き状態にする
		m_player->ChangeState(m_player->PlayerState::Walk);
	}
}

void PlayerWallWalk::HeadMove()
{
	//		現在の座標を受け取る
	DirectX::SimpleMath::Vector3 height = m_player->GetInformation()->GetPosition();

	//		頭の高さが5以上なら処理をする
	if (m_heightMove > HEAD_WALLWALK_HEIGHT)
	{
		//		
		m_heightMove -= m_player->GetInformation()->GetHeadMoveSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

		//		高さの制限をする
		m_heightMove = Library::Clamp(m_heightMove, HEAD_WALLWALK_HEIGHT, m_player->GetInformation()->GetStandingHeight());
	}

	//		高さを足す
	height.y += m_heightMove;

	//		頭の移動量を受け取る
	float move = m_player->GetInformation()->GetHeadMove();

	//		移動速度
	move += m_player->GetInformation()->GetHeadMoveSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		移動量の制限
	move = Library::Clamp(move, 0.0f, m_player->GetInformation()->GetHeadMoveMAX());

	//		頭の移動量を設定する
	m_player->GetInformation()->SetHeadMove(move);

	//		頭の移動量を足す
	height.x += m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().x * m_player->GetInformation()->GetHeadMove();;
	height.z += m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().z * m_player->GetInformation()->GetHeadMove();;

	//		プレイヤーの高さを更新
	m_player->GetInformation()->SetPlayerHeight(height);
}
