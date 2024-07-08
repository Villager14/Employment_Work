/*
* @file		ResultManager.cpp
* @brief	リザルトマネージャー
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultManager.h"

#include "State/ResultStart.h"
#include "State/ResultNumberMove.h"
#include "State/ResultEvaluation.h"
#include "State/ResultStay.h"
#include "State/ResultEnd.h"

ResultManager::ResultManager()
	:
	m_score(0),
	m_time(0),
	m_deathCount(0),
	m_iState(),
	m_rotation(0.0f),
	m_changeScene(false),
	m_state{}
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

	//		数字上昇シェーダーの生成
	m_riseNumber = std::make_unique<RiseNumberShader>();

	//		数字上昇シェーダーの初期化
	m_riseNumber->Initialize(m_deathCount, m_time, m_score);
	
	//		UI描画の生成
	m_fadeRender = std::make_unique<FadeRender>();

	//		UI描画の作製
	m_fadeRender->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		スタンダードシェーダーの作製
	CreateStandardShader();

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
	m_iState->Update();

	//		背景の更新
	m_backGroundMove->Update();

	//		プレイヤーの回転
	m_rotation += LibrarySingleton::GetInstance()->GetElpsedTime() * PLAYER_ROTATION_SPEED;

	//		プレイヤーのアニメーション
	m_playerAnimation->Execute(0.0f, PLAYER_POSITION, { m_rotation, 0.0f }, PLAYER_HEIGHT);
}

void ResultManager::Render()
{
	//		レンダーターゲットの変更
	m_screenEffectManager->ChangeRenderTarget();

	//		プレイヤーの描画(ワイヤー)
	m_playerAnimation->Render(true);

	//		レンダーターゲットを戻す
	m_screenEffectManager->FirstRenderTarget();

	//		移動背景の描画
	m_backGroundMove->Render();

	//		背景の描画(UI)
	m_shader->Render(ResultUIType::Back);

	//		レンダーターゲットの描画
	m_screenEffectManager->Render();

	//		状態の描画
	m_iState->Render();
}

void ResultManager::Finalize()
{
}


void ResultManager::CreateState()
{
	//		状態を生成する
	m_stateInformation.insert({State::Start, std::make_unique<ResultStart>(this)});
	m_stateInformation.insert({ State::NumberMove, std::make_unique<ResultNumberMove>(this) });
	m_stateInformation.insert({ State::Evaluation, std::make_unique<ResultEvaluation>(this) });
	m_stateInformation.insert({ State::Stay, std::make_unique<ResultStay>(this) });
	m_stateInformation.insert({ State::End, std::make_unique<ResultEnd>(this) });

	//		初期状態を代入する
	m_state = State::Start;

	//		初期状態を設定する
	m_iState = m_stateInformation[m_state].get();

	//		状態を初期化する
	m_iState->Initialize();
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
		m_iState = m_stateInformation[State::Stay].get();
	}
}

void ResultManager::CreateStandardShader()
{
	//		リザルトUIマネージャーの生成
	m_shader = std::make_unique<StandardShader<ResultManager::ResultUIType>>();

	//		初期化処理
	m_shader->Initialize();

	//		背景画像
	m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ResultBack.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f },
		ResultManager::ResultUIType::Back);

	//		スコアによって評価を変える
	if (2000.0f > m_score)
	{
		//		A評価の生成
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreA.png",
			{ 350.0f, 150.0f }, { 0.0f, 0.0f },
			ResultManager::ResultUIType::EvaluationUI);
	}
	else if (1000.0f > m_score)
	{
		//		B評価の生成
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreB.png",
			{ 350.0f, 150.0f }, { 0.0f, 0.0f },
			ResultManager::ResultUIType::EvaluationUI);
	}
	else
	{
		//		C評価の生成
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreC.png",
			{ 350.0f, 150.0f }, { 0.0f, 0.0f },
			ResultManager::ResultUIType::EvaluationUI);
	}

	//		次のシーン誘導の生成
	m_shader->CreateUIInformation(L"Resources/Texture/UI/GameOver/button.png",
		{ 0.0f, 280.0f }, { 1.0f, 1.0f },
		ResultManager::ResultUIType::Button);
}

void ResultManager::ChangeState(State state)
{
	//		同じ状態なら処理をしない
	if (m_state == state) return;

	//		現在の状態の終了処理をする
	m_iState->Finalize();

	m_state = state;

	//		状態を切り替える
	m_iState = m_stateInformation[state].get();

	//		新しい状態の初期化処理をする
	m_iState->Initialize();
}
