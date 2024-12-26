/*
* @file		IMenuTabUIObserver.h
* @brief	メニューのTabUIオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/19
*/
#pragma once

#include "pch.h"

#include "../../UI/MenuUITabEnums.h"

class IMenuTabUIObserver
{
public:

	//		デストラクタ
	~IMenuTabUIObserver() = default;

	/*
	*	タブUIの移動
	*
	*	@param	(move)	移動量(0~1)
	*/
	virtual void TabMove(float move) = 0;

	/*
	*	タブを使うかどうか
	* 
	*	@param	(bool) true : 使う false : 使わない
	*/
	virtual void TabUseJudgement(float judgement) = 0;
};