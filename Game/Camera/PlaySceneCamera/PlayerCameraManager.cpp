/*
* @file		PlayerCameraManager.cpp
* @brief	プレイヤーのカメラのマネージャー
* @author	Morita
* @date		2024/05/08
*/

#include "pch.h"

#include "PlayerCameraManager.h"

#include "State/DebugCamera.h"
#include "State/PlayerCamera.h"
#include "State/PlayerWallWalkCamera.h"
#include "State/PlayerStartCamera.h"
#include "State/PlayerDeathCamera.h"
#include "State/PlayerCameraStop.h"
#include "State/PlayerGoalCamera.h"

PlayerCameraManager::PlayerCameraManager(GameManager* gameManager)
	:
	m_state{},
	m_gameManager(gameManager),
	m_cameraType{},
	m_shakingSpeed(0.0f),
	m_shakingRatio(0.0f),
	m_shakingTime(0.0f)
{
	//		カメラの情報を
	m_information = std::make_unique<PlayerCameraInformation>();

	//		カメラのビューベクトルオブザーバー
	m_cameraViewVelocityObserver = std::make_unique<CameraViewVelocityObserver>();

	//		カメラの派生クラスの生成
	m_stateInformation.insert({ CameraType::Standard, std::make_unique<PlayerCamera>(this) });
	m_stateInformation.insert({ CameraType::Debug, std::make_unique<DebugCamera>(this) });
	m_stateInformation.insert({ CameraType::WallWalk, std::make_unique<PlayerWallWalkCamera>(this) });
	m_stateInformation.insert({ CameraType::Start, std::make_unique<PlayerStartCamera>(this) });
	m_stateInformation.insert({ CameraType::Stop, std::make_unique<PlayerCameraStop>(this) });
	m_stateInformation.insert({ CameraType::Death, std::make_unique<PlayerDeathCamera>(this) });
	m_stateInformation.insert({ CameraType::Goal, std::make_unique<PlayerGoalCamera>(this) });
}

PlayerCameraManager::~PlayerCameraManager()
{
}

void PlayerCameraManager::Initialize()
{
	//		プロジェクション行列の作製
	CreateProj(m_information->GetViewAngle(),
				LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN,
				LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX);

	//		情報の初期化
	m_information->Initialize();

	//		初期状態
	m_cameraType = CameraType::Start;

	//		初期状態を設定する
	m_state = m_stateInformation[m_cameraType].get();

	//		初期化処理
	m_state->Initialize();

	//		一度更新をしておく(Effectの為)
	m_state->Update();
}

void PlayerCameraManager::Update()
{
	//		カメラの更新処理
	m_state->Update();
}

void PlayerCameraManager::Finalize()
{
	m_information->Finalize();
}

void PlayerCameraManager::CameraMove()
{
	//		マウスの相対位置から移動量を出す
	float x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x);
	float y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y);

	DirectX::SimpleMath::Vector2 angle = m_information->GetAngle();

	//		移動量
	DirectX::SimpleMath::Vector2 move = DirectX::SimpleMath::Vector2::Zero;

	//		カメラの移動量を足す
	move.x += x * m_information->GetCameraSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();
	move.y += -y * (m_information->GetCameraSpeed() / 2.0f) * LibrarySingleton::GetInstance()->GetElpsedTime();

	angle += move;

	//		視点移動の制限
	angle.y = Library::Clamp(angle.y, m_information->GetCameraAngleMin(), m_information->ANGLE_Y_MAX);
	
	m_information->SetAngle(angle);
	m_information->SetCameraMove(move);
}

void PlayerCameraManager::ChangeState(CameraType type)
{
	//		現在の同じ状態なら行わない
	if (type == m_cameraType) return;

	//		現在の状態の終了処理を行う
	m_state->Finalize();

	//		新しい状態に上書きする
	m_cameraType = type;

	//		新しい状態にする
	m_state = m_stateInformation[m_cameraType].get();

	//		新しい状態の初期化をする
	m_state->Initialize();

}

void PlayerCameraManager::ViewingAngleUpdate()
{
	float angle = Library::Clamp(((m_information->GetPlayerSpeed() -
					m_information->ANGLE_CHANGE_MIN_SPEED) / m_information->ANGLE_CHANGE_MAX_SPEED), 0.0f, 1.0f);

	angle = Library::Lerp(0.0f, m_information->ANGLE_CHANGE_MIN_SPEED, angle);

	m_information->SetNowViewAngle(Library::Lerp
	(m_information->GetNowViewAngle(), angle, 0.7f));

	float viewAnge = m_information->GetNowViewAngle() + m_information->GetViewAngle();

	CreateProj(viewAnge, LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MIN, LibrarySingleton::GetInstance()->DRAWING_DISTANCE_MAX);

}

void PlayerCameraManager::CreateProj(float fov, float nearPlane, float farPlane)
{
	//		proj行列を作成する
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(fov), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			nearPlane,
			farPlane);

	//		プロジェクション行列を設定する
	LibrarySingleton::GetInstance()->SetProj(proj);
}

void PlayerCameraManager::CreateEye(DirectX::SimpleMath::Vector3 position,
									DirectX::SimpleMath::Vector2 angle,
									DirectX::SimpleMath::Vector3 up)
{
	//		デグリーからラジアンへ行列にする
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(angle.x));
	DirectX::SimpleMath::Matrix matrixX = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(angle.y));

	//		向いている角度にする
	DirectX::SimpleMath::Matrix rotation = matrixY * matrixX;

	//		視点方向
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Transform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), rotation.Invert());

	//		ターゲットにプレイヤーの座標を足す
	target += position;

	//		ビュー行列を設定する
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	(position, target, up));

	m_information->SetEye(position);
	m_information->SetTarget(target);
	m_information->SetUp(up);

	//		視線ベクトルを設定する
	m_information->SetViewVelocity(target - position);

	m_cameraViewVelocityObserver->CameraViewVelocity(m_information->GetViewVelocity());
	m_cameraViewVelocityObserver->CameraView(m_information->GetEye());
	m_cameraViewVelocityObserver->CameraUp(m_information->GetUP());
}

void PlayerCameraManager::PlayerHeght(DirectX::SimpleMath::Vector3 height)
{
	m_information->SetPlayerHeight(height);
}

void PlayerCameraManager::NowSpeed(float speed)
{
	m_information->SetPlayerSpeed(speed);

	ViewingAngleUpdate();
}

void PlayerCameraManager::ShakeHead()
{
	ShakingView();
}

void PlayerCameraManager::CameraStop()
{
	m_information->SetStopJudgement(false);

	//		カメラ停止フラグがtrueの時
	ChangeState(CameraType::Stop);
}

void PlayerCameraManager::WallWalkMove(float height)
{
	m_information->SetWallHeight(height);

	if (height > 0.0f)
	{
		//		壁走りカメラに切り替える
		ChangeState(CameraType::WallWalk);
	}
	else
	{
		//		スタンダード
		ChangeState(CameraType::Standard);
	}
}

void PlayerCameraManager::Direction(DirectX::SimpleMath::Vector3 direction)
{
	m_information->SetDirection(direction);
}

void PlayerCameraManager::WallNormalize(DirectX::SimpleMath::Vector3 normal)
{
	m_information->SetWallNormalize(normal);
}

void PlayerCameraManager::ShakingView()
{
	//		頭を動かす割合を設定する
	m_shakingRatio = m_information->GetPlayerSpeed() / 70.0f;

	//		頭を動かす速さ
	m_shakingSpeed = Library::Lerp(2.0f, 10.0f, m_shakingRatio);

	m_shakingSpeed = Library::Lerp(0.0f, 20.0f, m_information->GetPlayerSpeed() / 70.0f);

	//		頭を動かす速さ
	m_shakingTime += LibrarySingleton::GetInstance()->GetElpsedTime() * m_shakingSpeed;

	//		縦揺れ
	//VerticalShaking();

	//		横揺れ
	//HorizontalShaking();
}

void PlayerCameraManager::HorizontalShaking()
{
	DirectX::SimpleMath::Vector2 velocity = { m_information->GetViewVelocity().x,
											  m_information->GetViewVelocity().z };

	velocity.Normalize();

	velocity = DirectX::SimpleMath::Vector2(velocity.y, -velocity.x);


	float move = (cos(m_shakingTime) + 1.0f) / 2.0f;

	//		頭の動きの幅
	float moveLength = Library::Lerp(0.0f, 0.5f, m_shakingRatio);


	velocity = DirectX::SimpleMath::Vector2::Lerp(DirectX::SimpleMath::Vector2(velocity.x, velocity.y) * moveLength,
		DirectX::SimpleMath::Vector2(velocity.x, velocity.y) * -moveLength,
		move);

	m_information->SetSheakHeadVelocity({ m_information->GetShaekHeadVelocity().x + velocity.x,
										  0.0f,
										  m_information->GetShaekHeadVelocity().x + velocity.y });

	//m_position.x += velocity.x;
	//m_position.z += velocity.y;
}

void PlayerCameraManager::VerticalShaking()
{
	float move = (sin(m_shakingTime) + 1.0f) / 2.0f;

	//		頭の動きの幅
	float moveLength = Library::Lerp(0.0f, 0.1f, m_shakingRatio);

	//m_position.y += Library::Lerp(-moveLength, moveLength, move);
}
