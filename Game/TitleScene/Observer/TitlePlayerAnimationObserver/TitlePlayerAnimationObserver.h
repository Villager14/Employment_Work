/*
* @file		TitlePlayerAnimationObserver.cpp
* @brief	プレイヤーのアニメションオブザーバー
* @author	Morita
* @date		2024/12/16
*/

#pragma once

#include "ITitlePlayerAnimationObserver.h"

class TitlePlayerAnimationObserver
{
public:

	//		コンストラクタ
	TitlePlayerAnimationObserver();

	//		デストラクタ
	~TitlePlayerAnimationObserver();

	/*
	*	オブザーバーの追加
	* 
	*	@param	(observer)	オブザーバー
	*/
	void AddObserver(ITitlePlayerAnimationObserver* observer);

	/*
	*	オブザーバーの削除
	* 
	*	@param	(observer)	オブザーバー
	*/
	void DeleteObserver(ITitlePlayerAnimationObserver* observer);

	//		デリート
	void Dalete();

	//		プレイ時のアニメーション
	void PlayAnimation();

	//		設定時のアニメーション
	void SettingAnimation();

	//		終了時のアニメーション
	void ExitAnimation();

private:

	//		オブザーバー
	std::vector<ITitlePlayerAnimationObserver*> m_observer;

};
