/*
* @file		TitlePostEffectObserver.h
* @brief	ポストエフェクトオブザーバー
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "ITitlePostEffectObserver.h"

class TitlePostEffectObserver
{
public:

	//		コンストラクタ
	TitlePostEffectObserver();

	//		デストラクタ
	~TitlePostEffectObserver();

	/*
	*	オブザーバーの追加
	* 
	*	@param	(observer)	オブザーバー
	*/
	void AddObserver(ITitlePostEffectObserver* observer);

	/*
	*	オブザーバーの削除
	* 
	*	@param	(observer)	オブザーバー
	*/
	void DeleteObserver(ITitlePostEffectObserver* observer);

	//		フェードイン
	void FadeIn();

	//		フェードアウト
	void FadeOut();

	//		デリート
	void Dalete();

private:

	//		オブザーバー
	std::vector<ITitlePostEffectObserver*> m_observer;

};
