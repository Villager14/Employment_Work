/*
* @file		FadeObserver.h
* @brief	タイトルUIオブザーバー
* @author	Morita
* @date		2024/12/12
*/


#pragma once

#include "IFadeObserver.h"

class FadeObserver
{
public:

	//		コンストラクタ
	FadeObserver();

	//		デストラクタ
	~FadeObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバー
	*/
	void AddObserver(IFadeObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバー
	*/
	void DeleteObserver(IFadeObserver* observer);

	//		フェードアウト
	void SceneEndFadeOut();

	//		フェードアウト
	void FadeOut();

	//		全削除
	void Dalete();

private:

	//		オブザーバー
	std::vector<IFadeObserver*> m_observer;
};