/*
* @file		FadeIn.h
* @brief	�t�F�[�h�̏���
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
	//		UI�`��̐���
	m_fadeRender = std::make_unique<FadeRender>();

	//		UI�`��̍쐻
	m_fadeRender->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });
}

void FadeIn::Update(GameManager* gameManager)
{
	//		������ԁ��t�F�[�h�A�E�g�����Ȃ���Ԃ̏ꍇ
	if (gameManager->GetRevivalJudgement() && !m_fadeoutResetJudgement)
	{
		m_fadeoutResetJudgement = true;

		m_time = 1.0f;
	}

	//		�t�F�[�h�C���̏���
	if (m_fadeinResetJudgement)
	{
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		if (m_time > 1.0f)
		{
			m_fadeinResetJudgement = false;
		}
	}

	//		�t�F�[�h���s�̏���
	if (m_fadeoutResetJudgement)
	{
		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 4.0f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		if (m_time <= 0.0f)
		{
			m_fadeoutResetJudgement = false;

			//		������Ԃ��I��
			gameManager->SetRevivalJudgement(false);
			gameManager->SetDeathJudgement(false);
			m_fadeinResetJudgement = true;
		}
	}
}

void FadeIn::Render()
{
	//		�w�i�̕`��
	m_fadeRender->Render(m_time);
}

void FadeIn::Finalize()
{
}
