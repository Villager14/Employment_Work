/*
* @file		FadeIn.h
* @brief	ƒtƒF[ƒh‚Ìˆ—
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "FadeIn.h"

FadeIn::FadeIn()
	:
	m_time(0.0f)
{
}

FadeIn::~FadeIn()
{
}

void FadeIn::Initialize()
{
	//		UI•`‰æ‚Ì¶¬
	m_fadeRender = std::make_unique<FadeRender>();

	//		UI•`‰æ‚Ìì»
	m_fadeRender->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });
}

void FadeIn::Update()
{
}

void FadeIn::Render()
{
	//		Œo‰ßŠÔ
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		”wŒi‚Ì•`‰æ
	m_fadeRender->Render(m_time);
}

void FadeIn::Finalize()
{
}
