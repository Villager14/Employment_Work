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
	//		タイトルのUIクラスの生成
	m_titleUI = std::make_unique<TitleUI>();

	//		タイトルの流れマネージャーの生成
	m_titleFlowManager = std::make_unique<TitleFlowManager>();

	//		タイトルポストエフェクトマネージャー
	m_titlePostEffectManager = std::make_unique<TitlePostEffectManager>
				(sceneManager->GetInformation()->GetPostEffectManager());

	//		タイトルシーン切り替えの処理
	m_titleSceneChange = std::make_unique<TitleSceneChange>(sceneManager);

	//		メニューマネジメントの生成
	m_menuManagement = std::make_unique<TitleMenuManagement>
		(m_sceneManager->GetInformation()->GetMenuManager()->GetInformation());

	//		オブジェクトマネージャーの生成
	m_objectManager = std::make_unique<ObjectManager>();

	//		タイトルのプレイヤーの生成
	m_player = std::make_unique<TitlePlayer>();

	//		タイトルエフェクトマネージャーの生成
	m_titleEffectManager = std::make_unique<TitleEffectManager>();

	//		タイトルカメラマネージャー
	m_cameraManager = std::make_unique<TitleCameraManager>();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{	
	//		タイトルのBGMの再生
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		タイトルのUIの初期化
	m_titleUI->Initalize();

	//		タイトルの流れマネージャーの初期化
	m_titleFlowManager->Initialize();

	//		タイトルポストエフェクトマネージャー
	m_titlePostEffectManager->Initialize();

	//		オブジェクトマネージャーの初期化
	m_objectManager->Initialize(ObjectManager::Title);

	//		プレイヤーの初期化処理
	m_player->Initialize();

	//		タイトルエフェクトマネージャーの初期化処理
	m_titleEffectManager->Initialize();

	//		カメラマネージャの初期化
	m_cameraManager->Initialize();

	//		オブザーバーの追加
	AddObserver();
}

void TitleScene::Update()
{
	//		メニューを使用している場合は処理をしない
	if (m_menuManagement->MenuUseJudgement()) return;

	//		タイトルシーンのUIの更新処理
	m_titleUI->Update();

	//		タイトルの流れマネージャーの更新
	m_titleFlowManager->Update();

	//		ポストエフェクトの更新
	m_titlePostEffectManager->Update();

	//		プレイヤーの更新
	m_player->Update();

	//		タイトルエフェクトマネージャの更新処理
	m_titleEffectManager->Update();

	//		カメラマネージャーの更新
	m_cameraManager->Update();
}

void TitleScene::Render()
{
	//		ポストエフェクトの更新
	for (int i = 1; i <= PostEffectFlag::Fade;)
	{
		//		ポストエフェクトを使用するか?
		if (!m_titlePostEffectManager->PostEffectUseJudgement(i))
		{
			i = i + i;

			continue;
		}

		//		ポストエフェクトの更新
		m_titlePostEffectManager->PostEffectUpdate(i);

		//		プレイヤーの描画
		m_player->Render(PostEffectFlag::Flag(i));

		//		オブジェクトの描画
		m_objectManager->Render({0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f},
			PostEffectFlag::Flag(i),
			m_sceneManager->GetInformation()->
			GetPostEffectManager()->GetPostObjectShader());

		//		タイトルエフェクトマネージャーの描画
		m_titleEffectManager->Render(PostEffectFlag::Flag(i));

		//		タイトルシーンのUIの描画処理
		m_titleUI->Render(i);

		//		ポストエフェクトの描画
		m_titlePostEffectManager->PostEffectRender(i);

		i = i + i;
	}

	//		ポストエフェクトのテクスチャ描画
	m_titlePostEffectManager->PostEffectTextureRender();
}

void TitleScene::Finalize()
{
	//		タイトルUIの終了処理
	m_titleUI->Finalize();

	//		タイトル流れマネージャの終了処理
	m_titleFlowManager->Finalize();

	//		タイトルポストエフェクトの終了処理
	m_titlePostEffectManager->Finalize();

	//		オブジェクトマネージャーの終了処理
	m_objectManager->Finalize();

	//		プレイヤーの終了処理
	m_player->Finalize();

	//		タイトルエフェクトマネージャーの終了処理
	m_titleEffectManager->Finalize();

	//		カメラマネージャーの終了処理
	m_cameraManager->Finalize();
}

void TitleScene::AddObserver()
{
	//		タイトルポストエフェクトオブザーバーに登録する（タイトルの流れ）
	m_titlePostEffectManager->AddTitlePostEffectObserver(m_titleFlowManager.get());

	//		タイトルポストエフェクトオブザーバーに登録する(シーン切り替え)
	m_titlePostEffectManager->AddTitlePostEffectObserver(m_titleSceneChange.get());

	//		タイトルUIオブザーバーに登録する（タイトルUI）
	m_titleFlowManager->AddITitleUIObserver(m_titleUI.get());

	//		タイトルフェードオブザーバーに登録する（ポストエフェクト）
	m_titleFlowManager->AddIFadeObserver(m_titlePostEffectManager.get());

	//		タイトルカメラのオブザーバーに登録する（ポストエフェクト）
	m_cameraManager->AddFadeObserver(m_titlePostEffectManager.get());

	//		タイトルカメラのオブザーバーに登録する(タイトルUI)
	m_cameraManager->AddFadeObserver(m_titleUI.get());

	//		タイトルゲーム終了オブザーバーに登録する（シーン切り替え）
	m_titleFlowManager->AddGameExitObserver(m_titleSceneChange.get());

	//		タイトルメニュー使用オブザーバーに登録する(メニューマネージャー)
	m_titleFlowManager->AddMenUseObserver(m_menuManagement.get());

	//		タイトルのアニメーションオブザーバーに登録する（プレイヤー）
	m_titleFlowManager->AddAnimationObserver(m_player.get());
}