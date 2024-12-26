/*
* @file		MenuFlow.h
* @brief	メニューの流れ
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenu.h"

#include "../Observer/BackGroundUI/MenuBackGroundUIObserver.h"
#include "../Observer/TabUI/MenuTabUIObserver.h"
#include "../Observer/SelectType/MenuSelectTypeObserver.h"
#include "../Observer/Title/MenuTitleUIObserver.h"
#include "../Observer/Icon/MenuIconUIObserver.h"

#include "../Observer/Mouse/IMenuMouseObserver.h"
#include "Library/Mouse/Observer/IMouseKeyInputObserver.h"
#include "../Observer/Collider/IMenuColliderObserver.h"
#include "Library/Keyboard/Observer/IKeyboardObserver.h"

class MenuFlowCommonProcess;

class MenuFlow : public IMenuMouseObserver,
	public IMouseKeyInputObserver,
	public IMenuColliderObserver,
	public IKeyboardObserver
{
public:

	MenuFlow();

	~MenuFlow();

	void Initialize();

	void Update();

	void Finalize();

	void CreateState();

	/*
	*	マウスのX座標の更新
	*
	*	@param	(x) x座標
	*/
	void MousePositionX(int x) override;

	/*
	*	マウスのY座標の更新
	*
	*	@param	(y) y座標
	*/
	void MousePositionY(int y) override;

	/*
	*	マウスの押した瞬間の処理
	*
	*	@param	(key)	押したキー
	*/
	void IsKeyPressed(KeyInputMouse::MouseList key) override;

	/*
	*	マウスの離した瞬間の処理
	*
	*	@param	(key)	離したキー
	*/
	void IsKeyReleased(KeyInputMouse::MouseList key) override;

	/*
	*	マウスの押し続けたの時の処理
	*
	*	@param	(key)	押し続けたキー
	*/
	void IsKeepPushing(KeyInputMouse::MouseList key) override;

	/*
	*	キーボードの押した瞬間の処理
	*
	*	@param	(key)	押したキー
	*/
	void IsKeyPressed(KeyboardList::KeyboardList key) override;

	/*
	*	キーボードの離した瞬間の処理
	*
	*	@param	(key)	押したキー
	*/
	void IsKeyReleased(KeyboardList::KeyboardList key) override;

	/*
	*	キーボードの押している時の処理
	*
	*	@param	(key)	押したキー
	*/
	void IsKeyState(KeyboardList::KeyboardList key) override;

	/*
	*	当たったUIのタイプ
	*
	*	@param	(type)	UIのタイプ
	*/
	void HitUIType(UISubType type) override;

	bool ButtonHitJudgement(UISubType type);

public:

	enum MenuType
	{
		Empty,
		Audio,
		Option,
		GamePlay,
		Standby,
		Start,
		Close,
	};

	enum KeyProcessFlag
	{
		None = 0b00000000,
		TabAudio = 1 << 0,				//		TabAudioの入力処理
		TabOption = 1 << 1,				//		TabOptionの入力処理
		TabGamePlay = 1 << 2,			//		TabGamePlayの入力処理
		ButtonExit = 1 << 3,			//		Exitボタンの入力処理
		ButtonMenuClose = 1 << 4,		//		MenuCloseボタンの入力処理
		K_MenuClose	= 1 << 5,			//		メニューを閉じる入力処理
	};

private:

	//		現在の状態
	IMenu* m_state;

	//		現在のタイプ
	MenuType m_type;

	//		次のタイプ
	MenuType m_nextType;

	//		共通処理
	std::unique_ptr<MenuFlowCommonProcess> m_commonProcess;

	//		メニューの状態の情報
	std::unordered_map<MenuType, std::unique_ptr<IMenu>> m_menuStateInformation;

	//		背景のUIオブザーバー
	std::unique_ptr<MenuBackGroundUIObserver> m_menuBackGroundUIObserver;

	//		TabUIオブザーバー
	std::unique_ptr<MenuTabUIObserver> m_menuTabUIObserver;

	//		選択タイプオブザーバー
	std::unique_ptr<MenuSelectTypeObserver> m_selectTypeObserver;

	//		タイトルUIオブザーバー
	std::unique_ptr<MenuTitleUIObserver> m_titleUIObserver;

	//		メニューアイコンオブザーバー
	std::unique_ptr<MenuIconUIObserver> m_menuIconUIObserver;

	//		マウス座標X
	int m_mousePositionX;

	//		マウス座標Y
	int m_mousePositoinY;

	//		初期処理
	bool m_firstProcess;

	//		フラグ
	int m_flag;

	UISubType m_uiSubType;

	//		メニューを終了するか判断する
	bool m_menuEndJudgemnet;

	//		メニューを開始するか判断する
	bool m_meneStartJudgement;

	//		メニューの開始キーを押したかどうか
	bool m_menuOpenKeyJudgement;

public:

	/*
	*	メニューの開始キーを押したかどうか設定する
	* 
	*	@param	(judgement) true : 押した false : 押していない
	*/
	void SetMenuOpenKeyJudgement(bool judgement) { m_menuOpenKeyJudgement = judgement; }

	/*
	*	メニューの開始キーを押したかどうか受け取る
	*
	*	@return true : 押した false : 押していない
	*/
	bool GetMenuOpenKeyJudgement() { return m_menuOpenKeyJudgement; }

	/*
	*	メニューを開始するか設定する
	* 
	*	@param	(judgement) true : 開始する false : 開始しない
	*/
	void SetMenuStartJudgement(bool judgement) { m_meneStartJudgement = judgement; }

	/*
	*	メニューを開始するか受け取る
	* 
	*	@return true : 開始する false : 開始しない
	*/
	bool GetMenuStartJudgement() { return m_meneStartJudgement; }

	/*
	*	メニューを終了するかを設定する
	*
	*	@param	(judgement)	true : 終了する false : 終了しない
	*/
	void SetMenuEndJudgement(bool judgement) { m_menuEndJudgemnet = judgement; }

	/*
	*	メニューを終了するかを受け取る
	* 
	*	@return true : 終了する false : 終了しない
	*/
	bool GetMenuEndJugement() { return m_menuEndJudgemnet; }

	/*
	*	フラグが立っているか
	*
	*	@param	(flag)	確認したいフラグ
	*	@return true : yes false : no
	*/
	bool FlagJudgement(KeyProcessFlag flag);

	/*
	*	フラグをOnにする
	*
	*	@param	(flag)	オンにしたいフラグ
	*/
	void TrueFlag(KeyProcessFlag flag);

	/*
	*	フラグをofにする
	*
	*	@param	(flag)	オフにしたいフラグ
	*/
	void FalseFlag(KeyProcessFlag flag);

	/*
	*	イージング関数通常UI用
	*
	*	@param	(time)	時間
	*/
	float EasingIcon(float time) { return 1.0f - pow(1.0f - time, 3.0f); }

	/*
	*	イージング関数背景用
	*
	*	@param	(time) 時間
	*/
	float EasingBackUI(float time) {
		if (time == 1.0f)
		{
			return 1.0f;
		}
		else
		{
			return 1.0f - pow(2.0f, -10.0f * time);
		}
	}

	//		タブの処理
	bool TabProcess(MenuType type);

	void NextScene(MenuType type);

	/*
	*	状態の切り替え
	*
	*	@param	(type)	状態
	*/
	void ChangState(MenuType type);

	/*
	*	メニューIconUIオブザーバーの追加
	* 
	*	@param	(observer)	オブザーバー
	*/
	void AddMenuIconUIObserver(IMenuIconUIObserver* observer) { m_menuIconUIObserver->AddObserver(observer); }

	void IconMoveProcess(float move) { m_menuIconUIObserver->IconMoveProcess(move); }

	bool GetFirstProcess() { return m_firstProcess; }

	void SetFirestProcess(bool judgement) { m_firstProcess = judgement; }

	MenuTitleUIObserver* GetTitleUIUObserver() { return m_titleUIObserver.get(); }

	MenuSelectTypeObserver* GetSelectTypeObserver() { return m_selectTypeObserver.get(); }

	MenuFlowCommonProcess* GetMenuFlowCommonProcess() { return m_commonProcess.get(); }

	void SetNextType(MenuType type) { m_nextType = type; }

	MenuType GetNextType() { return m_nextType; }

	MenuBackGroundUIObserver* GetMenuBackGroundUIObserver() { return m_menuBackGroundUIObserver.get(); }

	MenuTabUIObserver* GetMenuTabUIObserver() { return m_menuTabUIObserver.get(); }
};