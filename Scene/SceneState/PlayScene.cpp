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
	m_menuCloseJugement(false)
{
	Generation();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	CreateProjaction();

	//		ゲームマネージャーの初期化処理
	m_gameManager->Initialize();

	//		プレイヤーカメラマネージャーの初期化処理
	m_playerCameraManager->Initialize();

	//		カメラの情報を受け取る
	m_player->SetCameraInformation(m_playerCameraManager->GetInformation());

	//		プレイヤーの初期化処理
	m_player->Initialize();

	//		影の初期化
	//m_shadow->Initialize();

	//		オブジェクトマネージャーの初期化処理
	m_objectManager->Initialize();

	//		UIマネージャーの初期化
	m_uiManager->Initialize();

	//		スクリーンエフェクトマネージャーの初期化
	m_screenEffectManager->Initialize();

	//		ワイヤーの情報を受け取る
	m_effectManager->SetWireInformation(m_objectManager->GetUseWireInformation());

	//		エフェクトマネージャーの初期化
	m_effectManager->Initialize();

	//		エネミーマネージャーの初期化
	//m_enemyManager->Initialize();

	//		プレイシーン時のBGMを再生
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::PlayScene);

	//		視野角の情報を受け取る
	m_playerCameraManager->GetInformation()->SetViewAngle(m_sceneManager->GetMenuManager()->GetInformation()->GetViewAngle());

	//		視野角の更新
	m_playerCameraManager->ViewAngleUpdate(m_player->GetInformation());

	//		カメラの速度の更新
	m_playerCameraManager->GetInformation()->SetCameraSpeed(m_sceneManager->GetMenuManager()->GetInformation()->GetCameraSpeed());
}

void PlayScene::Generation()
{
	//		ゲームマネージャーを生成する
	m_gameManager = std::make_unique<GameManager>();

	//		プレイヤーカメラマネージャーの生成
	m_playerCameraManager = std::make_unique<PlayerCameraManager>(m_gameManager.get());

	//		プレイヤーの生成
	m_player = std::make_unique<Player>(m_gameManager.get());

	//		スクリーンエフェクトマネージャーの生成
	m_screenEffectManager = std::make_unique<ScreenEffectManager>
		(ScreenEffectManager::Scene::PlayScene, m_gameManager.get());

	//		エフェクトマネージャーの作製
	m_effectManager = std::make_unique<EffectManager>(m_player->GetInformation());

	//		UIマネージャーの生成
	m_uiManager = std::make_unique<UIManager>(m_player->GetInformation(), m_gameManager.get());

	//		当たり判定マネージャーの生成
	m_collitionManager = std::make_unique<CollitionManager>(m_gameManager.get());

	//		影の生成
	m_shadow = std::make_unique<Shadow>();

	//		オブジェクトマネージャーの生成
	m_objectManager = std::make_unique<ObjectManager>(m_shadow->GetInformation(), m_gameManager.get());

	//		エネミーマネージャーの生成
	//m_enemyManager = std::make_unique<EnemyManager>();
}

bool PlayScene::MenuInformation()
{
	//		メニューを開いている場合の処理
	if (m_sceneManager->GetMenuManager()->GetInformation()->GetMenuJudgement())
	{
		//		メニューを開いている
		m_menuCloseJugement = true;

		//		視野角の情報を受け取る
		m_playerCameraManager->GetInformation()->SetViewAngle(m_sceneManager->GetMenuManager()->GetInformation()->GetViewAngle());

		//		視野角の更新
		m_playerCameraManager->ViewAngleUpdate(m_player->GetInformation());

		//		カメラの速度の更新
		m_playerCameraManager->GetInformation()->SetCameraSpeed(m_sceneManager->GetMenuManager()->GetInformation()->GetCameraSpeed());

		//		グレイ
		m_screenEffectManager->GrayScare(m_sceneManager->GetMenuManager()->GetInformation());

		return true;
	}

	return false;
}

void PlayScene::Update()
{
	//		メニューを開いているかどうか
	if (MenuInformation()) return;

	//		メニューが使えるかどうか？
	m_sceneManager->GetMenuManager()->GetInformation()->SetMenuUseJudgement(m_player->GetMenuUseJugement());

	//		プレイヤーのワールド座標を受け取る
	m_objectManager->SetPlayerWorld(m_player->GetInformation()->GetWorld());

	//		オブジェクトマネージャーの更新処理
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		範囲内にあるワイヤーの座標を受け取る
	m_player->GetInformation()->SetWirePosition(m_objectManager->GetWirePosition());

	//		ワイヤーの情報を受け取る
	m_player->SetWireInformation(m_objectManager->GetUseWireInformation());


	//		視線ベクトルを設定する
	m_player->GetInformation()->SetViewVelocity(m_playerCameraManager->GetInformation()->GetViewVelocity());

	//		プレイヤーの更新処理
	m_player->Update(m_playerCameraManager->GetInformation());

	//		メッシュを受け取る
	m_collitionManager->SetObjectMesh(m_objectManager->GetMesh());

	//		当たり判定の更新処理
	m_collitionManager->Update(m_player->GetPlayerInformationCollition(), m_gameManager.get());

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
		m_playerCameraManager->Update(m_player->GetInformation());
	}

	//		プレイヤーにカメラの角度を送る
	m_player->GetInformation()->SetCameraAngle(m_playerCameraManager->GetInformation()->GetAngle());

	//		アニメーションのアップデート
	m_player->AnimationUpdate();

	//		UIマネージャーの更新
	m_uiManager->Update();

	//		スクリーンエフェクトの更新処理
	m_screenEffectManager->Update(m_playerCameraManager->GetInformation());

	//		ゲームマネージャーの更新処理
	m_gameManager->Update();

	//		エフェクトマネージャーの描画
	m_effectManager->Update(m_playerCameraManager->GetInformation());

	//		次のシーンに切り替えるかどうか
	if (m_gameManager->FlagJudgement(GameManager::NextScene))
	{
		//		クリアタイムを受け取る
		m_sceneManager->SetClearTime(static_cast<int>(m_gameManager->GetTime()));

		//		死亡回数を受け取る
		m_sceneManager->SetDeathCount(static_cast<int>(m_gameManager->GetDeathCount()));

		//		次のシーンに切り替える（リザルトシーン）
		m_sceneManager->ChangeScene(SceneManager::SceneType::Result);
	}

	//m_enemyManager->Update(m_gameManager->GetTime(),
	//	m_player->GetInformation()->GetPosition());
}

void PlayScene::Render()
{
	//		レンダーターゲットの変更
	//m_shadow->ChangeRenderTarget(m_player->GetInformation()->GetPosition());

	//		プレイヤーの描画処理
	//m_player->Render(m_shadow.get());

	//		レンダーターゲットの変更
	m_screenEffectManager->ChangeRenderTarget();

	//		オブジェクトマネージャーの描画処理
	m_objectManager->Render(m_player->GetCameraInformation()->GetViewVelocity(),
							m_player->GetInformation()->GetPlayerHeight());

	//		プレイヤーのモデル描画
	m_player->ModelRender();

	//		エネミーマネージャーの描画
	//m_enemyManager->Render();

	//		デバック描画
	m_player->DebugRender();

	//		エフェクトマネージャーの描画
	m_effectManager->Render();

	//		UIマネージャーの描画
	m_uiManager->FrontRender();

	//		レンダーターゲットを基に戻す
	m_screenEffectManager->FirstRenderTarget();

	//		画面エフェクトの描画
	m_screenEffectManager->Render();

	//		UIマネージャーの描画
	m_uiManager->BackRender();
}

void PlayScene::Finalize()
{
	m_objectManager->Finalize();

	m_effectManager->Finalize();

	m_gameManager->Finalize();

	m_uiManager->Finalize();

	m_player->Finalize();
}

void PlayScene::CreateProjaction()
{
	/*
	*	視野角90度
	*		
	*	近い距離0.1f
	* 　遠い距離500.0f
	*/
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(70.0f), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			0.1f, 500.0f);

	//		プロジェクション行列を設定する
	LibrarySingleton::GetInstance()->SetProj(proj);
}
