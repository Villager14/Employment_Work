/*
* @file		BackGroundMove.h
* @brief	”wŒi‚ÌˆÚ“®
* @author	Morita
* @date		2024/05/24
*/

#include "pch.h"

#include "BackGroundMove.h"

BackGroundMove::BackGroundMove()
	:
	m_time(0.0f),
	m_fadeinResetJudgement(true),
	m_fadeoutResetJudgement(false)
{
}

BackGroundMove::~BackGroundMove()
{
}

void BackGroundMove::Initialize()
{
	//		UI•`‰æ‚Ì¶¬
	m_backGroundMoveRender = std::make_unique<BackGroundMoveRender>();

	//		UI•`‰æ‚Ìì»
	m_backGroundMoveRender->Create(L"Resources/Texture/TitleScene/TitleBack.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });
}

void BackGroundMove::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;
}

void BackGroundMove::Render()
{
	//		”wŒi‚Ì•`‰æ
	m_backGroundMoveRender->Render(m_time);
}

void BackGroundMove::Finalize()
{
}
