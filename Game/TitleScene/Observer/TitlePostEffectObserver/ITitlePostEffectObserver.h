/*
* @file		ITitlePostEffectObserver.h
* @brief	タイトルポストエフェクトのオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/12
*/

#pragma once

class ITitlePostEffectObserver
{
public:

	//		デストラクタ
	~ITitlePostEffectObserver() = default;

	//		フェードイン
	virtual void FadeIn() = 0;

	//		フェードアウト
	virtual void FadeOut() = 0;

};