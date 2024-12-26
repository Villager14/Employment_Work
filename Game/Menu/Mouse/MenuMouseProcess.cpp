/*
* @file		MenuMouseProcess.h
* @brief	メニューのマウス処理
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuMouseProcess.h"

MenuMouseProcess::MenuMouseProcess()
{
	m_menuMouseObserver = std::make_unique<MenuMouseObserver>();
}

MenuMouseProcess::~MenuMouseProcess()
{
}

void MenuMouseProcess::Initialize()
{
	//		マウスを相対位置にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_ABSOLUTE);
}

void MenuMouseProcess::Update()
{
	//		マウスの座標
	int mousePositionX = 0;
	int mousePositionY = 0;

	//		マウスの現在座標を受け取る
	mousePositionX = LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x;
	mousePositionY = LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y;

	//		マウスの座標が更新した場合
	if (mousePositionX != m_mousePositionX)
	{
		//		マウスの座標の更新
		m_mousePositionX = mousePositionX;

		//		マウスのオブザーバーX座標の更新
		m_menuMouseObserver->MousePositionX(m_mousePositionX);
	}

	if (mousePositionY != m_mousePositionY)
	{
		//		マウスの座標の更新
		m_mousePositionY = mousePositionY;
		
		//		マウスのオブザーバーY座標の更新
		m_menuMouseObserver->MousePositionY(m_mousePositionY);
	}
}

void MenuMouseProcess::Finalize()
{
	//		マウス相対モード
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_mousePositionX = 0;

	m_mousePositionY = 0;
}
