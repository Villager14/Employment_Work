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
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultStart::~ResultStart()
{
}

void ResultStart::Initialize()
{
}

void ResultStart::Update()
{
	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_time >= 1.0f)
	{
		//		状態を切り替える(数字移動状態)
		m_resultManager->ChangeState(m_resultManager->GetNumberMove());
	}
}

void ResultStart::Render()
{
	//		UI背景の描画
	//m_resultManager->UIViewProcess(0);

	//		フェード
	m_resultManager->FadeViewProcess(m_time);
}

void ResultStart::Finalize()
{
}
