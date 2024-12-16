/*
* @file		TitleFlowManager.cpp
* @brief	タイトルの流れマネージャー
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitleFlowManager.h"

#include "State/SelectPlayState.h"
#include "State/SelectEndState.h"
#include "State/SelectSettingState.h"
#include "State/ChangeSceneState.h"
#include "State/StartSceneState.h"

TitleFlowManager::TitleFlowManager()
	:
	m_iState(nullptr),
	m_state(State::StartState),
	m_fadeInEndJudgement(false),
	m_keyInputJudgement(false),
	m_time(0.0f),
	m_scrollWheel(0)
{
	//		タイトルUIオブザーバーの生成
	m_titleUIObserver = std::make_unique<TitleUIObserver>();

	//		フェードオブザーバーの生成
	m_fadeObserver = std::make_unique<FadeObserver>();

	//		ゲーム終了オブザーバー
	m_gameExitObserver = std::make_unique<TitleGameExitObserver>();

	//		メニュー使用オブザーバー
	m_menuUseObserver = std::make_unique<TitleMenuUseObserver>();

	//		タイトルプレイヤーアニメーションオブザーバー
	m_animationObserver = std::make_unique<TitlePlayerAnimationObserver>();
}

TitleFlowManager::~TitleFlowManager()
{
}

void TitleFlowManager::Initialize()
{
	//		フェードインが終了していない状態にする
	m_fadeInEndJudgement = false;

	//		移動状況は何もない状態にしておく
	m_selectionBarMoveDirection = SelectionBarMoveDirection::Not;

	//		状態の情報を設定する
	m_stateInformation.insert({ State::PlayState, std::make_unique<SelectPlayState>(this) });
	m_stateInformation.insert({ State::EndState, std::make_unique<SelectEndState>(this) });
	m_stateInformation.insert({ State::SettingState, std::make_unique<SelectSettingState>(this) });
	m_stateInformation.insert({ State::StartState, std::make_unique<StartSceneState>(this) });
	m_stateInformation.insert({ State::ChangState, std::make_unique<ChangeSceneState>(this) });

	//		初期の状態
	m_state = State::StartState;

	//		状態の更新
	m_iState = m_stateInformation[m_state].get();

	//		初期化する
	m_iState->Initialize();
}

void TitleFlowManager::Update()
{
	//		現在の状態の更新
	m_iState->Update();
}

void TitleFlowManager::Finalize()
{
	m_fadeInEndJudgement = false;
	m_keyInputJudgement = false;
	m_scrollWheel = 0;

	//		オブザーバーの削除
	m_titleUIObserver->Dalete();
	m_gameExitObserver->Dalete();
	m_fadeObserver->Dalete();
	m_menuUseObserver->Dalete();
}

void TitleFlowManager::FadeIn()
{
	//		フェードインの終了
	m_fadeInEndJudgement = true;
}

void TitleFlowManager::FadeOut()
{

}

void TitleFlowManager::InputKey()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		SボタンORマウスホイール上で上に移動
	if (keyboard.IsKeyPressed(DirectX::Keyboard::S) || 
		m_scrollWheel < DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		もし移動処理をしている場合は処理をしない
		if (!m_keyInputJudgement)
		{
			//		キーを押している
			m_keyInputJudgement = true;
			//		移動する向き（上）
			m_selectionBarMoveDirection = SelectionBarMoveDirection::Up;

			//		選択効果音
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		m_scrollWheel = DirectX::Mouse::Get().GetState().scrollWheelValue;
	}

	//		WボタンORマウスホイールしたで下に移動
	if (keyboard.IsKeyPressed(DirectX::Keyboard::W) ||
		m_scrollWheel > DirectX::Mouse::Get().GetState().scrollWheelValue)
	{
		//		もし移動処理をしている場合は処理をしない
		if (!m_keyInputJudgement)
		{
			//		キーを押している
			m_keyInputJudgement = true;

			//		移動する向き（下）
			m_selectionBarMoveDirection = SelectionBarMoveDirection::Down;

			//		選択効果音
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Select);
		}

		//		ホイールの値を更新する
		m_scrollWheel = DirectX::Mouse::Get().GetState().scrollWheelValue;
	}
}

bool TitleFlowManager::SelectionBarMoveProcess()
{
	//		移動方向がNotの場合移動しない
	if (m_selectionBarMoveDirection == SelectionBarMoveDirection::Not) return false;

	//		メニューを使用できないようにする
	m_menuUseObserver->DisableMenu();

	//		移動速度
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * MOVE_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		移動方向が上の場合
	if (m_selectionBarMoveDirection == SelectionBarMoveDirection::Up)
	{
		m_titleUIObserver->UpSelect(m_time);
	}
	//		移動方向が下の場合
	else
	{
		m_titleUIObserver->DownSelect(m_time);
	}

	if (m_time >= 1.0f)
	{
		//		メニューを使用できるようにする
		m_menuUseObserver->EnableMenu();

		return true;
	}

	return false;
}

void TitleFlowManager::SelectionInfromationReset()
{
	m_time = 0.0f;

	m_selectionBarMoveDirection = SelectionBarMoveDirection::Not;

	m_keyInputJudgement = false;
}

void TitleFlowManager::ChangeState(State state)
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