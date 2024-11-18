/*
* @file		ResultStart.cpp
* @brief	リザルト開始処理
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultStart.h"

ResultStart::ResultStart(ResultManager* resultManager)
	:
	m_resultManager(resultManager)
{
}

ResultStart::~ResultStart()
{
}

void ResultStart::Initialize()
{
	//		タイトルのBGMの再生
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		メニューを使えないようにする
	m_resultManager->SetMenuUseJugement(false);
}

void ResultStart::Update()
{
	if (m_resultManager->GetPostEffectManager()->GetInformation()->
		FlagJudgement(PostEffectInformation::Flag::FadeInEnd))
	{
		//		状態を切り替える(数字移動状態)
		m_resultManager->ChangeState(ResultManager::State::NumberMove);
	}
}

void ResultStart::Render()
{
}

void ResultStart::Finalize()
{
	//		メニューを使えるようにする
	m_resultManager->SetMenuUseJugement(true);
}
