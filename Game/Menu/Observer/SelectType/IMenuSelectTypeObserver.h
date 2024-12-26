/*
* @file		iMenuSelectTypeObserver.h
* @brief	メニューの選択タイプオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/19
*/
#pragma once

#include "pch.h"

#include "../../UI/MenuUITabEnums.h"

class IMenuSelectTypeObserver
{
public:

	//		デストラクタ
	~IMenuSelectTypeObserver() = default;

	/*
	*	選択タイプ
	* 
	*	@param	(type)　タイプ
	*/
	virtual void SelectType(MenuUITaype::UIType type) = 0;
};