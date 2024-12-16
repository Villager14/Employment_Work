/*
* @file		TitleSceneChange.cpp
* @brief	�^�C�g���̃V�[���ύX
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitleSceneChange.h"

TitleSceneChange::TitleSceneChange(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager)
{
}

TitleSceneChange::~TitleSceneChange()
{
}

void TitleSceneChange::FadeIn()
{
}

void TitleSceneChange::FadeOut()
{
	//		�V�[����؂�ւ���
	m_sceneManager->ChangeScene(SceneManager::Play);
}

void TitleSceneChange::GameExit()
{
	//		�Q�[�����I������
	m_sceneManager->GetInformation()->SetEndJudgement(true);
}
