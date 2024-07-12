/*
* @file		MenuClose.cpp
* @brief	メニューを閉じる時の処理
* @author	Morita
* @date		2024/07/11
*/

#include "pch.h"

#include "MenuClose.h"

MenuClose::MenuClose(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
	m_scale(0.0f),
	m_move(0.0f),
	m_mainClose(0.0f)
{
}

MenuClose::~MenuClose()
{
}

void MenuClose::Initialize()
{
	m_move = 0.0f;
	m_scale = 0.0f;
	m_mainClose = 1.0f;
}

void MenuClose::Update()
{
	if (m_move < 1.0f)
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime() * m_menuManager->GetInformation()->MENU_SPEED;

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float transrationTime = m_menuManager->EasingBackUI(m_move);

		//		バー１の移動
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar1].position =
		{ 0.0f, Library::Lerp(300.0f, 13.0f, transrationTime) };

		//		バー２の移動
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar2].position =
		{ 0.0f, Library::Lerp(-300.0f, -13.0f, transrationTime) };

		//		背景のスケール縮小
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::BackGround].scale =
		{ 1.0f, 1 - transrationTime };
	}
	else
	{
			m_scale += LibrarySingleton::GetInstance()->GetElpsedTime() * m_menuManager->GetInformation()->MENU_SPEED;

			m_scale = Library::Clamp(m_scale, 0.0f, 1.0f);

			float transrationTime = m_menuManager->EasingBackUI(m_scale);

			//		バー１のスケール縮小
			(*m_menuManager->GetInformation()->GetStandardShader()
				->GetUIInformation())[MenuInformation::UIType::Bar1].scale =
			{ 1.0f - transrationTime, 1.0f };

			//		バー２のスケール縮小
			(*m_menuManager->GetInformation()->GetStandardShader()
				->GetUIInformation())[MenuInformation::UIType::Bar2].scale =
			{ 1.0f - transrationTime, 1.0f };
	}

	if (m_scale >= 1.0f)
	{
		m_menuManager->ChangState(MenuManager::MenuType::Start);
	}
}

void MenuClose::Render()
{
	//		メニューの背景の描画
	m_menuManager->MenuBackRneder();
}

void MenuClose::Finalize()
{
	//		メニューを終了する
	*m_menuManager->GetMenuJudgement() = false;
	m_menuManager->SetFirstAudioMenuJudgement(true);
}
