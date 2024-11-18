/*
* @file		CountDown.h
* @brief	�J�E���g�_�E���̏���
* @author	Morita
* @date		2024/11/01
*/

#include "pch.h"

#include "CountDown.h"

CountDown::CountDown()
	:
	m_time(0.0f),
	m_alpha(0.0f)
{
}

CountDown::~CountDown()
{
}

void CountDown::Initialize()
{
	//		�t�F�[�h�`��̐���
	m_numberAlpha = std::make_unique<UIRenderManager>();

	m_numberAlpha->Create(COUNT_DOWN_TEXTURE_PATH,
		NUMBER_ALPHA_VS_PATH, NUMBER_ALPHA_GS_PATH,
		NUMBER_ALPHA_PS_PATH, buffer,
		COUNT_DOWN_POSITION, { 0.8f, 0.8f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	buffer.rotationMatrix = m_numberAlpha->GetRotationMatrix();

	m_time = 0.0f;
	m_alpha = 0.0f;
}

void CountDown::Update(float time)
{
	m_time = time;
}

void CountDown::Render()
{
	if (m_time > MAX_TIME ||
		m_time < MIN_TIME) return;

	buffer.alpha = sinf(m_time - static_cast<float>(static_cast<int>(m_time))) / 2.0f;
	buffer.time = static_cast<int>(m_time);

	m_numberAlpha->Render(buffer);
}

void CountDown::Finalize()
{
	m_numberAlpha.reset();
}
