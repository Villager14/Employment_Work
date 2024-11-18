/*
* @file		MenuSelect.h
* @brief	���j���[�̑I������
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "MenuSelect.h"

MenuSelect::MenuSelect()
	:
	m_time(0.0f)
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(SELECT_TEXTURE,
		SELECT_MENU_VS_TEXTURE,
		SELECT_MENU_GS_TEXTURE,
		SELECT_MENU_PS_TEXTURE,
		m_constBuffer,
		{ 0.0f, 0.0f , }, { 1.0f,1.0f },
		CENTER_POINT::MIDDLE_CENTER);
}

MenuSelect::~MenuSelect()
{
}

void MenuSelect::Initialize()
{
	//		��]�s��𑗂�
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		�E�B���h�E�T�C�Y�𑗂�
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

void MenuSelect::Render(DirectX::SimpleMath::Vector2 position)
{
	//		�o�ߎ���
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�R���X�g�o�b�t�@�̍X�V
	m_constBuffer.time = { m_time, 0.0f, 0.0f, 0.0f };

	//		�����ݒ肷��
	m_shader->SetPosition(position);

	//		�`��
	m_shader->Render(m_constBuffer);
}
