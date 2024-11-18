/*
* @file		StartSceneState.cpp
* @brief	�J�n�������
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
		//		�J�n��Ԃɂ���
		m_titleSelectManager->ChangeState(TitleInformation::State::PlayState);
	}
}

void StartSceneState::Render()
{
}

void StartSceneState::Finalize()
{
	m_titleSelectManager->GetInformation()->SetKeyInput(false);

	//		���j���[���g����悤�ɂ���
	m_titleSelectManager->GetInformation()->SetMenuUseJudgement(true);
}
