/*
* @file		FadeUI.cpp
* @brief	�t�F�[�hUI
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

	//		��]�V�F�[�_�[�̍쐻
	m_shader->Create(FADE_TEXTURE_PATH,
		FADE_VS_PATH, FADE_GS_PATH,
		FADE_PS_PATH, m_buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	m_buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	m_buffer.rotationMatrix = m_shader->GetRotationMatrix();

	m_time = 0.0f;
}

void FadeUI::Update()
{
	//		�t�F�[�h�A�E�g
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

	//		�t�F�[�h�C��
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

	//		UI�̕`��
	m_shader->Render(m_buffer);
}

void FadeUI::Finalize()
{
	m_shader.reset();
}

void FadeUI::FadeOutUse()
{
	//		�t�F�[�h�A�E�g�J�n
	m_fadeOutFlag = true;
}
