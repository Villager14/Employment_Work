/*
* @file		TitleScene.h
* @brief	タイトルシーン
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Scene/IScene.h"

#include "../SceneManager.h"

#include "Game/PlayScene/UIManager/UIRender.h"

#include "Game/TitleScene/UI/BackGroundMove.h"

#include "Game/TitleScene/UI/Select/TitleSelectManager.h"

class SceneManager;

class TitleScene : public IScene
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

private:
	//		シーンマネージャーのインスタンスのポインタ
	SceneManager* m_sceneManager;

	//		UI描画
	std::unique_ptr<UIRender> m_uiRender;

	//		背景移動処理
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	//		タイトル選択状態
	std::unique_ptr<TitleSelectManager> m_titleSelectManager;
};
