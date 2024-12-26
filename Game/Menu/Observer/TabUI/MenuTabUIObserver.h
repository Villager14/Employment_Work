/*
* @file		MenuTabUIObserver.h
* @brief	メニューのTabUIオブザーバー
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenuTabUIObserver.h"

class MenuTabUIObserver
{
public:

	//		コンストラクタ
	MenuTabUIObserver();

	//		デストラクタ
	~MenuTabUIObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuTabUIObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuTabUIObserver* observer);

	/*
	*	タブUIの移動
	*
	*	@param	(move)	移動量(0~1)
	*/
	void TabMove(float move);

	/*
	*	タブを使うかどうか
	*
	*	@param	(bool) true : 使う false : 使わない
	*/
	void TabUseJudgement(float judgement);

	//		全削除
	void Dalete();
private:

	std::vector<IMenuTabUIObserver*> m_observer;

};