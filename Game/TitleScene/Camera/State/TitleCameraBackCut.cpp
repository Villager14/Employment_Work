/*
* @file		TitleCameraBackCut.cpp
* @brief	タイトルカメラの背景カット
* @author	Morita
* @date		2024/12/15
*/

#include "pch.h"

#include "TitleCameraBackCut.h"

#include "../TitleCameraManager.h"

TitleCameraBackCut::TitleCameraBackCut(TitleCameraManager* titleCameraManager)
	:
	m_titleCameraManager(titleCameraManager),
	m_elapsedTime(0.0f)
{
}

TitleCameraBackCut::~TitleCameraBackCut()
{
}

void TitleCameraBackCut::Initialize()
{
	m_elapsedTime = 0.0f;
}

void TitleCameraBackCut::Update()
{
	//		遷移時間
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	float radian = Library::Lerp(FIRST_RADIAN, END_RADIAN, m_elapsedTime);

	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Lerp(
		FIRST_TARGET, END_TARGET, m_elapsedTime);


	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::
		CreateRotationY(DirectX::XMConvertToRadians(radian));

	DirectX::SimpleMath::Vector3 eye = { 0.0f, 0.0f, 1.0f };

	eye = DirectX::SimpleMath::Vector3::Transform(eye, rotation.Invert());

	//		注視点からの距離
	eye *= (2.0f - 0.0f / 100.0f);

	eye += target;

	//		プロジェの作製
	m_titleCameraManager->CreateView(eye, target);

	//		フェードアウト
	m_titleCameraManager->FadeOut(m_elapsedTime);

	if (m_elapsedTime >= 1.0f)
	{
		//		前方カットカメラに変更
		m_titleCameraManager->ChangeState(TitleCameraManager::Front);
	}
}

void TitleCameraBackCut::Finalize()
{
	m_elapsedTime = 0.0f;
}
