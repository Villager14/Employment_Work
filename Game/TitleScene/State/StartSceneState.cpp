/*
* @file		StartSceneState.cpp
* @brief	開始した状態
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "StartSceneState.h"


StartSceneState::StartSceneState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager)
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
	if (m_titleSelectManager->GetPostEffectManager()->GetInformation()->
		FlagJudgement(PostEffectInformation::Flag::FadeInEnd))
	{
		//		開始状態にする
		m_titleSelectManager->ChangeState(TitleInformation::State::PlayState);
	}
}

void StartSceneState::Render()
{
}

void StartSceneState::Finalize()
{
	m_titleSelectManager->GetInformation()->SetKeyInput(false);

	//		メニューを使えるようにする
	m_titleSelectManager->GetInformation()->SetMenuUseJudgement(true);
}
