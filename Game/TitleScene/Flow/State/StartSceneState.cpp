/*
* @file		StartSceneState.cpp
* @brief	�J�n�������
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
	//		�t�F�[�h�C�����I��������ǂ���
	if (m_titleFlow->GetFadeInEndJudgement())
	{
		//		�v���C�I����Ԃɂ���
		m_titleFlow->ChangeState(TitleFlowManager::State::PlayState);
	}
}

void StartSceneState::Finalize()
{
	//titleFlowManager->GetInformation()->SetKeyInput(false);

	////		���j���[���g����悤�ɂ���
	m_titleFlow->MenuEnableMenu();
}
