/*
* @file		StartSceneState.cpp
* @brief	開始した状態
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "StartSceneState.h"

#include "../TitleFlowManager.h"

StartSceneState::StartSceneState(TitleFlowManager* titleFlowManager)
	:
	m_titleFlow(titleFlowManager)
{
}

StartSceneState::~StartSceneState()
{
}

void StartSceneState::Initialize()
{
}

void StartSceneState::Update()
{
	//		フェードインが終わったかどうか
	if (m_titleFlow->GetFadeInEndJudgement())
	{
		//		プレイ選択状態にする
		m_titleFlow->ChangeState(TitleFlowManager::State::PlayState);
	}
}

void StartSceneState::Finalize()
{
	//titleFlowManager->GetInformation()->SetKeyInput(false);

	////		メニューを使えるようにする
	m_titleFlow->MenuEnableMenu();
}
