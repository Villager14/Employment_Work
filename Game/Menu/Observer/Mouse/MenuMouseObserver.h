/*
* @file		MenuMouseObserver.h
* @brief	メニューのマウスオブザーバー
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenuMouseObserver.h"

class MenuMouseObserver
{
public:

	//		コンストラクタ
	MenuMouseObserver();

	//		デストラクタ
	~MenuMouseObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuMouseObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuMouseObserver* observer);

	/*
	*	マウスのX座標の更新
	*
	*	@param	(x) x座標
	*/
	void MousePositionX(int x);

	/*
	*	マウスのY座標の更新
	*
	*	@param	(y) y座標
	*/
	void MousePositionY(int y);


	//		全削除
	void Dalete();
private:

	std::vector<IMenuMouseObserver*> m_observer;

};