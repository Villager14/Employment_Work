/*
* @file		FadeIn.h
* @brief	フェードの処理
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
	//		UI描画の生成
	m_fadeRender = std::make_unique<FadeRender>();

	//		UI描画の作製
	m_fadeRender->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });
}

void FadeIn::Update()
{
}

void FadeIn::Render()
{
	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		背景の描画
	m_fadeRender->Render(m_time);
}

void FadeIn::Finalize()
{
}
