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
	m_scene{}
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	//		プレイシーンを生成する
	m_playScene = std::make_unique<PlayScene>(this);

	//		初期シーンを設定する
	m_scene = m_playScene.get();
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
