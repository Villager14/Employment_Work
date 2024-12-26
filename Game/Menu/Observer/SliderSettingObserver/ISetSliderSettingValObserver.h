/*
* @file		ISetSliderSettignValObserver.h
* @brief	スライダーの値を設定に送るオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/26
*/

#pragma once

#include "pch.h"

class ISetSliderSettingValObserver
{
public:

	//		デストラクタ
	~ISetSliderSettingValObserver() = default;

	/*
	*	視野角の値を受け取る
	* 
	*	@param	(val)　視野の割合
	*/
	virtual void SetFov(float val) = 0;

	/*
	*	マウス感度を受け取る
	*
	*	@param	(val)　感度の割合
	*/
	virtual void SetMouseSensitivity(float val) = 0;
};