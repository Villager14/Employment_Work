/*
* @file		TitleFlowManager.h
* @brief	タイトルの流れマネージャー
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "ITitleSelect.h"

#include "../Observer/TitlePostEffectObserver/ITitlePostEffectObserver.h"

#include "../Observer/TitleUIObserver/TitleUIObserver.h"

#include "../Observer/FadeObserver/FadeObserver.h"

#include "../Observer/GameExitObserver/TitleGameExitObserver.h"

#include "../Observer/MenuUseObserver/TitleMenuUseObserver.h"

#include "../Observer/TitlePlayerAnimationObserver/TitlePlayerAnimationObserver.h"

class TitleFlowManager : public ITitlePostEffectObserver
{
public:

	//		コンストラクタ
	TitleFlowManager();

	//		デストラクタ
	~TitleFlowManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		終了処理
	void Finalize();

	//		フェードイン
	void FadeIn() override;

	//		フェードアウト
	void FadeOut() override;

	//		キー入力
	void InputKey();

	/*
	*
	*	選択バーの移動処理
	*
	*	@return true : 移動処理を終了 false : 移動処理中OR移動処理をしていない
	*/
	bool SelectionBarMoveProcess();

	//		選択情報のリセット
	void SelectionInfromationReset();

public:

	//		状態
	enum State
	{
		PlayState,		//		プレイ状態
		EndState,		//		終了状態
		SettingState,	//		設定状態
		ChangState,		//		変更状態
		StartState		//		スタート状態
	};

	//		選択バーの移動向き
	enum SelectionBarMoveDirection
	{
		Not,		//		動いていない
		Up,			//		上に動く
		Down,		//		下に動く
	};

public:

	/*
	*	状態を変更する
	*
	*	@param	(state)	状態
	*/
	void ChangeState(State state);

private:

	//		移動速度
	const float MOVE_SPEED = 7.0f;

private:

	//		状態の情報
	std::unordered_map<State, std::unique_ptr<ITitleSelect>> m_stateInformation;

	//		現在の状態
	State m_state;

	//		状態を扱うインターフェイス
	ITitleSelect* m_iState;

	//		タイトルUIオブザーバー
	std::unique_ptr<TitleUIObserver> m_titleUIObserver;

	//		選択バーの移動方向
	SelectionBarMoveDirection m_selectionBarMoveDirection;

	//		フェードオブザーバー
	std::unique_ptr<FadeObserver> m_fadeObserver;

	//		ゲーム終了オブザーバー
	std::unique_ptr<TitleGameExitObserver> m_gameExitObserver;

	//		メニューを使用するオブザーバー
	std::unique_ptr<TitleMenuUseObserver> m_menuUseObserver;

	//		アニメーションオブザーバー
	std::unique_ptr<TitlePlayerAnimationObserver> m_animationObserver;

	//		キーを押しているか判断する
	bool m_keyInputJudgement;

	//		フェードインが終わっているかどうか
	bool m_fadeInEndJudgement;

	//		経過時間
	float m_time;

	//		スクロールホイールの値
	int m_scrollWheel;
public:

	/*
	*	フェードインが終わっているかどうか
	*
	*	@return true : 終わっている false : 終わっていない
	*/
	const bool GetFadeInEndJudgement() { return m_fadeInEndJudgement; }

	/*
	*	選択バーの移動方向
	*
	*	@return 移動方向
	*/
	SelectionBarMoveDirection GetSelectionBarMoveDirection() { return m_selectionBarMoveDirection; }

	/*
	*	タイトルUIオブザーバーを追加する
	*
	*	@param	(observer)	オブザーバー
	*/
	void AddITitleUIObserver(ITitleUIObserver* observer) { m_titleUIObserver->AddObserver(observer); }

	/*
	*	フェードオブザーバーを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	FadeObserver* GetFadeObserver() { return m_fadeObserver.get(); }

	/*
	*	タイトルのフェードオブザーバーを追加する
	*
	*	@param	(observer)	オブザーバー
	*/
	void AddIFadeObserver(IFadeObserver* observer) { m_fadeObserver->AddObserver(observer); }

	/*
	*	ゲーム終了オブザーバーを追加する
	*
	*	@param	(observer)	オブザーバー
	*/
	void AddGameExitObserver(ITitleGameExitObserver* observer) { m_gameExitObserver->AddObserver(observer); }

	//		ゲーム終了オブザーバー
	void GameExitObserver() { m_gameExitObserver->GameExit(); }

	/*
	*	メニュー使用オブザーバーを追加する
	*
	*	@param	(observer)	オブザーバー
	*/
	void AddMenUseObserver(ITitleMenuUseObserver* observer) { m_menuUseObserver->AddObserver(observer); }

	//		メニューを開く
	void MenuUse() { m_menuUseObserver->MenuUse(); }

	//		メニューを使用できるようにする
	void MenuEnableMenu() { m_menuUseObserver->EnableMenu(); }

	//		メニューを使用できないようにする
	void MenuDisableMenu() { m_menuUseObserver->DisableMenu(); }

	//		アニメーションオブザーバーの追加
	void AddAnimationObserver(ITitlePlayerAnimationObserver* observer) { m_animationObserver->AddObserver(observer); }

	/*
	*	アニメーションオブザーバのインスタンスのポインタ
	* 
	*	@return インスタンスのポインタ
	*/
	TitlePlayerAnimationObserver* AnimationObserver() { return m_animationObserver.get(); }
};