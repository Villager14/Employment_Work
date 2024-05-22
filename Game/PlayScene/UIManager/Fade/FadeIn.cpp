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
	m_time(0.0f)
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

void FadeIn::Update()
{
}

void FadeIn::Render()
{
	//		�o�ߎ���
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		�w�i�̕`��
	m_fadeRender->Render(m_time);
}

void FadeIn::Finalize()
{
}
