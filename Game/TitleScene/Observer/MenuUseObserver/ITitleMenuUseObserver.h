/*
* @file		ITitleMenuUseObserver.h
* @brief	メニューを使うかのオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/13
*/

#pragma once

#include "pch.h"

class ITitleMenuUseObserver
{
public:

	//		デストラクタ
	~ITitleMenuUseObserver() = default;


	//		メニューを使う
	virtual void OpenMenu() = 0;

	//		メニューを使用できるようにする
	virtual void EnableMenu() = 0;

	//		メニューを使用できないようにする
	virtual void DisableMenu() = 0;
};