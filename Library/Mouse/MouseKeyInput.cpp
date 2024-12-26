/*
* @file		MouseKeyInput.cpp
* @brief	マウスのキー入力
* @author	Morita
* @date		2024/12/22
*/

#include "pch.h"

#include "MouseKeyInput.h"

MouseKeyInput::MouseKeyInput()
{
	//		マウスのキー入力オブザーバーの生成
	m_mouseKeyInputObserver = std::make_unique<MouseKeyInputObserver>();
}

MouseKeyInput::~MouseKeyInput()
{
}

void MouseKeyInput::Update()
{
	//		押したときの処理
	m_mouseKeyInputObserver->IsKeyPressed();

	//		離したときの処理
	m_mouseKeyInputObserver->IsKeyReleased();

	//		押し続けているときの処理
	m_mouseKeyInputObserver->IsKeepPushing();
}

void MouseKeyInput::Finalize()
{
	m_mouseKeyInputObserver->Dalete();
}
