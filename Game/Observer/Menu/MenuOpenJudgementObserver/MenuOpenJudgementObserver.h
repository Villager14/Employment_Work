/*
* @file		MenuOpenJudgementObserver.cpp
* @brief	メニュー開いているか判断するオブザーバー
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "IMenuOpenJudgementObserver.h"

class MenuOpenJudgementObserver
{
public:

	//		コンストラクタ
	MenuOpenJudgementObserver();

	//		デストラクタ
	~MenuOpenJudgementObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuOpenJudgementObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuOpenJudgementObserver* observer);

	//		メニューを開いている
	void MenuOpen();

	//		メニューを閉じている
	void MenuClose();

	//		全削除
	void Dalete();
private:

	std::vector<IMenuOpenJudgementObserver*> m_observer;

};