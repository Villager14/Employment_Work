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
	m_sceneManager{sceneManager}
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	CreateProjaction();

	//		ゲームマネージャーを生成する
	m_gameManager = std::make_unique<GameManager>();

	//		プレイヤーカメラマネージャーの生成
	m_playerCameraManager = std::make_unique<PlayerCameraManager>(m_gameManager.get());

	//		プレイヤーカメラマネージャーの初期化処理
	m_playerCameraManager->Initialize();

	//		プレイヤーの生成
	m_player = std::make_unique<Player>(m_gameManager.get());

	//		プレイヤーの初期化処理
	m_player->Initialize();

	//		オブジェクトマネージャーの生成
	m_objectManager = std::make_unique<ObjectManager>();

	//		オブジェクトマネージャーの初期化処理
	m_objectManager->Initialize();

	//		当たり判定マネージャーの生成
	m_collitionManager = std::make_unique<CollitionManager>();

	//		当たり判定マネージャーの初期化
	m_collitionManager->Initialize();

	//		エネミーマネージャーの生成
	m_enemyManager = std::make_unique<EnemyManager>();

	//		エネミーマネージャーの初期化
	m_enemyManager->Initialize();

	//		UIマネージャーの生成
	m_uiManager = std::make_unique<UIManager>(m_player->GetInformation(), m_gameManager.get());

	//		UIマネージャーの初期化
	m_uiManager->Initialize();

	//		スクリーンエフェクトマネージャーの生成
	m_screenEffectManager = std::make_unique<ScreenEffectManager>(m_gameManager.get());

	//		スクリーンエフェクトマネージャーの初期化
	m_screenEffectManager->Initialize();
}

void PlayScene::Update()
{
	//		プレイヤーのワールド座標を受け取る
	m_objectManager->SetPlayerWorld(m_player->GetInformation()->GetWorld());

	//		オブジェクトマネージャーの更新処理
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		範囲内にあるワイヤーの座標を受け取る
	m_player->GetInformation()->SetWirePosition(m_objectManager->GetWirePosition());

	//		視線ベクトルを設定する
	m_player->GetInformation()->SetViewVelocity(m_playerCameraManager->GetInformation()->GetViewVelocity());

	//		プレイヤーの更新処理
	m_player->Update(m_playerCameraManager->GetInformation());

	//		エネミーの更新処理
	m_enemyManager->Update(m_player->GetInformation()->GetTimeSpeed(), m_player->GetInformation()->GetPosition());

	//		メッシュを受け取る
	m_collitionManager->SetObjectMesh(m_objectManager->GetMesh());

	//		弾の座標を設定する
	m_collitionManager->SetBulletPoistion(m_enemyManager->GetBulletPosition());

	//		当たり判定の更新処理
	m_collitionManager->Update(m_player->GetPlayerInformationCollition());

	//		当たり判定の情報
	m_player->SetCollitionInformation(m_collitionManager->GetCollitionInformation());

	//		メッシュアップデート(仮)
	m_player->MeshUpdate();

	//		カメラマネージャーの更新処理
	m_playerCameraManager->Update(m_player->GetInformation());


	//		プレイヤーにカメラの角度を送る
	m_player->GetInformation()->SetCameraAngle(m_playerCameraManager->GetInformation()->GetAngle());

	//		UIマネージャーの更新
	m_uiManager->Update();

	//		スクリーンエフェクトの更新処理
	m_screenEffectManager->Update();

	//		ゲームマネージャーの更新処理
	m_gameManager->Update();
}

void PlayScene::Render()
{
	//		レンダーターゲットの変更
	m_screenEffectManager->ChangeRenderTarget();

	//		オブジェクトマネージャーの描画処理
	m_objectManager->Render();

	//		エネミーの描画
	m_enemyManager->Render();

	//		プレイヤーの描画処理
	m_player->Render();

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
	m_player.reset();
	m_objectManager.reset();
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
