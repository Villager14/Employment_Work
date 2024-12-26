/*
* @file		IMenuUsedObserver.h
* @brief	メニューを使うことができるか判断するオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/23
*/
#pragma once

#include "pch.h"

class IMenuUsedObserver
{
public:

	//		デストラクタ
	~IMenuUsedObserver() = default;

	//		メニューを使うことができるか判断する
	virtual void MenuUseJudgement(bool judgement) = 0;
};