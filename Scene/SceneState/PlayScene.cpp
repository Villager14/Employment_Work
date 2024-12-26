/*
* @file		PlayScene.cpp
* @brief	プレイシーン
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "PlayScene.h"

#include "Common/DebugDraw.h"

PlayScene::PlayScene(SceneManager* sceneManager)
	:
	m_sceneManager{sceneManager},
	m_menuCloseJugement(false),
	m_menuOpenJudgement(false)
{
	Generation();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//		カメラオブザーバーの追加（エフェクト）
	m_playerCameraManager->AddCameraObserver(m_effectManager.get());

	//		ゲームマネージャーの初期化処理
	m_gameManager->Initialize();

	//		リミットタイムを設定する
	m_gameManager->SetLimitTime(90.0f);

	//		プレイヤーカメラマネージャーの初期化処理
	m_playerCameraManager->Initialize();

	//		カメラの情報を受け取る
	m_player->SetCameraInformation(m_playerCameraManager->GetInformation());

	//		プレイヤーの初期化処理
	m_player->Initialize();

	//		オブジェクトマネージャーの初期化処理
	m_objectManager->Initialize(ObjectManager::Play);

	//		UIマネージャーの初期化
	m_uiManager->Initialize();

	//		ストエフェクトマネージャーの初期化
	m_sceneManager->GetInformation()->GetPostEffectManager()->Initialize(m_gameManager->BACK_GROUND_COLOR, m_postEffectFlag.get());

	//		ワイヤーの情報を受け取る
	m_effectManager->SetWireInformation(m_objectManager->GetUseWireInformation());

	//		エフェクトマネージャーの初期化
	m_effectManager->Initialize();

	//		リスポーンマネージャーの初期化
	m_respawnManager->Initialize();

	//		プレイシーン時のBGMを再生
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::PlayScene);

	//		視野角の更新
	m_playerCameraManager->ViewingAngleUpdate();

	//		サブジェクト
	m_player->GetSubject()->AddObserver(m_uiManager.get());
	m_player->GetSubjectSpeed()->AddObserver(m_uiManager.get());
	m_player->GetSubjectHeight()->AddObserver(m_playerCameraManager.get());
	m_player->GetSubjectSpeed()->AddObserver(m_playerCameraManager.get());
	m_player->GetSubjectCamera()->AddObserver(m_playerCameraManager.get());

	m_menuUsedObserver->MenuUseJudgement(true);
}

void PlayScene::Generation()
{
	//		ゲームマネージャーを生成する
	m_gameManager = std::make_unique<GameManager>();

	//		プレイヤーカメラマネージャーの生成
	m_playerCameraManager = std::make_unique<PlayerCameraManager>(m_gameManager.get());

	//		プレイヤーの生成
	m_player = std::make_unique<Player>(m_gameManager.get());

	//		エフェクトマネージャーの作製
	m_effectManager = std::make_unique<EffectManager>(m_player->GetInformation(), m_playerCameraManager->GetInformation());

	//		UIマネージャーの生成
	m_uiManager = std::make_unique<UIManager>(m_gameManager.get());

	//		当たり判定マネージャーの生成
	m_collitionManager = std::make_unique<CollitionManager>(m_gameManager.get());

	//		オブジェクトマネージャーの生成
	m_objectManager = std::make_unique<ObjectManager>();

	//		リスポーンマネージャー
	m_respawnManager = std::make_unique<RespawnManager>(m_gameManager.get());

	//		メニューを使用できるか判断するオブザーバーを生成する
	m_menuUsedObserver = std::make_unique<MenuUsedObserver>();

	//		ポストエフェクトフラグの生成
	m_postEffectFlag = std::make_unique<PostEffectFlag>(true);

	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::Glitch);
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::PlayerView);
}

bool PlayScene::MenuInformation()
{
	//		メニューを開いている場合の処理
	if (m_menuOpenJudgement)
	{
		//		メニューを開いている
		m_menuCloseJugement = true;

		//		視野角の更新
		m_playerCameraManager->ViewingAngleUpdate();

		//		グレイ
		m_sceneManager->GetInformation()->GetPostEffectManager()->Update(PostEffectFlag::Flag::Color);

		return true;
	}

	return false;
}

void PlayScene::MenuOpen()
{
	m_menuOpenJudgement = true;
}

void PlayScene::MenuClose()
{
	m_menuOpenJudgement = false;
}

void PlayScene::GetMenuCameraSpeed(float speed)
{
	m_playerCameraManager->GetInformation()->SetCameraSpeed(speed);
}

void PlayScene::GetMenuCameraViewAngle(float angle)
{
	m_playerCameraManager->GetInformation()->SetViewAngle(angle);
}

void PlayScene::Update()
{
	//		Pを押すとリザルトになる
	if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState().IsKeyDown(DirectX::Keyboard::P))
	{
		m_sceneManager->ChangeScene(SceneManager::Result);

		return;
	}

	//		メニューを開いているかどうか
	if (MenuInformation()) return;

	//		メニューが使えるかどうか？
	//m_sceneManager->GetInformation()->GetMenuManager()->GetInformation()->SetMenuUseJudgement(m_player->GetMenuUseJugement());

	//		オブジェクトマネージャーの更新処理
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		ワイヤーの情報を受け取る
	m_player->SetWireInformation(m_objectManager->GetUseWireInformation());

	//		視線ベクトルを設定する
	m_player->GetInformation()->SetViewVelocity(m_playerCameraManager->GetInformation()->GetViewVelocity());

	//		プレイヤーの更新処理
	m_player->Update(m_playerCameraManager->GetInformation());

	//		メッシュを受け取る
	m_collitionManager->SetObjectMesh(m_objectManager->GetMesh());

	//		当たり判定の更新処理
	m_collitionManager->Update(m_player->GetPlayerInformationCollition());

	//		当たり判定の情報
	m_player->SetCollitionInformation(m_collitionManager->GetCollitionInformation());

	//		メッシュアップデート
	m_player->MeshUpdate();

	//		マウス絶対モードから相対モードに切り替わる時一フレーム必要なので
	if (m_menuCloseJugement)
	{
		m_menuCloseJugement = false;
	}
	else
	{
		//		カメラマネージャーの更新処理
		m_playerCameraManager->Update();
	}

	//		プレイヤーにカメラの角度を送る
	m_player->GetInformation()->SetCameraAngle(m_playerCameraManager->GetInformation()->GetAngle());

	//		アニメーションのアップデート
	m_player->AnimationUpdate();

	//		UIマネージャーの更新
	m_uiManager->Update();

	//		ポストエフェクトの更新処理
	for (int i = 1; i <= PostEffectFlag::Flag::Fade;)
	{
		//		フラグがfalseの場合処理をしない
		if (!m_postEffectFlag->FlagJudgement(PostEffectFlag::Flag(i)))
		{
			i = i + i;

			continue;
		}

		m_sceneManager->GetInformation()->GetPostEffectManager()
						->Update(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		ゲームマネージャーの更新処理
	m_gameManager->Update(m_sceneManager->GetInformation()
			->GetPostEffectManager()->GetInformation());

	//		エフェクトマネージャーの描画
	m_effectManager->Update();

	//		リスポーンポイントの更新処理
	m_respawnManager->Update(m_player->GetInformation()->GetPosition());

	//		リスポーン座標を設定する
	m_player->GetInformation()->SetRespawnPosition(m_respawnManager->GetRespownPosition());

	//		リスポーン時の回転量を受け取る
	m_playerCameraManager->GetInformation()->SetStartDirection(m_respawnManager->GetRespownDirection());

	//		次のシーンに切り替えるかどうか
	if (m_sceneManager->GetInformation()->GetPostEffectManager()->
		GetInformation()->FlagJudgement(PostEffectInformation::Flag::SceneEnd))
	{
		//		次のシーンに切り替える（リザルトシーン）
		m_sceneManager->ChangeScene(SceneManager::SceneType::Result);
	}
}

void PlayScene::Render()
{
	for (int i = 1; i <= PostEffectFlag::Flag::Fade;)
	{
		//		フラグがfalseの場合処理をしない
		if (!m_postEffectFlag->FlagJudgement(PostEffectFlag::Flag(i)))
		{
			i = i + i;

			continue;
		}

		//		ポストエフェクトマネージャーの変更
		m_sceneManager->GetInformation()->
			GetPostEffectManager()->Render(PostEffectFlag::Flag(i));

		//オブジェクトマネージャーの描画処理
		m_objectManager->Render(m_player->GetCameraInformation()->GetViewVelocity(),
			m_player->GetInformation()->GetPlayerHeight(),
			PostEffectFlag::Flag(i), m_sceneManager->GetInformation()->
			GetPostEffectManager()->GetPostObjectShader());

		//		プレイヤーのモデル描画
		m_player->ModelRender(PostEffectFlag::Flag(i), 
			m_sceneManager->GetInformation()->
			GetPostEffectManager()->GetPostObjectShader());

		//		エフェクトマネージャーの描画
		m_effectManager->Render(PostEffectFlag::Flag(i));

		if (PostEffectFlag::Flag(i) == PostEffectFlag::Flag::UI)
		{
			//		UIマネージャーの描画
			m_uiManager->FrontRender();
		}

		if (PostEffectFlag::Flag(i) == PostEffectFlag::Flag::UIBack)
		{
			//		UIマネージャーの後描画
			m_uiManager->BackRender();
		}

		//		ポストエフェクトマネージャーのラスト描画
		m_sceneManager->GetInformation()->
			GetPostEffectManager()->RastRender(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		デバック描画
	m_player->DebugRender();

	//		レンダーテクスチャをリセットする
	m_sceneManager->GetInformation()->
		GetPostEffectManager()->ResetRenderTarget();

	//		レンダーテクスチャの描画
	m_sceneManager->GetInformation()->
		GetPostEffectManager()->RenderTextureView();
}

void PlayScene::Finalize()
{
	//		クリアタイムを設定する
	m_sceneManager->GetInformation()->SetClearTime(static_cast<int>(m_gameManager->GetTime()));

	//		死亡回数を設定する
	m_sceneManager->GetInformation()->SetDeathCount(static_cast<int>(m_gameManager->GetDeathCount()));

	//		最大リミットタイムを設定する
	m_sceneManager->GetInformation()->SetMaxTime(static_cast<int>(m_gameManager->GetLimitTime()));

	//		ゲームマネージャーの終了処理
	m_gameManager->Finalize();

	//		当たり判定マネージャーの終了処理
	m_collitionManager->Finalize();

	//		カメラの終了処理
	m_playerCameraManager->Finalize();

	//		プレイヤの終了処理
	m_player->Finalize();

	//		ポストエフェクトマネージャー
	m_sceneManager->GetInformation()->
		GetPostEffectManager()->Finalize();

	//		リスポーンポイントの終了処理
	m_respawnManager->Finalize();

	//		エフェクトマネージャー
	m_effectManager->Finalize();
	
	//		UIマネージャーの終了処理
	m_uiManager->Finalize();

	m_objectManager->Finalize();
}