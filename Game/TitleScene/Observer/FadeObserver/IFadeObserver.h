/*
* @file		IFadeObserver.h
* @brief	フェードオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "pch.h"

class IFadeObserver
{
public:

	//		デストラクタ
	~IFadeObserver() = default;

	//		シーン終了フェードアウト
	virtual void SceneEndFadeOut() = 0;

	//		フェードアウト
	virtual void FadeOut() = 0;
};