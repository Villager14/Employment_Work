/*
* @file		MenuIconUIObserver.cpp
* @brief	メニューのアイコンUIオブザーバー
* @author	Morita
* @date		2024/12/20
*/

#pragma once

#include "IMenuIconUIObserver.h"

class MenuIconUIObserver
{
public:

	//		コンストラクタ
	MenuIconUIObserver();

	//		デストラクタ
	~MenuIconUIObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuIconUIObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuIconUIObserver* observer);

	/*
	*	アイコンの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	void IconMoveProcess(float move);

	//		全削除
	void Dalete();
private:

	std::vector<IMenuIconUIObserver*> m_observer;

};