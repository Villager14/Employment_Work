/*
* @file		ITitleGameExitObserver.h
* @brief	タイトルゲーム終了オブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "pch.h"

class ITitleGameExitObserver
{
public:

	//		デストラクタ
	~ITitleGameExitObserver() = default;

	//		ゲームを終了する
	virtual void GameExit() = 0;
};