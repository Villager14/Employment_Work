/*
* @file		ITitleUIObserver.h
* @brief	タイトルUIオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "pch.h"

class ITitleUIObserver
{
public:

	//		デストラクタ
	~ITitleUIObserver() = default;

	/*
	*	下を選択した
	* 
	*	@param	(processingTime)	処理時間
	*/
	virtual void DownSelect(float processingTime) = 0;

	/*
	*	上を選択した
	*
	*	@param	(processingTime)	処理時間
	*/
	virtual void UpSelect(float processingTime) = 0;
};