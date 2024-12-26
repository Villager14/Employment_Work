/*
* @file		MenuStandby.h
* @brief	メニュー待機状態の処理
* @author	Morita
* @date		2024/12/24
*/

#pragma once

#include "../IMenu.h"

#include "../MenuFlow.h"

class MenuStandby : public IMenu
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(menuFlow)	メニューの流れインスタンスのポインタ
	*/
	MenuStandby(MenuFlow* menuFlow);

	//		デストラクタ
	~MenuStandby();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

private:

	//		メニュー流れのインスタンスのポインタ
	MenuFlow* m_menuFlow;
};