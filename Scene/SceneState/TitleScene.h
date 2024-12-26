/*
* @file		TitleScene.h
* @brief	タイトルシーン
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Scene/IScene.h"

#include "../SceneManager.h"

#include "Game/TitleScene/UI/TitleUI.h"

#include "Game/TitleScene/Flow/TitleFlowManager.h"

#include "Game/TitleScene/PostEffect/TitlePostEffectManager.h"

#include "Game/TitleScene/SceneChange/TitleSceneChange.h"

#include "Game/TitleScene/Menu/TitleMenuManagement.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Game/TitleScene/Player/TItlePlayer.h"

#include "Game/TitleScene/Effect/TitleEffectManager.h"

#include "Game/TitleScene/Camera/TitleCameraManager.h"

#include "Game/Observer/Menu/MenuOpenJudgementObserver/IMenuOpenJudgementObserver.h"

#include "Game/Observer/Menu/MenuUsedObserver/MenuUsedObserver.h"

#include "Game/Observer/Menu/MenuOpenObserver/MenuOpenObserver.h"

class SceneManager;

class TitleScene : public IScene,
				   public IMenuOpenJudgementObserver
{
public:

	//		コンストラクタ
	TitleScene(SceneManager* sceneManager);

	//		デストラクタ
	~TitleScene();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	//		オブザーバーの追加
	void AddObserver();

	//		メニューを開いている
	void MenuOpen() override;

	//		メニューを閉じている
	void MenuClose() override;

private:
	//		シーンマネージャーのインスタンスのポインタ
	SceneManager* m_sceneManager;

	//		タイトルのUI処理
	std::unique_ptr<TitleUI> m_titleUI;

	//		タイトルの流れマネージャー
	std::unique_ptr<TitleFlowManager> m_titleFlowManager;

	//		タイトルポストエフェクトマネージャー
	std::unique_ptr<TitlePostEffectManager> m_titlePostEffectManager;

	//		タイトルシーンのチェンジ
	std::unique_ptr<TitleSceneChange> m_titleSceneChange;

	//		メニューマネジメント
	std::unique_ptr<TitleMenuManagement> m_menuManagement;

	//		オブジェクトマネージャー
	std::unique_ptr<ObjectManager> m_objectManager;

	//		タイトルのプレイヤー
	std::unique_ptr<TitlePlayer> m_player;

	//		タイトルエフェクトマネージャー
	std::unique_ptr<TitleEffectManager> m_titleEffectManager;

	//		カメラマネージャー
	std::unique_ptr<TitleCameraManager> m_cameraManager;

	//		メニューを使うか判断するオブザーバー
	std::unique_ptr<MenuUsedObserver> m_menuUsedObserver;

	//		メニューを開くオブザーバー
	std::unique_ptr<MenuOpenObserver> m_menuOpenObserver;

public:

	/*
	*	メニューを使用できるか判断するオブザーバー
	* 
	*	@return インスタンスのポインタ
	*/
	MenuUsedObserver* GetMenuUsedObserver() { return m_menuUsedObserver.get(); }

	/*
	*	メニューを開くオブザーバーを受け取る
	* 
	*	@param	(observer)	インスタンスのポインタ
	*/
	void AddMenuOpenObserver(IMenuOpenObserver* observer) { m_menuOpenObserver->AddObserver(observer); }
};
 