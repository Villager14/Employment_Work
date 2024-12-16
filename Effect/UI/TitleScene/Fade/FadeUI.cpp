/*
* @file		FadeUI.cpp
* @brief	フェードUI
* @author	Morita
* @date		2024/12/15
*/

#include "pch.h"

#include "FadeUI.h"

FadeUI::FadeUI()
	:
	m_time(0.0f),
	m_fadeOutFlag(false),
	m_fadeInFlag(false)
{
}

FadeUI::~FadeUI()
{
}

void FadeUI::Initialize()
{
	m_shader = std::make_unique<UIRenderManager>();

	//		回転シェーダーの作製
	m_shader->Create(FADE_TEXTURE_PATH,
		FADE_VS_PATH, FADE_GS_PATH,
		FADE_PS_PATH, m_buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		ウィンドウサイズを設定する
	m_buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	m_buffer.rotationMatrix = m_shader->GetRotationMatrix();

	m_time = 0.0f;
}

void FadeUI::Update()
{
	//		フェードアウト
	if (m_fadeOutFlag && !m_fadeInFlag)
	{
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		if (m_time >= 1.0f)
		{
			m_time = 1.0f;

			m_fadeInFlag = true;
			m_fadeOutFlag = false;
		}
	}

	//		フェードイン
	if (m_fadeInFlag && !m_fadeOutFlag)
	{
		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		if (m_time <= 0.0f)
		{
			m_fadeInFlag = false;
			m_time = 0.0f;
		}
	}
}

void FadeUI::Render()
{
	m_buffer.time = m_time;

	//		UIの描画
	m_shader->Render(m_buffer);
}

void FadeUI::Finalize()
{
	m_shader.reset();
}

void FadeUI::FadeOutUse()
{
	//		フェードアウト開始
	m_fadeOutFlag = true;
}
