/*
* @file		SceneManager.h
* @brief	シーンマネージャー
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "IScene.h"

#include "SceneState/PlayScene.h"

#include "SceneState/TitleScene.h"

class PlayScene;

class TitleScene;

class SceneManager
{
public:
	//		コンストラクタ
	SceneManager();
	//		デストラクタ
	~SceneManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:
	//		シーン
	IScene* m_scene;

	//		プレイシーン
	std::unique_ptr<PlayScene> m_playScene;

	//		タイトルシーン
	std::unique_ptr<TitleScene> m_titleScene;
};
