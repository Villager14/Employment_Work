/*
* @file		ChangeSceneState.cpp
* @brief	シーン切り替えをした状態
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "ChangeSceneState.h"

ChangeSceneState::ChangeSceneState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager)
{
}

ChangeSceneState::~ChangeSceneState()
{
}

void ChangeSceneState::Initialize()
{
	//		メニューを使えるようにする
	m_titleSelectManager->GetInformation()->SetMenuUseJudgement(false);

	//		効果音
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

	//		フェードアウトの処理
	m_titleSelectManager->GetPostEffectManager()->GetInformation()->
		TrueFlag(PostEffectInformation::Flag::SceneEndFade);
}

void ChangeSceneState::Update()
{
	if (m_titleSelectManager->GetPostEffectManager()->GetInformation()->FlagJudgement(PostEffectInformation::Flag::SceneEnd))
	{
		//		プレイシーンに切り替える
		m_titleSelectManager->GetInformation()->SetChangeSceneJudgement(true);
	}
}

void ChangeSceneState::Render()
{	
}

void ChangeSceneState::Finalize()
{
	m_titleSelectManager->GetInformation()->SetKeyInput(false);
}
