/*
* @file		TitleCameraFrontOverHeadCut.cpp
* @brief	タイトルカメラの頭上カット
* @author	Morita
* @date		2024/12/15
*/

#include "pch.h"

#include "TitleCameraFrontOverHeadCut.h"

#include "../TitleCameraManager.h"

TitleCameraFrontOverHeadCut::TitleCameraFrontOverHeadCut(TitleCameraManager* titleCameraManager)
	:
	m_titleCameraManager(titleCameraManager),
	m_elapsedTime(0.0f)
{
}

TitleCameraFrontOverHeadCut::~TitleCameraFrontOverHeadCut()
{
}

void TitleCameraFrontOverHeadCut::Initialize()
{
	m_elapsedTime = 0.0f;
}

void TitleCameraFrontOverHeadCut::Update()
{
	//		遷移時間
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Lerp(
								FIRST_POSITION, END_POSITION, m_elapsedTime);

	//		プロジェの作製
	m_titleCameraManager->CreateView(position, TARGET);

	//		フェードアウト
	m_titleCameraManager->FadeOut(m_elapsedTime);

	if (m_elapsedTime >= 1.0f)
	{
		//		
		m_titleCameraManager->ChangeState(TitleCameraManager::Back);
	}
}

void TitleCameraFrontOverHeadCut::Finalize()
{
	m_elapsedTime = 0.0f;
}
