/*
* 
* @file		Player.cpp
* @brief	プレイヤーの処理
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"
#include "Player.h"

#include <bitset>

Player::Player(GameManager* gameManager)
	:
	m_state{},
	m_collitionInformation(),
	m_gameManager(gameManager)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//		プレイヤーの情報を生成する
	m_information = std::make_unique<PlayerInformation>();

	//		プレイヤー待機状態の生成
	m_playerStay = std::make_unique<PlayerStay>(this);

	//		プレイヤー歩き状態の生成
	m_playerWalk = std::make_unique<PlayerWalk>(this);

	//		プレイヤーのしゃがみ状態の生成
	m_playerCrouching = std::make_unique<PlayerCrouching>(this);

	//		プレイヤーのジャンプ状態を生成
	m_playerJump = std::make_unique<PlayerJump>(this);

	//		プレイヤーのスライディング状態の生成
	m_playerSliding = std::make_unique<PlayerSliding>(this);

	//		プレイヤーのダッシュ状態を生成
	m_playerDash = std::make_unique<PlayerDash>(this);

	//		プレイヤーの低速状態を生成
	m_playerSlowTime = std::make_unique<PlayerSlowTime>(this);

	//		プレイヤーの壁歩き状態の生成
	m_playerWallWalk = std::make_unique<PlayerWallWalk>(this);

	//		プレイヤーのワイヤー状態の生成
	m_playerWire = std::make_unique<PlayerWire>(this);

	//		プレイヤーの壁ジャンプ状態を生成
	m_playerWallJump = std::make_unique<PlayerWallJump>(this);

	//		プレイヤーの死亡状態を生成する
	m_playerDeath = std::make_unique<PlayerDeath>(this);

	//		プレイヤーのスタート状態を生成する
	m_playerStart = std::make_unique<PlayerStart>(this);

	//		初期状態
	m_state = m_playerStart.get();

	//		状態を初期化する
	m_state->Initialize();

	//		立っている高さを入れておく
	m_information->SetPlayerHeight(DirectX::SimpleMath::Vector3(0.0f, m_information->GetStandingHeight(), 0.0f));

	//		プレイヤーの攻撃の生成
	m_playerAttack = std::make_unique<PlayerAttack>(this);

	//		プレイヤーの攻撃の初期化
	m_playerAttack->Initialize();

	//		当たり判定用プレイヤーの情報を生成する
	m_playerInformationCollition = std::make_unique<PlayerInformationCollition>();

	//		当たり判定用プレイヤーの情報を生成する
	//m_playerInformationCamera = std::make_unique<PlayerInformationCamera>();

	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_playerObject = DirectX::Model::CreateFromCMO
	(LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		L"Resources/Models/Player.cmo", *m_effect);
}

void Player::Update(PlayerCameraInformation* cameraInformation)
{
	m_cameraInformation = cameraInformation;

	//		更新処理
	m_state->Update();

	WireActionJudgement();

	m_playerInformationCollition->SetPlayerPosition(m_information->GetPlanPosition());
	m_playerInformationCollition->SetPlayerHeight(m_information->GetPlayerHeight());

	//		
	if (!m_information->GetDashJudgement())
	{
		//		クールタイム
		float coolTime = m_information->GetDashCoolTime();

		//		経過時間
		coolTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		//		一定時間たったら
		if (coolTime >= 2.0f)
		{
			m_information->SetDashJudgement(true);
			coolTime = 0.0f;
		}

		//		クールタイムを設定する
		m_information->SetDashCoolTime(coolTime);
	}

	m_information->SetWallWalkNormalize(m_playerInformationCollition->GetWallWalkNormalize());
}

void Player::MeshUpdate()
{
	//		移動処理
	m_state->Move();
}

void Player::Render()
{
	//		描画処理
	m_state->Render();

	//		座標
	LibrarySingleton::GetInstance()->DebugFont(L"PositionX", m_information->GetPosition().x, 0, 0);
	LibrarySingleton::GetInstance()->DebugFont(L"PositionY", m_information->GetPosition().y, 0, 20);
	LibrarySingleton::GetInstance()->DebugFont(L"PositionZ", m_information->GetPosition().z, 0, 40);

	//		速度
	LibrarySingleton::GetInstance()->DebugFont(L"Speed", m_information->GetAcceleration().Length(), 0, 80);

	//		重力
	LibrarySingleton::GetInstance()->DebugFont(L"gravity", m_information->GetGravity(), 0, 100);

	if (m_collitionInformation->GetWallHitVelocity().size() != 0)
	{
		//		めり込み
		LibrarySingleton::GetInstance()->DebugFont(L"wallX", m_collitionInformation->GetWallHitVelocity()[0].x, 0, 140);
		LibrarySingleton::GetInstance()->DebugFont(L"wallZ", m_collitionInformation->GetWallHitVelocity()[0].y, 0, 160);
	}
}

void Player::Finalize()
{
}

void Player::DeathJudgement()
{
	//		簡易死亡判定
	if (m_information->GetPosition().y < -150.0f)
	{
		//		死亡状態に切り替える
		ChangeState(m_playerDeath.get());
	}
}

void Player::ChangeState(IPlayer* state)
{
	//		同じ状態なら処理をしない
	if (m_state == state) return;

	//		現在の状態の終了処理をする
	m_state->Finalize();

	//		状態を切り替える
	m_state = state;

	//		新しい状態の初期化処理をする
	m_state->Initialize();
}

DirectX::SimpleMath::Vector3 Player::Direction(bool* keyPressjudgement)
{
	std::bitset<4> directionbit;

	//		キーボードStateの取得
	DirectX::Keyboard::State m_keyboard = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::W))
	{
		directionbit.set(0, 1);

		direction.z += 1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::S))
	{
		directionbit.set(1, 1);

		direction.z += -1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::D))
	{
		directionbit.set(2, 1);

		direction.x += -1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::A))
	{
		directionbit.set(3, 1);

		direction.x += 1.0f;
	}

	if (directionbit != 0)
	{
		//		キーが押されている
		*keyPressjudgement = true;
	}

	return direction;
}

DirectX::SimpleMath::Vector3 Player::MoveDirection
(const DirectX::SimpleMath::Vector3 direction)
{
	//		カメラの向き
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(m_information->GetCameraAngle().x));

	//		移動する方向
	return DirectX::SimpleMath::Vector3::Transform(
		direction, matrixY.Invert());
}

void Player::Gravity(bool weekJudgement)
{
	float speed = 2.0f;

	//		落下時間を受け取る
	float fallTime = m_information->GetFallTime();

	if (weekJudgement)
	{
		speed = 1.0f;

		//		重力加速度
		fallTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed;

		m_information->SetGravity(m_information->GetGravitationalAcceleration() * (fallTime * fallTime));

	}
	else
	{
		//		重力加速度
		fallTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed * (m_information->GetTimeSpeed()* m_information->GetTimeSpeed());

		m_information->SetGravity(m_information->GetGravitationalAcceleration() * (fallTime * fallTime));
	}

	//		落下時間を設定する
	m_information->SetFallTime(fallTime);

	m_information->SetPlanPosition({ m_information->GetPlanPosition().x,
									 m_information->GetPlanPosition().y - m_information->GetGravity() * 
									LibrarySingleton::GetInstance()->GetElpsedTime()
									* m_information->GetTimeSpeed(),
									 m_information->GetPlanPosition().z});


}

bool Player::FloorMeshHitJudgement()
{
	//		床に当たっているか
	if (m_collitionInformation->GetFloorMeshHitPoint().size() != 0)
	{
		//		メッシュのY座標を受け取る
		m_information->SetPlanPosition({ m_information->GetPlanPosition().x,
			m_collitionInformation->GetFloorMeshHitPoint()[0].y,
			m_information->GetPlanPosition().z });

		//		落下時間を０にする
		m_information->SetFallTime(0.0f);

		//		ジャンプできる状態にする
		m_information->SetJumpJudgement(false);

		return true;
	}

	return false;
}

bool Player::WallMeshHitJudgement()
{
	if (m_collitionInformation->GetWallHitVelocity().size() > 0)
	{
		DirectX::SimpleMath::Vector3 planePosition = m_information->GetPlanPosition();

		planePosition.x = m_collitionInformation->GetWallHitVelocity()[0].x;
		planePosition.z = m_collitionInformation->GetWallHitVelocity()[0].y;

		m_information->SetPlanPosition(planePosition);

		return true;
	}

	return false;
}

void Player::PlayerHeightTransition(const float& firstHeight, const float& endHeight, const float& speed)
{
	DirectX::SimpleMath::Vector3 headPosition = m_information->GetPosition();

	float heightTime = m_information->GetHeightTime();

	//		一以上なら処理をしない
	if (heightTime < 1.0f)
	{
		//		遷移速度
		heightTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed;

		//		一以上にならないようにする
		heightTime = Library::Clamp(heightTime, 0.0f, 1.0f);

		//		easeOutQuart
		float move = 1.0f - pow(1.0f - heightTime, 4.0f);

		m_information->SetHeightTime(heightTime);

		//		ラープで初期の高さから立ちの高さへ
		headPosition.y = Library::Lerp(firstHeight, endHeight, move);
	}
	else
	{
		headPosition.y = endHeight;
	}

	if (m_information->GetHeadMove() > 0.0f)
	{
		float headMove = m_information->GetHeadMove();

		//		移動速度
		headMove -= m_information->GetHeadMoveSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

		//		移動量の制限
		headMove = Library::Clamp(headMove, 0.0f, m_information->GetHeadMoveMAX());

		//		頭の移動量を足す
		headPosition.x += m_playerInformationCollition->GetWallWalkNormalize().x * headMove;
		headPosition.z += m_playerInformationCollition->GetWallWalkNormalize().z * headMove;

		m_information->SetHeadMove(headMove);
	}

	//		高さを設定する
	m_information->SetPlayerHeight(headPosition);
}

bool Player::WireActionJudgement()
{
	//		ワイヤーの座標がない場合処理をしない
	if (m_information->GetWirePosition().size() == 0) return false;

	//		ワイヤーのある方向
	DirectX::SimpleMath::Vector3 wireDirection = m_information->GetWirePosition()[0] - m_information->GetPlayerHeight();

	//		視線ベクトル
	DirectX::SimpleMath::Vector3 viewDirection = m_information->GetViewVelocity();

	//		正規化
	wireDirection.Normalize();
	viewDirection.Normalize();

	//		内積を取る
	float dot = wireDirection.Dot(viewDirection);

	//		ワイヤーの方向を向いていたら
	if (dot < 0.9f) return false;

	//		マウストラッカーの値を受け取る
	DirectX::Mouse::ButtonStateTracker* mouse = LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		マウスが押された場合
	if (mouse->leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		移動ワイヤーの座標を設定する
		DirectX::SimpleMath::Vector3 wireMovePosition = m_information->GetWirePosition()[0];

		wireMovePosition.y -= 12.0f;

		//		移動ワイヤー座標を設定する
		m_information->SetWireMovePosition(wireMovePosition);

		//		状態を遷移する（）
		ChangeState(m_playerWire.get());
		
		return true;
	}

	return false;
}

void Player::WallWalkJudgement()
{
	//		壁に当たっている場合
	if (m_collitionInformation->GetMeshWallNormalize().size() == 1)
	{
		DirectX::SimpleMath::Vector3 acceleation = m_information->GetAcceleration();

		acceleation.Normalize();

		float dot = m_collitionInformation->GetMeshWallNormalize()[0].Dot(acceleation);

		//		プレイヤーが一定の角度を向いている場合処理をする
		if (dot <= -0.1f && dot >= -0.9f)
		{
			//		法線を代入する
			m_playerInformationCollition->SetWallWalkNormalize(m_collitionInformation->GetMeshWallNormalize()[0]);

			//		状態を切り替える(壁歩き状態)
			ChangeState(m_playerWallWalk.get());

			return;
		}
	}
}
