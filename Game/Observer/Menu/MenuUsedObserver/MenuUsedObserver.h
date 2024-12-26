/*
* @file		MenuUsedObserver.h
* @brief	メニューを使えるか判断するオブザーバー
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "IMenuUsedObserver.h"

class MenuUsedObserver
{
public:

	//		コンストラクタ
	MenuUsedObserver();

	//		デストラクタ
	~MenuUsedObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuUsedObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuUsedObserver* observer);

	//		メニューを使うことができるか判断する
	void MenuUseJudgement(bool judgement);

	//		全削除
	void Dalete();
private:

	std::vector<IMenuUsedObserver*> m_observer;

};