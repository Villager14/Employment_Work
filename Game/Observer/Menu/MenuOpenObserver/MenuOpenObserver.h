/*
* @file		MenuOpenObserver.cpp
* @brief	メニュー開くオブザーバー
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "IMenuOpenObserver.h"

class MenuOpenObserver
{
public:

	//		コンストラクタ
	MenuOpenObserver();

	//		デストラクタ
	~MenuOpenObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuOpenObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuOpenObserver* observer);

	//		メニューを開いている
	void MenuOpen();

	//		全削除
	void Dalete();
private:

	std::vector<IMenuOpenObserver*> m_observer;

};