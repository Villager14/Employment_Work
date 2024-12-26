/*
* @file		TitleCameraManager.cpp
* @brief	タイトルカメラマネージャー
* @author	Morita
* @date		2024/12/15
*/

#include "pch.h"

#include "TitleCameraManager.h"

#include "State/TitleCameraFrontCut.h"
#include "State/TitleCameraFrontAscendingCut.h"
#include "State/TitleCameraFrontOverHeadCut.h"
#include "State/TitleCameraBackCut.h"

TitleCameraManager::TitleCameraManager()
	:
	m_state(NULL),
	m_cameraType(CameraType::Non),
	m_fadeOutUseJudgement(false)
{
	m_fadeObserver = std::make_unique<FadeObserver>();

	m_cameraViewVelocityObserver = std::make_unique<CameraViewVelocityObserver>();
}

TitleCameraManager::~TitleCameraManager()
{
}

void TitleCameraManager::Initialize()
{
	//		フェードを行っていない
	m_fadeOutUseJudgement = false;

	//		状態の追加
	m_cameraInformation.insert({CameraType::Front, std::make_unique<TitleCameraFrontCut>(this)});
	m_cameraInformation.insert({ CameraType::FrontAscending, std::make_unique<TitleCameraFrontAscendingCut>(this) });
	m_cameraInformation.insert({ CameraType::OverHead, std::make_unique<TitleCameraFrontOverHeadCut>(this) });
	m_cameraInformation.insert({ CameraType::Back, std::make_unique<TitleCameraBackCut>(this) });

	m_cameraType = CameraType::Front;

	m_state = m_cameraInformation[m_cameraType].get();

	m_state->Initialize();

	m_state->Update();

	CreateProj();
}

void TitleCameraManager::Update()
{
	m_state->Update();
}

void TitleCameraManager::Finalize()
{
	m_fadeObserver->Dalete();
}

void TitleCameraManager::CreateView(DirectX::SimpleMath::Vector3 position,
									DirectX::SimpleMath::Vector3 target)
{
	//		アップベクトル
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		ビュー行列を設定する
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	(position, target, up));

	m_cameraViewVelocityObserver->CameraViewVelocity(target - position);
	m_cameraViewVelocityObserver->CameraUp(up);
	m_cameraViewVelocityObserver->CameraView(position);
}

void TitleCameraManager::CreateProj()
{
	//		ビュー行列を作成する
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(60.0f), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			0.1f, 360.0f);

	//		プロジェクション行列を設定する
	LibrarySingleton::GetInstance()->SetProj(proj);
}

void TitleCameraManager::ChangeState(CameraType changeState)
{
	//		同じシーンの場合処理をしない
	if (m_cameraType == changeState) return;

	//		フェードを行っていない状態にする
	m_fadeOutUseJudgement = false;

	//		現在の状態の終了処理をする
	m_state->Finalize();

	//		状態を切り替える
	m_cameraType = changeState;

	m_state = m_cameraInformation[m_cameraType].get();

	//		新しい状態の初期化処理をする
	m_state->Initialize();
}
