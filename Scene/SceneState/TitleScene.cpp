/*
* @file		TitleScene.cpp
* @brief	タイトルシーン
* @author	Morita
* @date		2024/05/24
*/

#include "pch.h"

#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//		UIの描画の生成
	m_uiRender = std::make_unique<UIRender>();

	//		UIの作製
	m_uiRender->Create(L"Resources/Texture/TitleScene/TitleRogo.png",
		{ 0.0f,-170.0f }, { 1.0f, 1.0f });

	//		背景の生成
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		背景の初期化
	m_backGroundMove->Initialize();

	//		タイトル選択マネージャーの生成
	m_titleSelectManager = std::make_unique<TitleSelectManager>();

	//		タイトル選択マネージャーの初期化
	m_titleSelectManager->Initialize();
}

void TitleScene::Update()
{
	//		更新処理
	m_backGroundMove->Update();

	//		タイトル選択マネージャーの更新処理
	m_titleSelectManager->Update();
}

void TitleScene::Render()
{
	m_backGroundMove->Render();

	m_uiRender->Render();

	//		タイトル選択マネージャーの描画処理
	m_titleSelectManager->Render();
}

void TitleScene::Finalize()
{
}
