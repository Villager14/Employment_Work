
#pragma once

#include "Game/Menu/MenuInformation.h"

#include "../Observer/MenuUseObserver/ITitleMenuUseObserver.h"

class TitleMenuManagement : public ITitleMenuUseObserver
{
public:

	/*
	*	タイトルメニューマネージャー
	* 
	*	@param	(information)	メニューの情報インスタンスのポインタ
	*/
	TitleMenuManagement(MenuInformation* information);

	//		デストラクタ
	~TitleMenuManagement();

	/*
	*	メニューを使っているかどうか
	* 
	*	@return true : 使っている false : 使っていない
	*/
	bool MenuUseJudgement();

	//		メニューを使用する
	void OpenMenu() override;

	//		メニューを使用できるようにする
	void EnableMenu() override;

	//		メニューを使用できないようにする
	void DisableMenu() override;

private:

	//		メニュー情報のインスタンスのポインタ
	MenuInformation* m_menuInformation;
};