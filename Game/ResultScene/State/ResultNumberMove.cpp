/*
* @file		ResultNumberMove.cpp
* @brief	リザルト数字移動処理
* @author	Morita
* @date		2024/05/29
*/

#include "pch.h"

#include "ResultNumberMove.h"

ResultNumberMove::ResultNumberMove(ResultManager* resultManager)
	:
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultNumberMove::~ResultNumberMove()
{
}

void ResultNumberMove::Initialize()
{

}

void ResultNumberMove::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_time = Library::Clamp(m_time, 0.0f, 4.0f);

	if (m_time >= 4.0f)
	{
		//		状態を切り替える(評価状態)
		m_resultManager->ChangeState(m_resultManager->GetEvaluation());
	}

	//	アニメーションのスキップ
	m_resultManager->AnimationSkip();
}

void ResultNumberMove::Render()
{
	//		UI背景の描画
	//m_resultManager->UIViewProcess(0);

	m_resultManager->NumberRender(m_time);
}

void ResultNumberMove::Finalize()
{
}
