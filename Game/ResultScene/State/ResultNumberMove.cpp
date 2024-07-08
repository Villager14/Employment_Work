/*
* @file		ResultNumberMove.cpp
* @brief	ƒŠƒUƒ‹ƒg”ŽšˆÚ“®ˆ—
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
		//		ó‘Ô‚ðØ‚è‘Ö‚¦‚é(•]‰¿ó‘Ô)
		m_resultManager->ChangeState(ResultManager::State::Evaluation);
	}

	//	ƒAƒjƒ[ƒVƒ‡ƒ“‚ÌƒXƒLƒbƒv
	m_resultManager->AnimationSkip();
}

void ResultNumberMove::Render()
{
	//		UI”wŒi‚Ì•`‰æ
	//m_resultManager->UIViewProcess(0);

	//		”Žš‚Ì•`‰æ
	m_resultManager->GetRiseNumberShader()->Render(m_time);

	//m_resultManager->NumberRender(m_time);
}

void ResultNumberMove::Finalize()
{
}
