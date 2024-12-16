/*
* @file		ChangeSceneState.cpp
* @brief	シーン切り替えをした状態
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "ChangeSceneState.h"

ChangeSceneState::ChangeSceneState(TitleFlowManager* titleFlowManager)
	:
	m_titleFlow(titleFlowManager)
{
}

ChangeSceneState::~ChangeSceneState()
{
}

void ChangeSceneState::Initialize()
{
	//		メニューを使用できないようにする
	m_titleFlow->MenuDisableMenu();

	//		効果音
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);
}

void ChangeSceneState::Update()
{
	//		フェードアウトを開始する
	m_titleFlow->GetFadeObserver()->SceneEndFadeOut();
}

void ChangeSceneState::Finalize()
{
	//m_titleSelectManager->GetInformation()->SetKeyInput(false);
}
