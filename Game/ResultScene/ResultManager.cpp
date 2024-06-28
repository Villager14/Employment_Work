/*
* @file		ResultManager.cpp
* @brief	リザルトマネージャー
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultManager.h"

ResultManager::ResultManager()
	:
	m_score(0),
	m_time(0),
	m_deathCount(0),
	m_state(),
	m_rotation(0.0f),
	m_changeScene(false)
{
}

ResultManager::~ResultManager()
{
}

void ResultManager::Initialize(int score, int time, int deathCount)
{
	m_score = score;
	m_time = time;
	m_deathCount = deathCount;

	//		背景の生成
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		背景の初期化
	m_backGroundMove->Initialize();

	//		死亡回数
	for (int i = 0; i < 3; ++i)
	{
		//		上移動数字の生成
		m_aboveNumber.push_back(std::make_unique<AboveNumber>());

		//		上数字の作製
		m_aboveNumber[i]->Create(L"Resources/Texture/ResultScene/nomber.png", {970.0f + 60.0f * i, 140.0f}, {1.0f, 1.0f});
	}
	
	//		時間
	for (int i = 0; i < 4; ++i)
	{
		//		上移動数字の生成
		m_aboveNumber.push_back(std::make_unique<AboveNumber>());

		//		上数字の作製
		m_aboveNumber[i + 3]->Create(L"Resources/Texture/ResultScene/nomber.png", { 910.0f + 60.0f * i, 250.0f }, { 1.0f, 1.0f });
	}

	//		時間
	for (int i = 0; i < 4; ++i)
	{
		//		上移動数字の生成
		m_aboveNumber.push_back(std::make_unique<AboveNumber>());

		//		上数字の作製
		m_aboveNumber[i + 7]->Create(L"Resources/Texture/ResultScene/nomber.png", { 910.0f + 60.0f * i, 360.0f }, { 1.0f, 1.0f });
	}

	//		UI描画の生成
	m_fadeRender = std::make_unique<FadeRender>();

	//		UI描画の作製
	m_fadeRender->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });
	
	//		背景UIの作製
	AddRenderUI(L"Resources/Texture/ResultScene/ResultBack.png", { 0.0f, 0.0f }, { 1.0f, 1.0f });

	if (m_score >= 2000.0f)
	{
		//		背景UIの作製
		AddRenderUI(L"Resources/Texture/ResultScene/ScoreA.png", { 350.0f, 150.0f }, { 0.0f, 0.0f });
	}
	else if (m_score >= 1000.0f)
	{
		//		背景UIの作製
		AddRenderUI(L"Resources/Texture/ResultScene/ScoreB.png", { 350.0f, 150.0f }, { 0.0f, 0.0f });
	}
	else
	{
		//		背景UIの作製
		AddRenderUI(L"Resources/Texture/ResultScene/ScoreC.png", { 350.0f, 150.0f }, { 0.0f, 0.0f });
	}

	//		UI描画の作製(Continue)
	AddRenderUI(L"Resources/Texture/UI/GameOver/button.png",
		{ 0.0f, 280.0f }, { 1.0f, 1.0f });

	//		状態を作成する
	CreateState();

	//		スクリーンエフェクトマネージャーの作製
	m_screenEffectManager = std::make_unique<ScreenEffectManager>(nullptr);

	//		スクリーンエフェクトの初期化
	m_screenEffectManager->Initialize(ScreenEffectManager::ResultScene);

	//		プレイヤーのアニメーションの作製
	m_playerAnimation = std::make_unique<PlayerAnimation>();

	//		プレイヤーのアニメーション初期化
	m_playerAnimation->Initialize(true);

	//		直立状態
	m_playerAnimation->ChangeState(m_playerAnimation->Upright);
}

void ResultManager::Update()
{
	//		状態の更新
	m_state->Update();

	//		背景の更新
	m_backGroundMove->Update();

	m_rotation += LibrarySingleton::GetInstance()->GetElpsedTime() * 30.0f;

	m_playerAnimation->Execute(0.0f, { 0.0f, 0.0f, 8.0f }, { m_rotation, 0.0f }, 2.5f);
}

void ResultManager::Render()
{
	//		レンダーターゲットの変更
	m_screenEffectManager->ChangeRenderTarget();

	m_playerAnimation->Render(true);

	//		レンダーターゲットを戻す
	m_screenEffectManager->FirstRenderTarget();


	//		背景の描画
	m_backGroundMove->Render();

	//		UI背景の描画
	m_uiRender[0]->Render();

	//		レンダーターゲットの描画
	m_screenEffectManager->Render();

	//		状態の描画
	m_state->Render();
}

void ResultManager::Finalize()
{
}

void ResultManager::ChangeState(IResultManager* state)
{
	//		同じ状態なら処理をしない
	if (m_state == state) return;

	//		現在の状態の終了処理をする
	m_state->Finalize();

	//		状態を切り替える
	m_state = state;

	//		新しい状態の初期化処理をする
	m_state->Initialize();
}

void ResultManager::CreateState()
{
	//		スタート状態を生成する
	m_resultStart = std::make_unique<ResultStart>(this);
	//		番号移動状態を生成する
	m_resultNumberMove = std::make_unique<ResultNumberMove>(this);
	//		評価状態を生成する
	m_resultEvaluation = std::make_unique<ResultEvaluation>(this);
	//		待機状態を生成する
	m_resultStay = std::make_unique<ResultStay>(this);
	//		終了状態を生成する
	m_resultEnd = std::make_unique<ResultEnd>(this);
	//		初期状態を設定する
	m_state = m_resultStart.get();

	//		状態を初期化する
	m_state->Initialize();
}

void ResultManager::NumberRender(float time)
{
	//		死亡回数表示
	AboveNumberView(0, (m_deathCount / 100) % 10,	Library::Clamp(time, 0.0f, 1.0f));
	AboveNumberView(1, (m_deathCount / 10) % 10,	Library::Clamp(time, 0.3f, 1.3f) - 0.3f);
	AboveNumberView(2,  m_deathCount % 10,			Library::Clamp(time, 0.6f, 1.6f) - 0.6f);

	//		クリア時間
	AboveNumberView(3, m_time / 60 / 10, Library::Clamp(time, 0.9f, 1.9f) - 0.9f);
	AboveNumberView(4, m_time / 60 % 10, Library::Clamp(time, 1.2f, 2.2f) - 1.2f);
	AboveNumberView(5, m_time % 60 / 10, Library::Clamp(time, 1.5f, 2.5f) - 1.5f);
	AboveNumberView(6, m_time % 60 % 10, Library::Clamp(time, 1.8f, 2.8f) - 1.8f);

	//		スコア表示
	AboveNumberView(7,  m_score / 1000,			Library::Clamp(time, 2.1f, 3.1f) - 2.1f);
	AboveNumberView(8, (m_score / 100) % 10,	Library::Clamp(time, 2.4f, 3.4f) - 2.4f);
	AboveNumberView(9, (m_score / 10) % 10,		Library::Clamp(time, 2.7f, 3.7f) - 2.7f);
	AboveNumberView(10, m_score % 10,			Library::Clamp(time, 3.0f, 4.0f) - 3.0f);
}

void ResultManager::AddRenderUI(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 size)
{
	//		UIレンダーの生成
	std::unique_ptr<UIRender> uiRender = std::make_unique<UIRender>();

	//		UIの作製
	uiRender->Create(path, position, size);

	m_uiPosition.push_back(position);

	m_uiSize.push_back(size);

	//		UIの追加
	m_uiRender.push_back(std::move(uiRender));
}

void ResultManager::AnimationSkip()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		マウスの取得
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Spaceまたは左クリックを押した場合復活する
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		状態を切り替える(待機状態)
		m_state = m_resultStay.get();
	}
}
