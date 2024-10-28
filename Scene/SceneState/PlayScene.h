/*
* @file		PlayScene.h
* @brief	プレイシーン
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"
#include "Game/PlayScene/UIManager/UIManager.h"
#include "Game/PlayScene/Enemy/EnemyManager.h"
#include "Game/Camera/PlaySceneCamera/PlayerCameraManager.h"
#include "Game/PlayScene/Player/Player.h"
#include "Game/PlayScene/ObjectManager/ObjectManager.h"
#include "Game/PlayScene/CollitionManager/CollitionManager.h"
//#include "Game/PlayScene/ScreenEffect/ScreenEffectManager.h"
#include "Library/Effect/PostEffect/PostEffectManager.h"
#include "Game/PlayScene/Effect/EffectManager.h"
#include "Game/PlayScene/Respawn/RespawnManager.h"

#include "Library/Effect/PostEffect/PostEffectFlag.h"

#include "../SceneManager.h"

#include "Scene/IScene.h"

class SceneManager;

class PlayScene : public IScene
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

	//		エネミーマネージャー
	std::unique_ptr<EnemyManager> m_enemyManager;

	//		UIマネージャー
	std::unique_ptr<UIManager> m_uiManager;

	//		スクリーンエフェクトマネージャー
	//std::unique_ptr<ScreenEffectManager> m_screenEffectManager;
	
	//		ポストエフェクトマネージャー
	std::unique_ptr<PostEffectManager> m_postEffectManager;
	//		ゲームマネージャー
	std::unique_ptr<GameManager> m_gameManager;

	//		エフェクトマネージャー
	std::unique_ptr<EffectManager> m_effectManager;

	//		リスポーンマネージャー
	std::unique_ptr<RespawnManager> m_respawnManager;

	bool m_menuCloseJugement;
};