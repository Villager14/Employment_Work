/*
* @file		TitleGameExitObserver.h
* @brief	タイトルゲーム終了オブザーバー
* @author	Morita
* @date		2024/12/13
*/

#pragma once

#include "ITitleGameExitObserver.h"

class TitleGameExitObserver
{
public:

	//		コンストラクタ
	TitleGameExitObserver();

	//		デストラクタ
	~TitleGameExitObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバー
	*/
	void AddObserver(ITitleGameExitObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバー
	*/
	void DeleteObserver(ITitleGameExitObserver* observer);

	/*
	*	ゲーム終了
	*/
	void GameExit();

	//		全削除
	void Dalete();

private:

	//		オブザーバー
	std::vector<ITitleGameExitObserver*> m_observer;
};