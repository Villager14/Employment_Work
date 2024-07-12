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
	m_deathCount(0),
	m_clearTime(0),
	m_menuUseJudgement(false),
	m_sceneType{}
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	m_menuJudgement = std::make_unique<bool>(false);

	//		シーンを作成する
	m_sceneInformation.insert({ SceneType::Title, std::make_unique<TitleScene>(this) });
	m_sceneInformation.insert({ SceneType::Play, std::make_unique<PlayScene>(this) });
	m_sceneInformation.insert({ SceneType::Result, std::make_unique<ResultScene>(this) });

	//		初期のシーンタイプを設定する
	m_sceneType = SceneType::Title;

	//		シーンを設定する
	m_scene = m_sceneInformation[m_sceneType].get();

	//		シーンを初期化する
	m_scene->Initialize();


	//		メニューマネージャーの生成
	m_menuManager = std::make_unique<MenuManager>();

	//		メニューマネージャーの初期化
	m_menuManager->Initialize();

	m_menuManager->SetMenuJudgement(m_menuJudgement.get());
}

void SceneManager::Update()
{
	//		シーンの更新処理
	m_scene->Update();

	if (!m_menuUseJudgement) return;

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	if (keyboard.IsKeyPressed(DirectX::Keyboard::Escape))
	{
		*m_menuJudgement = true;
	}

	if (!*m_menuJudgement) return;

	//		メニューマネージャーの更新
	m_menuManager->Update();

	//		プレイシーンの場合マウスを元に戻す
	if (!*m_menuJudgement && m_sceneType == SceneType::Play)
	{
		//		マウス相対モード
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
	}
}

void SceneManager::Render()
{
	//		シーンの描画処理
	m_scene->Render();

	if (!*m_menuJudgement)return;

	//		メニューマネージャーの描画
	m_menuManager->Render();
}

void SceneManager::Finalize()
{
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
