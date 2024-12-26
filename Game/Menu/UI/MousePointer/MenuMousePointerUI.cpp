/*
* @file		MenuMousePointerUI.h
* @brief	メニューのマウスポインタ処理
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
	//		スタンダードシェーダーの生成
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	//		スタンダードシェーダーの初期化処理
	m_standardShader->Initialize();

	//		マウスポインタ
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
