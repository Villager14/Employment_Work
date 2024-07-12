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
	//		タイトル選択マネージャーの生成
	m_titleSelectManager = std::make_unique<TitleSelectManager>();

	//		タイトル選択マネージャーの初期化
	m_titleSelectManager->Initialize();

	//		タイトルのBGMの再生
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		メニューを設定
	m_titleSelectManager->SetMenuJudgement(m_sceneManager->GetMenuJudgement());
}

void TitleScene::Update()
{
	//		メニューを使える状態にするかどうか？
	m_sceneManager->SetMenuUseJudgement(m_titleSelectManager->GetMenuUseJudgement());

	//		タイトル選択マネージャーの更新処理
	m_titleSelectManager->Update();

	//		シーンを終了するかどうか
	if (m_titleSelectManager->GetChangeScnenJudgemnet())
	{
		//		プレイシーンに切り替える
		m_sceneManager->ChangeScene(SceneManager::SceneType::Play);
	}
}

void TitleScene::Render()
{
	//		タイトル選択マネージャーの描画処理
	m_titleSelectManager->Render();
}

void TitleScene::Finalize()
{
	m_titleSelectManager.reset();
}
