/*
* @file		TitleUIObserver.h
* @brief	タイトルUIオブザーバー
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "ITitleMenuUseObserver.h"

class TitleMenuUseObserver
{
public:

	//		コンストラクタ
	TitleMenuUseObserver();

	//		デストラクタ
	~TitleMenuUseObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバー
	*/
	void AddObserver(ITitleMenuUseObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバー
	*/
	void DeleteObserver(ITitleMenuUseObserver* observer);

	//		メニューを使う
	void MenuUse();

	//		メニューを使用できるようにする
	void EnableMenu();

	//		メニューを使用できないようにする
	void DisableMenu();

	//		全削除
	void Dalete();

private:

	//		オブザーバー
	std::vector<ITitleMenuUseObserver*> m_observer;
};