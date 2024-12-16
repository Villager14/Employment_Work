/*
* @file		TitleCameraFrontAscendingCut.cpp
* @brief	タイトルカメラのフロント上昇カット
* @author	Morita
* @date		2024/12/15
*/

#include "pch.h"

#include "TitleCameraFrontAscendingCut.h"

#include "../TitleCameraManager.h"

TitleCameraFrontAscendingCut::TitleCameraFrontAscendingCut(TitleCameraManager* titleCameraManager)
	:
	m_titleCameraManager(titleCameraManager),
	m_elapsedTime(0.0f)
{
}

TitleCameraFrontAscendingCut::~TitleCameraFrontAscendingCut()
{
}

void TitleCameraFrontAscendingCut::Initialize()
{
	m_elapsedTime = 0.0f;
}

void TitleCameraFrontAscendingCut::Update()
{
	//		遷移時間
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Lerp(
								FIRST_POSITION, END_POSITION, m_elapsedTime);

	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Lerp(
								FIRST_TARGET, END_TARGET, m_elapsedTime);

	//		プロジェの作製
	m_titleCameraManager->CreateView(position, target);

	//		フェードアウト
	m_titleCameraManager->FadeOut(m_elapsedTime);

	if (m_elapsedTime >= 1.0f)
	{
		//		
		m_titleCameraManager->ChangeState(TitleCameraManager::OverHead);
	}
}

void TitleCameraFrontAscendingCut::Finalize()
{
	m_elapsedTime = 0.0f;
}
