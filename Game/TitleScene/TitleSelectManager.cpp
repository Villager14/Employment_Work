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

TitleSelectManager::TitleSelectManager()
	:
	m_inputKey(false),
	m_direction(false),
	m_scrollWheeel(0),
	m_changeSceneJudgement(false),
	m_iState(),
	m_menuJudgement(false),
	m_state{}
{
}

TitleSelectManager::~TitleSelectManager()
{
}

void TitleSelectManager::Initialize()
{
	//		マウスのフォールチをリセットする
	DirectX::Mouse::Get().ResetScrollWheelValue();

	//		背景の生成
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		背景の初期化
	m_backGroundMove->Initialize();

	//		状態の情報を設定する
	m_stateInformation.insert({ State::PlayState, std::make_unique<SelectPlayState>(this) });
	m_stateInformation.insert({ State::EndState, std::make_unique<SelectEndState>(this) });
	m_stateInformation.insert({ State::SettingState, std::make_unique<SelectSettingState>(this) });
	m_stateInformation.insert({ State::StartState, std::make_unique<StartSceneState>(this) });
	m_stateInformation.insert({ State::ChangState, std::make_unique<ChangeSceneState>(this) });

	//		初期の状態
	m_state = State::StartState;

	//		初期の状態
	m_iState = m_stateInformation[m_state].get();

	//		初期化する
	m_iState->Initialize();

	//		フェードの生成
	m_fade = std::make_unique<FadeRender>();

	//		UI描画の作製
	m_fade->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		描画順を設定する
	m_drawOder.push_back(TitleUIType::Play);
	m_drawOder.push_back(TitleUIType::Setting);
	m_drawOder.push_back(TitleUIType::End);

	//		スタンダードシェーダーの作製
	CreateStandardShader();
}

void TitleSelectManager::Update()
{
	//		背景の更新処理
	m_backGroundMove->Update();

	//		メニューを開いている場合は処理をしない
	if (m_menuJudgement) return;

	//		更新処理
	m_iState->Update();
}

void TitleSelectManager::Render()
{
	//		背景の描画
	m_backGroundMove->Render();

	//		メニューを開いている場合は処理をしない
	if (m_menuJudgement) return;

	//		選択の描画
	for (int i = 0, max = static_cast<int>(m_drawOder.size()); i < max; ++i)
	{
		//		選択UIの描画
		m_standardShader->Render(m_drawOder[i]);
	}

	//		タイトルロゴの描画
	m_standardShader->Render(TitleUIType::TitleRogo);

	//		描画処理
	m_iState->Render();

}

void TitleSelectManager::Finalize()
{
}

void TitleSelectManager::InputKey()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		WボタンORマウスホイール上で上に移動
	if (keyboard.IsKeyPressed(DirectX::Keyboard::W)|| 
		m_scrollWheeel < DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		もし移動処理をしている場合は処理をしない
		if (!m_inputKey)
		{
			m_inputKey = true;
			m_direction = true;

			//		選択効果音
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		m_scrollWheeel = DirectX::Mouse::Get().GetState().scrollWheelValue;
	}

	//		SボタンORマウスホイールしたで下に移動
	if (keyboard.IsKeyPressed(DirectX::Keyboard::S) ||
		m_scrollWheeel > DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		もし移動処理をしている場合は処理をしない
		if (!m_inputKey)
		{
			m_inputKey = true;
			m_direction = false;

			//		選択効果音
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		//		ホイールの値を更新する
		m_scrollWheeel = DirectX::Mouse::Get().GetState().scrollWheelValue;
	}
}

void TitleSelectManager::CreateStandardShader()
{
	//		タイトルUIマネージャーの生成
	m_standardShader = std::make_unique<StandardShader<TitleUIType>>();

	//		タイトルUIマネージャの初期化
	m_standardShader->Initialize();

	//		タイトルロゴの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/TitleRogo.png",
		{ 0.0f, -170.0f }, { MAX_SCALE,
		MAX_SCALE },
		TitleSelectManager::TitleUIType::TitleRogo);

	//		Playの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitlePlay.png",
		CENTER_POINT, { MAX_SCALE,
		MAX_SCALE },
		TitleSelectManager::TitleUIType::Play);

	//		Endの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleEnd.png",
		UP_POINT, { MIN_SCALE,
		MIN_SCALE },
		TitleSelectManager::TitleUIType::End);

	//		Settingの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/TitleSetting.png",
		UNDER_POINT, { MIN_SCALE,
		MIN_SCALE },
		TitleSelectManager::TitleUIType::Setting);


}

void TitleSelectManager::ChangeState(State state)
{
	//		同じ状態なら処理をしない
	if (m_state == state) return;

	//		現在の状態の終了処理をする
	m_iState->Finalize();

	//		状態を切り替える
	m_state = state;

	//		状態を切り替える
	m_iState = m_stateInformation[m_state].get();

	//		新しい状態の初期化処理をする
	m_iState->Initialize();
}

void TitleSelectManager::CentreUP(bool direction, float time, TitleUIType type)
{
	//		遷移量
	float move = 0.0f;
	//		遷移量
	float size = 0.0f;

	//		初期座標
	DirectX::SimpleMath::Vector2 firstPosition;
	//		最終座標
	DirectX::SimpleMath::Vector2 endPosition;

	//		初期サイズ
	float firstSize = 0.0f;
	//		最終サイズ
	float endSize = 0.0f;

	//		描画順を最後にする
	m_drawOder[2] = type;

	//		移動方向を見て処理を変える
	if (direction)
	{
		firstPosition = CENTER_POINT;
		endPosition = UP_POINT;

		//		移動の遷移量
		move = sqrt(1.0f - pow(time - 1.0f, 2.0f));
		//		サイズの遷移量
		size = 1.0f - sqrt(1 - pow(time, 2.0f));

		//		初期サイズを設定
		firstSize = MAX_SCALE;
		//		最終サイズを設定
		endSize = MIN_SCALE;
	}
	else
	{
		firstPosition = UP_POINT;
		endPosition = CENTER_POINT;

		//		移動の遷移量
		move = 1.0f - sqrt(1.0f - pow(time, 2.0f));
		//		サイズの遷移量
		size = sqrt(1.0f - pow(time - 1.0f, 2.0f));

		//		初期サイズを設定
		firstSize = MIN_SCALE;
		//		最終サイズを設定
		endSize = MAX_SCALE;
	}

	//		座標を設定する
	(*m_standardShader->GetUIInformation())[type].position = DirectX::SimpleMath::Vector2::Lerp(firstPosition, endPosition, move);

	//		サイズを設定する
	(*m_standardShader->GetUIInformation())[type].scale = DirectX::SimpleMath::Vector2::Lerp({ firstSize, firstSize }, { endSize, endSize }, size);
}

void TitleSelectManager::CenterUnder(bool direction, float time, TitleUIType type)
{
	//		遷移量
	float move = 0.0f;
	//		遷移量
	float size = 0.0f;

	//		初期座標
	DirectX::SimpleMath::Vector2 firstPosition;
	//		最終座標
	DirectX::SimpleMath::Vector2 endPosition;

	//		初期サイズ
	float firstSize = 0.0f;
	//		最終サイズ
	float endSize = 0.0f;

	//		描画順を中間にする
	m_drawOder[1] = type;

	//		移動方向を見て処理を変える
	if (direction)
	{
		firstPosition = UNDER_POINT;
		endPosition = CENTER_POINT;

		//		移動の遷移量
		move = 1.0f - sqrt(1.0f - pow(time, 2.0f));
		//		サイズの遷移量
		size = sqrt(1.0f - pow(time - 1.0f, 2.0f));

		//		初期サイズを設定
		firstSize = MIN_SCALE;
		//		最終サイズを設定
		endSize = MAX_SCALE;
	}
	else
	{
		firstPosition = CENTER_POINT;
		endPosition = UNDER_POINT;

		//		移動の遷移量
		move = sqrt(1.0f - pow(time - 1.0f, 2.0f));
		//		サイズの遷移量
		size = 1.0f - sqrt(1.0f - pow(time, 2.0f));

		//		初期サイズを設定
		firstSize = MAX_SCALE;
		//		最終サイズを設定
		endSize = MIN_SCALE;
	}

	//		座標を設定する
	(*m_standardShader->GetUIInformation())[type].position = DirectX::SimpleMath::Vector2::Lerp(firstPosition, endPosition, move);

	//		サイズを設定する
	(*m_standardShader->GetUIInformation())[type].scale = DirectX::SimpleMath::Vector2::Lerp({ firstSize, firstSize }, { endSize, endSize }, size);
}

void TitleSelectManager::UPUnder(bool direction, float time, TitleUIType type)
{
	//		遷移量
	float move = 0.0f;
	//		遷移量
	float size = 0.0f;

	//		初期座標
	DirectX::SimpleMath::Vector2 firstPosition;
	//		最終座標
	DirectX::SimpleMath::Vector2 endPosition;

	//		初期サイズ
	float firstSize = MIN_SCALE - 0.5f;
	//		最終サイズ
	float endSize = MIN_SCALE;

	//		描画順を最初にする
	m_drawOder[0] = type;

	//		移動方向を見て処理を変える
	if (direction)
	{
		firstPosition = UP_POINT;
		endPosition = UNDER_POINT;
	}
	else
	{
		firstPosition = UNDER_POINT;
		endPosition = UP_POINT;
	}

	move = time * time * time;

	float radian = Library::Lerp(0.0f, 360.0f, move);

	
	size = (cosf(DirectX::XMConvertToRadians(radian)) / 2.0f + 0.5f);

	size = Library::Clamp(size, 0.0f, 1.0f);

	//		座標を設定する
	(*m_standardShader->GetUIInformation())[type].position = DirectX::SimpleMath::Vector2::Lerp(firstPosition, endPosition, move);

	//		サイズを設定する
	(*m_standardShader->GetUIInformation())[type].scale = DirectX::SimpleMath::Vector2::Lerp({ firstSize, firstSize }, { endSize, endSize }, size);
}