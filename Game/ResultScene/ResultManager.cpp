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
	m_deathCount(0)
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

	//		状態を作成する
	CreateState();
}

void ResultManager::Update()
{
	//		状態の更新
	m_state->Update();

	//		背景の更新
	m_backGroundMove->Update();
}

void ResultManager::Render()
{
	//		背景の描画
	m_backGroundMove->Render();

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
	//		リザルトスタートを生成する
	m_resultStart = std::make_unique<ResultStart>(this);
	//		番号移動を生成する
	m_resultNumberMove = std::make_unique<ResultNumberMove>(this);

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
	AboveNumberView(3, m_time / 60 / 10, Library::Clamp(time, 0.9f, 1.9f) - 0.9);
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
