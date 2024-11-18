/*
* @file		ResultEnd.cpp
* @brief	リザルト終了処理
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "ResultEnd.h"

ResultEnd::ResultEnd(ResultManager* resultManager)
	:
	m_resultManager(resultManager)
{
}

ResultEnd::~ResultEnd()
{
}

void ResultEnd::Initialize()
{
	//		メニューを使えないようにする
	m_resultManager->SetMenuUseJugement(false);

	//		フェードアウトの処理
	m_resultManager->GetPostEffectManager()->GetInformation()->
		TrueFlag(PostEffectInformation::Flag::SceneEndFade);
}

void ResultEnd::Update()
{
	if (m_resultManager->GetPostEffectManager()->GetInformation()->FlagJudgement(PostEffectInformation::Flag::SceneEnd))
	{
		//		プレイシーンに切り替える
		m_resultManager->GetInformation()->SetChangeSceneJudgement(true);
	}
}

void ResultEnd::Render()
{
	//		評価
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::EvaluationUI);

	//		遷移誘導画像
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::Button);

	//		数字の描画
	m_resultManager->GetInformation()->GetRiseNumber()->Render(4.0f);
}

void ResultEnd::Finalize()
{
}
