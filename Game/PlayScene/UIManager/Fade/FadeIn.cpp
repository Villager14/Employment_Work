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
	m_fadeoutResetJudgement(false),
	m_stayTime(0.0f),
	m_firstJudgement(true)
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
	//		終了の場合
	if (gameManager->GetEndJudgement())
	{
		m_stayTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		if (m_stayTime <= 1.0f) return;

		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 1.0f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		//		プレイシーン終了時の音量調整
		MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

		if (m_time <= 0.0f)
		{
			//		次のシーンに切り替える
			gameManager->SetNextSceneJudgement(true);
		}

		return;
	}

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

		if (m_firstJudgement)
		{
			//		プレイシーン開始時の音量調整
			MusicLibrary::GetInstance()->SceneLerpVolume(m_time);
		}

		if (m_time > 1.0f)
		{
			m_fadeinResetJudgement = false;
		}
	}

	//		フェードアウトの処理
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
