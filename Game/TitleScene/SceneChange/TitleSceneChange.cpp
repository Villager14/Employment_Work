/*
* @file		TitleSceneChange.cpp
* @brief	タイトルのシーン変更
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
	//		シーンを切り替える
	m_sceneManager->ChangeScene(SceneManager::Play);
}

void TitleSceneChange::GameExit()
{
	//		ゲームを終了する
	m_sceneManager->GetInformation()->SetEndJudgement(true);
}
