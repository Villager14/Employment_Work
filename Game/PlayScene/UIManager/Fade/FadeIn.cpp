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
	m_time(0.0f),
	m_fadeinResetJudgement(true),
	m_fadeoutResetJudgement(false)
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

void FadeIn::Update(GameManager* gameManager)
{
	//		復活状態＆フェードアウトをしない状態の場合
	if (gameManager->GetRevivalJudgement() && !m_fadeoutResetJudgement)
	{
		m_fadeoutResetJudgement = true;

		m_time = 1.0f;
	}

	//		フェードインの処理
	if (m_fadeinResetJudgement)
	{
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		if (m_time > 1.0f)
		{
			m_fadeinResetJudgement = false;
		}
	}

	//		フェード王都の処理
	if (m_fadeoutResetJudgement)
	{
		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 4.0f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		if (m_time <= 0.0f)
		{
			m_fadeoutResetJudgement = false;

			//		復活状態を終了
			gameManager->SetRevivalJudgement(false);
			gameManager->SetDeathJudgement(false);
			m_fadeinResetJudgement = true;
		}
	}
}

void FadeIn::Render()
{
	//		背景の描画
	m_fadeRender->Render(m_time);
}

void FadeIn::Finalize()
{
}
