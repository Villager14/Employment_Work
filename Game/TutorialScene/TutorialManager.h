/*
* @file		TutorialManager.h
* @brief	チュートリアルシーンを管理する
* @author	Morita
* @date		2024/09/17
*/

#pragma once

#include "ITutorialManager.h"

#include "State/TutorialWalkState.h"

#include "TutorialInformation.h"

#include "Test/Renderer.h"

#include "Test/RendererObject.h"

#include "Test/ModelMake.h"

#include "Test/IObjectMove.h"

class SceneManager;

class TutorialManager
{
public:

	//		コンストラクタ
	TutorialManager(SceneManager* sceneManager);

	//		デストラクタ
	~TutorialManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		生成
	void Generation();

public:

	enum TutorialState
	{
		Walk,	//		歩行状態
	};

private:

	//		各状態に応じたチュートリアル管理オブジェクトを保持
	std::unordered_map<TutorialState, std::unique_ptr<ITutorialManager>> m_tutorialInformation;

	//		現在のチュートリアルの状態
	ITutorialManager* m_state;

	//		現在のチュートリアルの進行状態
	TutorialState m_tutorialState;

	//		情報
	std::unique_ptr<TutorialInformation> m_information;

	//		描画
	std::unique_ptr<Renderer> m_renderer;

	//		オブジェクト
	std::unique_ptr<RendererObject> m_object;
	std::unique_ptr<RendererObject> m_object2;

	std::unique_ptr<ModelMake> m_modelMake;

	std::vector<std::unique_ptr<IObjectMove>> m_objectMove;

private:

	//		シーンマネージャー
	SceneManager* m_sceneManager;
};