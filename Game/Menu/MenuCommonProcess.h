/*
* @file		MenuCommonProcess.h
* @brief	メニューの共通処理
* @author	Morita
* @date		2024/08/05
*/

#pragma once

#include "MenuInformation.h"

class MenuCommonProcess
{
public:

	//		コンストラクタ
	MenuCommonProcess(MenuInformation* menuInformation);

	//		デストラクタ
	~MenuCommonProcess();

	//		メニューのESCボタンで閉じる処理
	bool MenuEscCloseProcess();

	//		四角の当たり判定
	bool BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max);

	/*
	*	選択したかどうか
	*
	*	@param	(type)	選択しないメニューの種類
	*/
	bool ButtonCollider(MenuInformation::MenuType type);

	/*
	*	スライダーの処理
	*
	*	@param	(type)	種類
	*/
	void SlideProcess(AboveUI::UIType type);

	void MousePointa();

private:

	MenuInformation* m_information;
};