
#pragma once

#include "Game/Menu/MenuInformation.h"

#include "../Observer/MenuUseObserver/ITitleMenuUseObserver.h"

#include "Game/Observer/Menu/MenuUsedObserver/MenuUsedObserver.h"

#include "Game/Observer/Menu/MenuOpenObserver/MenuOpenObserver.h"

class TitleMenuManagement : public ITitleMenuUseObserver
{
public:

	/*
	*	タイトルメニューマネージャー
	* 
	*	@param	(observer)　オブザーバー
	*/
	TitleMenuManagement(MenuUsedObserver* observer,
						MenuOpenObserver* menuOpenObserver);

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

	//		メニューを開いているか
	bool m_menuUseJudgement;

	//		メニューを使用するオブザーバー
	MenuUsedObserver* m_menuUsedObserver;

	//		メニューを開くオブザーバー
	MenuOpenObserver* m_menuOpenObserver;
public:

	/*
	*	メニューを使用しているか設定する
	* 
	*	@param	(judgement)	true : 使用している false : 使用していない
	*/
	void SetMenuUseJudgement(bool judgement) { m_menuUseJudgement = judgement; }

};