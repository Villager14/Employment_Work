/*
* @file		PlayScene.h
* @brief	プレイシーン
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "../SceneManager.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraManager.h"

#include "Game/PlayScene/Player/Player.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Game/PlayScene/CollitionManager/CollitionManager.h"

#include "Game/PlayScene/Enemy/EnemyManager.h"

#include "Game/PlayScene/UIManager/UIManager.h"

#include "Game/PlayScene/ScreenEffect/ScreenEffectManager.h"

#include "Game/PlayScene/GameManager/GameManager.h"

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

	//		プロジェクション行列の作製
	void CreateProjaction();

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
	std::unique_ptr<ScreenEffectManager> m_screenEffectManager;

	//		ゲームマネージャー
	std::unique_ptr<GameManager> m_gameManager;
};