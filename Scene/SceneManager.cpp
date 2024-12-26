/*
* @file		SceneManager.cpp
* @brief	シーンマネージャー
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "SceneManager.h"

#include "SceneState/TutorialScene.h"

#include "SceneState/PlayScene.h"
#include "SceneState/TitleScene.h"
#include "SceneState/ResultScene.h"

SceneManager::SceneManager()
	:
	m_scene{},
	m_sceneType{}
{
	//		シーンマネージャーの情報
	m_information = std::make_unique<SceneManagerInformation>();

	//		マウスのキー入力の生成
	m_mouseKeyInput = std::make_unique<MouseKeyInput>();

	//		キーボードのキー入力の生成
	m_keyboardInput = std::make_unique<KeyboardManager>();

	//		メニューマネージャーの生成
	m_menuManager = std::make_unique<MenuManager>(this);

	//		ポストエフェクトマネージャーを受け取る
	m_postEffectManager = std::make_unique<PostEffectManager>();

	//		情報を処理
	m_information->Initialize(m_postEffectManager.get(),
		m_menuManager.get(),
		m_mouseKeyInput.get(),
		m_keyboardInput.get());

	//		キーボードオブザーバーに登録する
	m_menuManager->KeyboardAddObserver();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	//		メニューマネージャーの初期化
	m_menuManager->Initialize();

	m_titleScene = std::make_unique<TitleScene>(this);
	m_playScene = std::make_unique<PlayScene>(this);
	m_resultScene = std::make_unique<ResultScene>(this);

	//		シーンを作成する
	m_sceneInformation.insert({ SceneType::Title, m_titleScene.get() });
	m_sceneInformation.insert({ SceneType::Play, m_playScene.get() });
	m_sceneInformation.insert({ SceneType::Result, m_resultScene.get() });

	AddObserver();

	//		初期のシーンタイプを設定する
	m_sceneType = SceneType::Play;

	//		シーンを設定する
	m_scene = m_sceneInformation[m_sceneType];

	//		シーンを初期化する
	m_scene->Initialize();
}

void SceneManager::Update()
{
	//		マウスのキー入力の更新
	m_mouseKeyInput->Update();

	//		キーボードの入力の更新
	m_keyboardInput->Update();

	//		シーンの更新処理
	m_scene->Update();

	//		メニューマネージャーの更新
	m_menuManager->Update();

	//		ゲームを終了するか？
	if (m_information->GetEndJudgement())
	{
		Finalize();

		//		マウスのキー入力終了処理
		m_mouseKeyInput->Finalize();
	}
}

void SceneManager::Render()
{
	//		ゲーム終了時には描画しない
	if (m_information->GetEndJudgement()) return;

	//		シーンの描画処理
	m_scene->Render();

	//		メニューマネージャーの描画
	m_menuManager->Render();
}

void SceneManager::Finalize()
{
	//		現在の状態の終了処理をする
	m_scene->Finalize();

	//		シーンの情報を削除する
	m_sceneInformation.clear();
}

void SceneManager::AddObserver()
{
	//		メニューが開いているか判断するオブザーバーに登録する（ポストエフェクト）
	m_menuManager->AddMenuOpenObserver(m_postEffectManager.get());
	//		メニューが開いているか判断するオブザーバーに登録する (タイトルシーン)
	m_menuManager->AddMenuOpenObserver(m_titleScene.get());
	//		メニューが開いているか判断するオブザーバーに登録する (プレイシーン)
	m_menuManager->AddMenuOpenObserver(m_playScene.get());
	//		メニューが開いているか判断するオブザーバーに登録する (リザルトシーン)
	m_menuManager->AddMenuOpenObserver(m_resultScene.get());

	//		メニューを使用するか判断するオブザーバーに登録する（メニュー）
	m_titleScene->GetMenuUsedObserver()->AddObserver(m_menuManager.get());
	//		メニューを使用するか判断するオブザーバーに登録する（メニュー）
	m_playScene->GetMenuUsedObserver()->AddObserver(m_menuManager.get());
	//		メニューを使用するか判断するオブザーバーに登録する（メニュー）
	m_resultScene->GetMenuUsedObserver()->AddObserver(m_menuManager.get());

	//		メニューを開くか判断するオブザーバーに登録する(メニュー)
	m_titleScene->AddMenuOpenObserver(m_menuManager.get());

	//		カメラの速度オブザーバーに登録する（プレイヤ）
	m_menuManager->AddCameraSpeed(m_playScene.get());
	//		カメラの視野角オブザーバーに登録する（プレイヤ）
	m_menuManager->AddCameraViewAngle(m_playScene.get());
}

void SceneManager::ChangeScene(SceneType type)
{
	//		同じシーンの場合処理をしない
	if (m_sceneType == type) return;

	//		現在の状態の終了処理をする
	m_scene->Finalize();

	//		状態を切り替える
	m_sceneType = type;

	m_scene = m_sceneInformation[m_sceneType];

	//		新しい状態の初期化処理をする
	m_scene->Initialize();
}