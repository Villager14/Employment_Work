/*
* @file		IMenuOpenObserver.h
* @brief	メニューを開くオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/23
*/
#pragma once

#include "pch.h"

class IMenuOpenObserver
{
public:

	//		デストラクタ
	~IMenuOpenObserver() = default;

	//		メニューを開いている
	virtual void MenuOpen() = 0;
};