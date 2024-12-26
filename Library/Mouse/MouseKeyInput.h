/*
* @file		MouseKeyInput.h
* @brief	マウスのキー入力
* @author	Morita
* @date		2024/12/22
*/

#pragma once

#include "Observer/MouseKeyInputObserver.h"

class MouseKeyInput
{
public:

	//		コンストラクタ
	MouseKeyInput();

	//		デストラクタ
	~MouseKeyInput();

	//		更新処理
	void Update();

	void Finalize();

private:

	//		マウスのキー入力オブザーバー
	std::unique_ptr<MouseKeyInputObserver> m_mouseKeyInputObserver;

public:

	/*
	*	マウスのキー入力オブザーバーのインスタンスのポインタ
	* 
	*	@return インスタンスのポインタ
	*/
	MouseKeyInputObserver* GetMouseKeyInputObserver() { return m_mouseKeyInputObserver.get(); }
};