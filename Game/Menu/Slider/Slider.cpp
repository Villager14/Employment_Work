/*
* @file		Slider.h
* @brief	�X���C�_�[�̏���
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "Slider.h"

Slider::Slider()
	:
	m_time(0.0f),
	m_fadeinResetJudgement(true),
	m_fadeoutResetJudgement(false),
	m_stayTime(0.0f),
	m_firstJudgement(true)
{
}

Slider::~Slider()
{
}

void Slider::Initialize()
{
	//		UI�`��̐���
	//m_fadeRender = std::make_unique<FadeRender>();

	//		UI�`��̍쐻
	//m_fadeRender->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
	//	{ 0.0f, 0.0f }, { 1.0f, 1.0f });
}

void Slider::Update(GameManager* gameManager)
{
	//		�I���̏ꍇ
	if (gameManager->GetEndJudgement())
	{
		m_stayTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		if (m_stayTime <= 1.0f) return;

		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 1.0f;

		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		//		�v���C�V�[���I�����̉��ʒ���
		MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

		if (m_time <= 0.0f)
		{
			//		���̃V�[���ɐ؂�ւ���
			gameManager->SetNextSceneJudgement(true);
		}

		return;
	}

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

		if (m_firstJudgement)
		{
			//		�v���C�V�[���J�n���̉��ʒ���
			MusicLibrary::GetInstance()->SceneLerpVolume(m_time);
		}

		if (m_time > 1.0f)
		{
			m_fadeinResetJudgement = false;
		}
	}

	//		�t�F�[�h�A�E�g�̏���
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

void Slider::Render()
{
	////		�w�i�̕`��
	//m_fadeRender->Render(m_time);
}

void Slider::Finalize()
{
}