/*
* @file		MenuStandby.cpp
* @brief	メニュー待機状態の処理
* @author	Morita
* @date		2024/12/24
*/

#include "pch.h"

#include "MenuStandby.h"

#include "../MenuFlowCommonProcess.h"

MenuStandby::MenuStandby(MenuFlow* menuFlow)
	:
	m_menuFlow(menuFlow)
{
}

MenuStandby::~MenuStandby()
{
}

void MenuStandby::Initialize()
{
}

void MenuStandby::Update()
{
	//		メニューを開始するか
	if (m_menuFlow->GetMenuOpenKeyJudgement())
	{
		//		メニューを開始する
		m_menuFlow->ChangState(MenuFlow::MenuType::Start);
	}
}

void MenuStandby::Render()
{
}

void MenuStandby::Finalize()
{
	//		カーソルを消す
	ShowCursor(FALSE);

	//		メニューを開始する
	m_menuFlow->SetMenuStartJudgement(true);

	//		メニューの開始キーを押していない状態にする
	m_menuFlow->SetMenuOpenKeyJudgement(false);
}
