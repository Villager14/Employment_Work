/*
* @file		MenuManager.h
* @brief	メニューのマネージャー
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include <unordered_map>

#include "UI/MenuUI.h"

#include "Flow/MenuFlow.h"

#include "Mouse/MenuMouseProcess.h"

#include "Collider/UIMouseCollider.h"

#include "Setting/GameSetting.h"

#include "Game/Observer/Menu/MenuOpenJudgementObserver/MenuOpenJudgementObserver.h"

#include "Game/Observer/Menu/MenuUsedObserver/IMenuUsedObserver.h"
#include "Game/Observer/Menu/MenuOpenObserver/IMenuOpenObserver.h"

class SceneManager;

class MenuManager : public IMenuUsedObserver,
					public IMenuOpenObserver
{
public:
	//		コンストラクタ
	MenuManager(SceneManager* sceneManager);

	//		デストラクタ
	~MenuManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		キーボードオブザーバーに登録する
	void KeyboardAddObserver();
	
	//		メニューを使うことができるか判断する
	void MenuUseJudgement(bool judgement) override;

	//		メニューを開いている
	void MenuOpen() override;

private:

	//		オブザーバーの追加
	void AddObserver();

	//		マウス入力のオブザーバーの追加
	void AddMouseObserver();

	//		キーボード入力のオブザーバーの追加
	void AddKeyboardObserver();

private:

	//		シーンマネージャ
	SceneManager* m_sceneManager;

	//		メニューUI
	std::unique_ptr<MenuUI> m_menuUI;

	//		メニューの流れ
	std::unique_ptr<MenuFlow> m_menuFlow;

	//		マウスの処理
	std::unique_ptr<MenuMouseProcess> m_mousePorcess;

	//		当たり判定
	std::unique_ptr<UIMouseCollider> m_collider;

	//		メニューオープンオブザーバー
	std::unique_ptr<MenuOpenJudgementObserver> m_menuOpenObserver;

	//		ゲームの設定
	std::unique_ptr<GameSetting> m_gameSetting;

	//		メニューを使用できるか
	bool m_menuUseJudgement;

	//		初めて音楽メニューを開いているかどうか
	bool m_firstAudioMenuJudgement;

	//		メニューを開くかどうか
	bool m_menuOpenJudgement;

public:

	/*
	*	Audioメニューをメニューを開いた時一度だけ行う処理を受け取る
	* 
	*	@retun	true : 行う false : 行わない
	*/
	bool GetFirstAudioMenuJudgement() { return m_firstAudioMenuJudgement; }

	/*
	*	Audioメニューをメニューを開いた時一度だけ行う処理を設定する
	*
	*	@param	(judgement)	true : 行う false : 行わない
	*/
	void SetFirstAudioMenuJudgement(bool judgement) { m_firstAudioMenuJudgement = judgement; }

	/*
	*	シーンマネージャーを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	SceneManager* GetSceneManager() { return m_sceneManager; }

	/*
	*	メニューオープンオブザーバーを追加する
	* 
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddMenuOpenObserver(IMenuOpenJudgementObserver* observer) { m_menuOpenObserver->AddObserver(observer); }

	/*
	*	カメラの視野角のオブザーバーを追加する
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddCameraViewAngle(IMenuCameraViewAngle* observer) { m_gameSetting->AddCameraViewAngle(observer); }

	/*
	*	カメラの速度のオブザーバーを追加する
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddCameraSpeed(IMenuCameraSpeed* observer) { m_gameSetting->AddCameraSpeed(observer); }
};