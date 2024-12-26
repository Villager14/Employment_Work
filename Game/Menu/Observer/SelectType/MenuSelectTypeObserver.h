/*
* @file		MenuSelectTypeObserver.h
* @brief	メニューの選択オブザーバー
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenuSelectTypeObserver.h"

class MenuSelectTypeObserver
{
public:

	//		コンストラクタ
	MenuSelectTypeObserver();

	//		デストラクタ
	~MenuSelectTypeObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuSelectTypeObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuSelectTypeObserver* observer);

	/*
	*	選択タイプ
	*
	*	@param	(type)　タイプ
	*/
	void SelectType(MenuUITaype::UIType type);

	//		全削除
	void Dalete();

private:

	std::vector<IMenuSelectTypeObserver*> m_observer;

};