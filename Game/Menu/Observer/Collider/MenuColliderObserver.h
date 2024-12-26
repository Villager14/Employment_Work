/*
* @file		MenuColliderObserver.h
* @brief	メニューの当たり判定オブザーバー
* @author	Morita
* @date		2024/12/22
*/

#pragma once

#include "IMenuColliderObserver.h"

class MenuColliderObserver
{
public:

	//		コンストラクタ
	MenuColliderObserver();

	//		デストラクタ
	~MenuColliderObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuColliderObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuColliderObserver* observer);

	/*
	*	当たったUIのタイプ
	*
	*	@param	(type)	UIのタイプ
	*/
	void HitUIType(UISubType type);

	//		全削除
	void Dalete();
private:

	std::vector<IMenuColliderObserver*> m_observer;

};