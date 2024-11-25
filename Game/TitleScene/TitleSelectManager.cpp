/*
* @file		BackGroundMove.cpp
* @brief	タイトルの選択マネージャー
* @author	Morita
* @date		2024/05/25
*/

#include "pch.h"

#include "TitleSelectManager.h"

#include "State/SelectPlayState.h"
#include "State/SelectEndState.h"
#include "State/SelectSettingState.h"
#include "State/ChangeSceneState.h"
#include "State/StartSceneState.h"

TitleSelectManager::TitleSelectManager(PostEffectManager* postEffectManager)
	:
	m_iState(),
	m_state{},
	m_menuInformation(nullptr),
	m_postEffectManager(postEffectManager)
{
	Generation();
}

TitleSelectManager::~TitleSelectManager()
{
}

void TitleSelectManager::Initialize()
{
	//		マウスのフォールチをリセットする
	DirectX::Mouse::Get().ResetScrollWheelValue();

	//		スタンダードシェーダーの作製
	CreateStandardShader();

	//		情報の初期化
	m_information->Initilaize(m_backGroundMove.get(), m_standardShader.get());

	//		背景の初期化
	m_backGroundMove->Initialize();

	//		プレイヤーのアニメーション初期化
	m_playerAnimation->Initialize();

	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::UI);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::PlayerView);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::UIBack);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Fade);

	//		ポストエフェクトマネージャーの初期化処理
	m_postEffectManager->Initialize(DirectX::Colors::White, m_posteffectFlag.get());

	//----
	//		タイトルの状態の作製
	//---

	//		初期の状態
	m_state = TitleInformation::State::StartState;
	
	m_iState = (*m_information->GetStateInformation())[m_state].get();

	//		初期化する
	m_iState->Initialize();
}

void TitleSelectManager::Generation()
{
	//		タイトル情報を設定する
	m_information = std::make_unique<TitleInformation>();

	//		背景の生成
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		タイトル共通処理の生成
	m_commonProcess = std::make_unique<TitleCommonProcess>(m_information.get());

	//		プレイヤーのアニメーションの作製
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::Title);

	//		ポストエフェクトフラグの作製
	m_posteffectFlag = std::make_unique<PostEffectFlag>();

	//----
	//		タイトルの状態の作製
	//---

	auto stateInformation = m_information->GetStateInformation();

	//		状態の情報を設定する
	(*stateInformation).insert({ TitleInformation::State::PlayState, std::make_unique<SelectPlayState>(this) });
	(*stateInformation).insert({ TitleInformation::State::EndState, std::make_unique<SelectEndState>(this) });
	(*stateInformation).insert({ TitleInformation::State::SettingState, std::make_unique<SelectSettingState>(this) });
	(*stateInformation).insert({ TitleInformation::State::StartState, std::make_unique<StartSceneState>(this) });
	(*stateInformation).insert({ TitleInformation::State::ChangState, std::make_unique<ChangeSceneState>(this) });

	//		描画順を設定する
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::Play);
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::Setting);
	(*m_information->GetDraowOder()).push_back(TitleInformation::TitleUIType::End);
}

void TitleSelectManager::Update()
{
	//		背景の更新処理
	m_backGroundMove->Update();

	//		メニューを開いている場合は処理をしない
	if (m_menuInformation->GetMenuJudgement()) return;

	//		プレイヤーのアニメーション
	m_playerAnimation->Execute(0.0f, { 0.5f, -2.0f, 1.05f },
		{ 180.0f, 0.0f }, 2.5f);

	//		更新処理
	m_iState->Update();

	//		ポストエフェクトの更新
	for (int i = 1; i <= PostEffectFlag::Fade;)
	{
		//		フラグが立っていない処理は行わない
		if (!m_posteffectFlag->FlagJudgement(PostEffectFlag::Flag(i)))
		{
			i = i + i;

			continue;
		}

		//		ポストエフェクトの更新
		m_postEffectManager->Update(PostEffectFlag::Flag(i));

		i = i + i;
	}
}

void TitleSelectManager::Render()
{
	//		ポストエフェクトの更新
	for (int i = 1; i <= PostEffectFlag::Fade;)
	{
		//		フラグが立っていない処理は行わない
		if (!m_posteffectFlag->FlagJudgement(PostEffectFlag::Flag(i)))
		{
			i = i + i;

			continue;
		}

		//		ポストエフェクトの更新
		m_postEffectManager->Render(PostEffectFlag::Flag(i));

		if (i == PostEffectFlag::Flag::UI)
		{
			//		背景の描画
			m_backGroundMove->Render();
		}

		if (i == PostEffectFlag::Flag::PlayerView)
		{
			m_playerAnimation->Render();
		}

		if (i == PostEffectFlag::Flag::UIBack)
		{
			//		選択の描画
			for (int j = 0, max = static_cast<int>((*m_information->GetDraowOder()).size()); j < max; ++j)
			{
				//		選択UIの描画
				m_information->GetStandardShader()->Render((*m_information->GetDraowOder())[j]);
			}

			//		スペース
			m_standardShader->Render(TitleInformation::TitleUIType::Space);

			//		タイトルロゴの描画
			m_standardShader->Render(TitleInformation::TitleUIType::TitleRogo);

			//		描画処理
			m_iState->Render();
		}

		//		ポストエフェクトマネージャーのラスト描画
		m_postEffectManager->RastRender(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		レンダーテクスチャをリセットする
	m_postEffectManager->ResetRenderTarget();

	//		レンダーテクスチャの描画
	m_postEffectManager->RenderTextureView();
}

void TitleSelectManager::Finalize()
{
	//		情報の初期化
	m_information->Finalize();

	m_playerAnimation->Finalize();

	m_backGroundMove->Finalize();

	m_standardShader.reset();

	m_postEffectManager->Finalize();
}

void TitleSelectManager::CreateStandardShader()
{
	//		タイトルUIマネージャーの生成
	m_standardShader = std::make_unique<StandardShader<TitleInformation::TitleUIType>>();

	//		タイトルUIマネージャの初期化
	m_standardShader->Initialize();

	//		タイトルロゴの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/TitleRogo.png",
		m_information->TITLE_POINT, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::TitleRogo);

	//		Playの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitlePlay.png",
		m_information->CENTER_POINT, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::Play);

	//		Endの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleEnd.png",
		m_information->UP_POINT , { m_information->MIN_SCALE,
		 m_information->MIN_SCALE },
		TitleInformation::TitleUIType::End);

	//		Settingの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleSetting.png",
		m_information->UNDER_POINT, { m_information->MIN_SCALE,
		 m_information->MIN_SCALE },
		TitleInformation::TitleUIType::Setting);

	//		Spaceの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/Space.png",
		m_information->SPACE_PLAY, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::Space);

	//		Wの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/W.png",
		m_information->W_END, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::W);

	//		Aの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/A.png",
		m_information->A_SETTING, { m_information->MAX_SCALE,
		m_information->MAX_SCALE },
		TitleInformation::TitleUIType::A);
}

void TitleSelectManager::ChangeState
(TitleInformation::State state)
{
	//		同じ状態なら処理をしない
	if (m_state == state) return;

	//		現在の状態の終了処理をする
	m_iState->Finalize();

	//		状態を切り替える
	m_state = state;

	//		状態を切り替える
	m_iState = (*m_information->GetStateInformation())[m_state].get();

	//		新しい状態の初期化処理をする
	m_iState->Initialize();
}