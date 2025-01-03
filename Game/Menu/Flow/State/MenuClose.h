/*
* @file		MenuClose.h
* @brief	メニューを閉じる時の処理
* @author	Morita
* @date		2024/07/11
*/

#pragma once

#include "../IMenu.h"

#include "../MenuFlow.h"

class MenuClose : public IMenu
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(menuFlow)	メニューの流れインスタンスのポインタ
	*/
	MenuClose(MenuFlow* menuFlow);

	//		デストラクタ
	~MenuClose();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

private:

	//		メニューの速度
	const float MENU_SPEED = 2.0f;

private:

	//		メニュー流れのインスタンスのポインタ
	MenuFlow* m_menuFlow;

	//		スケール
	float m_scale;

	//		移動
	float m_move;

	float m_mainClose;
};