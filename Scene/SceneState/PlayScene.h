/*
* @file		PlayScene.h
* @brief	プレイシーン
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"
#include "Effect/UI/PlayScene/UIManager.h"
#include "Game/Camera/PlaySceneCamera/PlayerCameraManager.h"
#include "Game/PlayScene/Player/Player.h"
#include "Game/PlayScene/ObjectManager/ObjectManager.h"
#include "Game/PlayScene/CollitionManager/CollitionManager.h"
#include "Effect/PostEffect/PostEffectManager.h"
#include "Game/PlayScene/Respawn/RespawnManager.h"
#include "Effect/PostEffect/PostEffectFlag.h"
#include "Effect/Effect/EffectManager.h"

#include "Game/Observer/Menu/MenuOpenJudgementObserver/IMenuOpenJudgementObserver.h"

#include "Game/Observer/Menu/MenuCameraSpeed/IMenuCameraSpeed.h"

#include "Game/Observer/Menu/MenuUsedObserver/MenuUsedObserver.h"
#include "Game/Observer/Menu/MenuCameraViewAngle/IMenuCameraViewAngle.h"

#include "../SceneManager.h"

#include "Scene/IScene.h"

class SceneManager;

class PlayScene : public IScene,
				  public IMenuOpenJudgementObserver,
				  public IMenuCameraSpeed,
				  public IMenuCameraViewAngle
{
public:
	/*
	*	コンストラクタ
	* 
	*	@param	(sceneManager) シーンマネージャーのインスタンスのポインタ
	*/
	PlayScene(SceneManager* sceneManager);

	//		デストラクタ
	~PlayScene();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	void Generation();

	//		メニューの情報
	bool MenuInformation();

	//		メニューを開いている
	void MenuOpen() override;

	//		メニューを閉じている
	void MenuClose() override;

	//		メニューのカメラの速度
	void GetMenuCameraSpeed(float speed) override;

	//		メニューのカメラの視野角
	void GetMenuCameraViewAngle(float angle) override;

private:
	//		シーンマネージャー
	SceneManager* m_sceneManager;

	//		プレイヤーのカメラマネージャー
	std::unique_ptr<PlayerCameraManager> m_playerCameraManager;

	//		プレイヤー
	std::unique_ptr<Player> m_player;

	//		オブジェクトマネージャー
	std::unique_ptr<ObjectManager> m_objectManager;

	//		当たり判定オブジェクト
	std::unique_ptr<CollitionManager> m_collitionManager;

	//		UIマネージャー
	std::unique_ptr<UIManager> m_uiManager;
	
	//		ゲームマネージャー
	std::unique_ptr<GameManager> m_gameManager;

	//		エフェクトマネージャー
	std::unique_ptr<EffectManager> m_effectManager;

	//		リスポーンマネージャー
	std::unique_ptr<RespawnManager> m_respawnManager;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	//		メニューを使うか判断するオブザーバー
	std::unique_ptr<MenuUsedObserver> m_menuUsedObserver;

	bool m_menuCloseJugement;

	//		メニューを開いているかどうか
	bool m_menuOpenJudgement;

public:

	/*
	*	メニューを使用できるか判断するオブザーバー
	*
	*	@return インスタンスのポインタ
	*/
	MenuUsedObserver* GetMenuUsedObserver() { return m_menuUsedObserver.get(); }

};