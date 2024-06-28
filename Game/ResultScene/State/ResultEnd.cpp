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
	m_resultManager(resultManager),
	m_time(1.0f)
{
}

ResultEnd::~ResultEnd()
{
}

void ResultEnd::Initialize()
{
}

void ResultEnd::Update()
{
	m_time -= LibrarySingleton::GetInstance()->GetElpsedTime();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	if (m_time <= 0.0f)
	{
		//		タイトルシーンへ
		m_resultManager->SetChangeSceneJudgement(true);
	}
}

void ResultEnd::Render()
{
	//		UI背景の描画
	m_resultManager->UIViewProcess(1);

	//		ボタン
	m_resultManager->UIViewProcess(2);

	//		数字の描画
	m_resultManager->NumberRender(4.0f);

	m_resultManager->FadeViewProcess(m_time);
}

void ResultEnd::Finalize()
{
}
