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

	//		UIシェーダーマネージャーの生成
	m_uiShaderManager = std::make_unique<UIRenderManager>();

	ConstBuffer buffer;

	//		シェーダーの作製
	m_uiShaderManager->Create(L"Resources/Texture/UI/GameOver/GameOver.png",
								L"Resources/Shader/UI/UIShaderVS.cso",
								L"Resources/Shader/UI/UIShaderGS.cso",
								L"Resources/Shader/UI/UIShaderPS.cso",
								buffer,
								{ 0.0f, 0.0f, }, { 1.0f, 1.0f },
								CENTER_POINT::MIDDLE_CENTER);

	//ConstBufferManager::ConstBuffer buffer;

	//m_uiShaderManager->GetConstBufferManager()->CreateConstBuffer(
	//LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(), buffer);
}

void TitleScene::Update()
{
	//		メニュー状態かどうか受け取る
	m_titleSelectManager->SetMenuJudgement(m_sceneManager->GetMenuJudgement());

	//		タイトル選択マネージャーの更新処理
	m_titleSelectManager->Update();

	//		シーンを終了するかどうか
	if (m_titleSelectManager->GetChangeScnenJudgemnet())
	{
		//		プレイシーンに切り替える
		m_sceneManager->ChangeState(m_sceneManager->GetPlayScene());
	}
}

void TitleScene::Render()
{
	//		タイトル選択マネージャーの描画処理
	m_titleSelectManager->Render();

	ConstBuffer buffer;

	//		回転行列を送る
	buffer.rotationMatrix = m_uiShaderManager->GetRotationMatrix();

	//		ウィンドウサイズを送る
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	m_uiShaderManager->Render(buffer);
}

void TitleScene::Finalize()
{
	m_titleSelectManager.reset();
}
