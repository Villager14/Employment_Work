/*
* @file		MenuTitle.h
* @brief	メニューのタイトル
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "../MenuUITabEnums.h"

class MenuTitle
{
public:

	MenuTitle(AboveUI* aboveUI);

	~MenuTitle();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

	//		タイトルの取得
	void SetTitleType(MenuUITaype::UIType type);

	/*
	*	タイトルの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	void TitleMoveProcess(float move);

private:

	AboveUI* m_aboveUI;

	MenuUITaype::UIType m_titleType;

	//		移動量
	float m_move;
};