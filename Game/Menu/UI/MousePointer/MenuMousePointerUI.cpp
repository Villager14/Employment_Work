/*
* @file		MenuMousePointerUI.h
* @brief	���j���[�̃}�E�X�|�C���^����
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuMousePointerUI.h"

MenuMousePointerUI::MenuMousePointerUI()
{
}

MenuMousePointerUI::~MenuMousePointerUI()
{
}

void MenuMousePointerUI::Initialize()
{
	//		�X�^���_�[�h�V�F�[�_�[�̐���
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	//		�X�^���_�[�h�V�F�[�_�[�̏���������
	m_standardShader->Initialize();

	//		�}�E�X�|�C���^
	m_standardShader->CreateUIInformation(MOUSE_POINTA_FILE_PATH,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::MousePointa);
}

void MenuMousePointerUI::Render()
{
	m_standardShader->Render(UIType::MousePointa);
}

void MenuMousePointerUI::Finalize()
{
}
