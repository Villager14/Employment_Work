/*
* @file		MenuTitleUIObserver.h
* @brief	メニューのタイトルUIオブザーバー
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenuTitleUIObserver.h"

class MenuTitleUIObserver
{
public:

	//		コンストラクタ
	MenuTitleUIObserver();

	//		デストラクタ
	~MenuTitleUIObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuTitleUIObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuTitleUIObserver* observer);

	/*
	*	タイトルの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	void TitleMoveProcess(float move);

	//		全削除
	void Dalete();
private:

	std::vector<IMenuTitleUIObserver*> m_observer;

};