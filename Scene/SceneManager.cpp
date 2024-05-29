/*
* @file		SceneManager.cpp
* @brief	シーンマネージャー
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "SceneManager.h"

SceneManager::SceneManager()
	:
	m_scene{},
	m_clearTime(0),
	m_deathCount(0)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	//		プレイシーンを生成する
	m_playScene = std::make_unique<PlayScene>(this);
	//		タイトルシーンを生成する
	m_titleScene = std::make_unique<TitleScene>(this);
	//		リザルトシーンを生成する
	m_resultScene = std::make_unique<ResultScene>(this);
	//		初期シーンを設定する
	m_scene = m_titleScene.get();
	//		シーンを初期化する
	m_scene->Initialize();
}

void SceneManager::Update()
{
	//		シーンの更新処理
	m_scene->Update();
}

void SceneManager::Render()
{
	//		シーンの描画処理
	m_scene->Render();
}

void SceneManager::Finalize()
{
}

void SceneManager::ChangeState(IScene* state)
{
	//		同じ状態なら処理をしない
	if (m_scene == state) return;

	//		現在の状態の終了処理をする
	m_scene->Finalize();

	//		状態を切り替える
	m_scene = state;

	//		新しい状態の初期化処理をする
	m_scene->Initialize();
}
