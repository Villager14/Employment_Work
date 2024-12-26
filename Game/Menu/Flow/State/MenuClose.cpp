/*
* @file		MenuClose.cpp
* @brief	メニューを閉じる時の処理
* @author	Morita
* @date		2024/07/11
*/

#include "pch.h"

#include "MenuClose.h"

MenuClose::MenuClose(MenuFlow* menuFlow)
	:
	m_menuFlow(menuFlow),
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

	//		オーディオを選択する
	m_menuFlow->GetSelectTypeObserver()->SelectType(MenuUITaype::Close);

	//		TabUIを使用出来ないようにする
	m_menuFlow->GetMenuTabUIObserver()->TabUseJudgement(false);
}

void MenuClose::Update()
{
	if (m_move < 1.0f)
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime() * MENU_SPEED;

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float transrationTime = m_menuFlow->EasingBackUI(m_move);

		//		背景の移動処理
		m_menuFlow->GetMenuBackGroundUIObserver()->MenuMoveProcess(1.0f - transrationTime);

		/*
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
		*/
	}
	else
	{
		m_scale += LibrarySingleton::GetInstance()->GetElpsedTime() * MENU_SPEED;

			m_scale = Library::Clamp(m_scale, 0.0f, 1.0f);

			float transrationTime = m_menuFlow->EasingBackUI(m_scale);

			//		背景のバーのスケールの変更
			m_menuFlow->GetMenuBackGroundUIObserver()->BarScale(1.0f - transrationTime);

			/*
			//		バー１のスケール縮小
			(*m_menuManager->GetInformation()->GetStandardShader()
				->GetUIInformation())[MenuInformation::UIType::Bar1].scale =
			{ 1.0f - transrationTime, 1.0f };

			//		バー２のスケール縮小
			(*m_menuManager->GetInformation()->GetStandardShader()
				->GetUIInformation())[MenuInformation::UIType::Bar2].scale =
			{ 1.0f - transrationTime, 1.0f };
		*/
	}

	if (m_scale >= 1.0f)
	{
		m_menuFlow->ChangState(MenuFlow::Standby);
	}
	
}

void MenuClose::Render()
{
}

void MenuClose::Finalize()
{
	//		メニューを終了する
	m_menuFlow->SetMenuEndJudgement(true);
}
