/*
* @file		MenuTitle.cpp
* @brief	メニューのタイトル
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuTitle.h"

MenuTitle::MenuTitle(AboveUI* aboveUI)
	:
	m_aboveUI(aboveUI)
{
}

MenuTitle::~MenuTitle()
{
}

void MenuTitle::Initialize()
{
}

void MenuTitle::Update()
{
}

void MenuTitle::Render()
{
	if (m_titleType ==MenuUITaype::UIType::Audio)
	{
		//m_aboveUI->Render(AboveUI::UIType::AudioTitle, m_move);
	}
	else if (m_titleType == MenuUITaype::UIType::Option)
	{
		m_aboveUI->Render(AboveUI::UIType::OptionTitle, m_move);
	}
	else if (m_titleType == MenuUITaype::UIType::GamePlay)
	{
		//m_aboveUI->Render(AboveUI::UIType::GamePlayTitle, m_move);
	}
}

void MenuTitle::Finalize()
{
}

void MenuTitle::SetTitleType(MenuUITaype::UIType type)
{
	m_titleType = type;
}

void MenuTitle::TitleMoveProcess(float move)
{
	m_move = move;
}
