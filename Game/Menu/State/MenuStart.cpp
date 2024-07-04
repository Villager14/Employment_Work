/*
* @file		MenuStart.cpp
* @brief	メニュースタート時の処理
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuStart.h"

MenuStart::MenuStart(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
	m_scale(0.0f),
	m_move(0.0f)
{
}

MenuStart::~MenuStart()
{
}

void MenuStart::Initialize()
{
}

void MenuStart::Update()
{
	if (m_scale < 1.0f)
	{

		m_scale += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_scale = Library::Clamp(m_scale, 0.0f, 1.0f);

		float move = 0.0f;

		if (m_scale == 1.0f)
		{
			move = 1.0f;
		}
		else
		{
			move = 1.0f - pow(2.0f, -10.0f * m_scale);
		}


		(*m_menuManager->GetUIRender())[m_menuManager->Bar1]->SetSize({ move, 1.0f });
		(*m_menuManager->GetUIRender())[m_menuManager->Bar2]->SetSize({ move, 1.0f });
	}
	else
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float move = 0.0f;

		if (m_move == 1.0f)
		{
			move = 1.0f;
		}
		else
		{
			move = 1.0f - pow(2.0f, -10.0f * m_move);
		}

		(*m_menuManager->GetUIRender())[m_menuManager->Bar1]->SetPosition({ 0.0f, Library::Lerp(13.0f, 300.0f, move) });
		(*m_menuManager->GetUIRender())[m_menuManager->Bar2]->SetPosition({ 0.0f, Library::Lerp(-13.0f, -300.0f, move) });
		(*m_menuManager->GetUIRender())[m_menuManager->BackGround]->SetSize({ 1.0f, move });
	}

	if (m_move >= 1.0f)
	{
		//		Audio状態にする
		m_menuManager->ChangState(m_menuManager->Audio);
	}
}

void MenuStart::Render()
{
	//		メニューの背景の描画
	m_menuManager->MenuBackRneder();
}

void MenuStart::Finalize()
{
}
