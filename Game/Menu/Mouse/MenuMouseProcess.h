/*
* @file		MenuMouseProcess.h
* @brief	メニューのマウス処理
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "../Observer/Mouse/MenuMouseObserver.h"

class MenuMouseProcess
{
public:

	//		コンストラクタ
	MenuMouseProcess();

	//		デストラクタ
	~MenuMouseProcess();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		終了処理
	void Finalize();

private:
	//		メニューマウスオブザーバー
	std::unique_ptr<MenuMouseObserver> m_menuMouseObserver;

	//		マウスの座標X
	int m_mousePositionX;

	//		マウスの座標Y
	int m_mousePositionY;

public:

	/*
	*	マウスオブザーバーに追加する
	* 
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddMenuMouseObserver(IMenuMouseObserver* observer) { m_menuMouseObserver->AddObserver(observer); }

};