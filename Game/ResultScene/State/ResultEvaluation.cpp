/*
* @file		ResultEvaluation.cpp
* @brief	リザルト評価処理
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "ResultEvaluation.h"

ResultEvaluation::ResultEvaluation(ResultManager* resultManager)
	:
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultEvaluation::~ResultEvaluation()
{
}

void ResultEvaluation::Initialize()
{
}

void ResultEvaluation::Update()
{
	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	float size = 0.0f;

	if (m_time < 0.5f)
	{
		size = 4.0f * m_time * m_time * m_time;
	}
	else
	{
		size = 1.0f - pow(-2.0f * m_time + 2.0f, 3.0f) / 2.0f;
	}

	//		評価
	(*m_resultManager->GetStandardShader()->GetUIInformation())[ResultManager::EvaluationUI].scale = { 1, size };


	if (m_time >= 1.0f)
	{
		//		状態を切り替える(待機状態)
		m_resultManager->ChangeState(ResultManager::State::Stay);
	}

	//	アニメーションのスキップ
	m_resultManager->AnimationSkip();
}

void ResultEvaluation::Render()
{
	//		評価
	m_resultManager->GetStandardShader()->Render(ResultManager::EvaluationUI);

	//		数字の描画
	m_resultManager->GetRiseNumberShader()->Render(4.0f);
}

void ResultEvaluation::Finalize()
{
}
