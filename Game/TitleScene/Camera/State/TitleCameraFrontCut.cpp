/*
* @file		TitleCameraFrontCut.cpp
* @brief	タイトルカメラのフロントカット
* @author	Morita
* @date		2024/12/15
*/

#include "pch.h"

#include "TitleCameraFrontCut.h"

#include "../TitleCameraManager.h"

TitleCameraFrontCut::TitleCameraFrontCut(TitleCameraManager* titleCameraManager)
	:
	m_titleCameraManager(titleCameraManager),
	m_elapsedTime(0.0f)
{
}

TitleCameraFrontCut::~TitleCameraFrontCut()
{
}

void TitleCameraFrontCut::Initialize()
{
	m_elapsedTime = 0.0f;
}

void TitleCameraFrontCut::Update()
{
	//		遷移時間
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	float radian = Library::Lerp(FIRST_RADIAN, END_RADIAN, m_elapsedTime);

	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::
		CreateRotationY(DirectX::XMConvertToRadians(radian));

	DirectX::SimpleMath::Vector3 eye = { 0.0f, 0.0f, 1.0f };

	eye = DirectX::SimpleMath::Vector3::Transform(eye, rotation.Invert());

	//		注視点からの距離
	eye *= (2.0f - 0.0f / 100.0f);

	eye += TARGET;

	//		プロジェの作製
	m_titleCameraManager->CreateView(eye, TARGET);

	//		フェードアウト
	m_titleCameraManager->FadeOut(m_elapsedTime);

	if (m_elapsedTime >= 1.0f)
	{
		//		
		m_titleCameraManager->ChangeState(TitleCameraManager::FrontAscending);
	}
}

void TitleCameraFrontCut::Finalize()
{
	m_elapsedTime = 0.0f;
}
