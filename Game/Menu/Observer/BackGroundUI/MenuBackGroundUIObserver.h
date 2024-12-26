/*
* @file		MenuBackGroundUIObserver.h
* @brief	メニューの背景UIオブザーバー
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenuBackGroundUIObserver.h"

class MenuBackGroundUIObserver
{
public:

	//		コンストラクタ
	MenuBackGroundUIObserver();

	//		デストラクタ
	~MenuBackGroundUIObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuBackGroundUIObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuBackGroundUIObserver* observer);

	/*
	*	バーのスケールの変更
	*
	*	@param	(float scale)
	*/
	void BarScale(float scale);

	/*
	*	メニューの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	void MenuMoveProcess(float move);

	//		全削除
	void Dalete();
private:

	std::vector<IMenuBackGroundUIObserver*> m_observer;

};