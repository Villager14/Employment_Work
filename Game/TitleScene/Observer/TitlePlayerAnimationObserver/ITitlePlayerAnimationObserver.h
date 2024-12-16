/*
* @file		ITitlePlayerAnimationObserver.h
* @brief	タイトルのプレイヤーアニメーションオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/12
*/

#pragma once

class ITitlePlayerAnimationObserver
{
public:

	//		デストラクタ
	~ITitlePlayerAnimationObserver() = default;

	//		プレイ時のアニメーション
	virtual void PlayAnimation() = 0;

	//		設定時のアニメーション
	virtual void SettingAnimation() = 0;

	//		終了時のアニメーション
	virtual void ExitAnimation() = 0;
};