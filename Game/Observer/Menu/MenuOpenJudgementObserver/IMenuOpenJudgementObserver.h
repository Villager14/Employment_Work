/*
* @file		IMenuOpenJudgementObserver.h
* @brief	メニューが開いているか判断するオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/23
*/
#pragma once

#include "pch.h"

class IMenuOpenJudgementObserver
{
public:

	//		デストラクタ
	~IMenuOpenJudgementObserver() = default;

	//		メニューを開いている
	virtual void MenuOpen() = 0;

	//		メニューを閉じている
	virtual void MenuClose() = 0;
};