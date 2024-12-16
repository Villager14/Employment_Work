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

	//		メニューマネージャーの生成
	m_menuManager = std::make_unique<MenuManager>(this);

	//		ポストエフェクトマネージャーを受け取る
	m_postEffectManager = std::make_unique<PostEffectManager>(m_menuManager->GetInformation());
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	m_information->Initialize(m_postEffectManager.get(), m_menuManager.get());

	//		メニューマネージャーの初期化
	m_menuManager->Initialize();

	//		シーンを作成する
	m_sceneInformation.insert({ SceneType::Title, std::make_unique<TitleScene>(this) });
	m_sceneInformation.insert({ SceneType::Play, std::make_unique<PlayScene>(this) });
	m_sceneInformation.insert({ SceneType::Result, std::make_unique<ResultScene>(this) });
	m_sceneInformation.insert({ SceneType::Tutorial, std::make_unique<TutorialScene>(this) });

	//		初期のシーンタイプを設定する
	m_sceneType = SceneType::Title;

	//		シーンを設定する
	m_scene = m_sceneInformation[m_sceneType].get();

	//		シーンを初期化する
	m_scene->Initialize();
}

void SceneManager::Update()
{
	//		シーンの更新処理
	m_scene->Update();

	//		メニューマネージャーの更新
	m_menuManager->Update();

	//		ゲームを終了するか？
	if (m_information->GetEndJudgement())
	{
		Finalize();
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

void SceneManager::ChangeScene(SceneType type)
{
	//		同じシーンの場合処理をしない
	if (m_sceneType == type) return;

	//		現在の状態の終了処理をする
	m_scene->Finalize();

	//		状態を切り替える
	m_sceneType = type;

	m_scene = m_sceneInformation[m_sceneType].get();

	//		新しい状態の初期化処理をする
	m_scene->Initialize();
}