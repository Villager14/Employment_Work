/*
* @file		GameManager.cpp
* @brief	ゲームマネージャー
* @author	Morita
* @date		2024/05/22
*/

#include "pch.h"

#include "GameManager.h"

GameManager::GameManager()
	:
	m_time(0.0f),
	m_deathCount(0),
	m_gameSpeed(1.0f),
	m_flag(0),
	m_limitTime(0.0f)
{
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
	m_flag = Flag::None;
	m_time = 0.0f;
	m_deathCount = 0;
	m_gameSpeed = 0.0f;
	m_limitTime = 0.0f;
}

void GameManager::Update(PostEffectInformation* postEffectInformation)
{
	//		シーンを終了するとき
	if (FlagJudgement(Flag::EndJudgement))
	{
		//		ポストエフェクトのフェード
		postEffectInformation->TrueFlag(PostEffectInformation::Flag::SceneEndFade);
	}

	//		死亡していない場合以下の処理をしない
	if (!FlagJudgement(Flag::DeathJudgement)) return;

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		マウスの取得
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Spaceまたは左クリックを押した場合復活する
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		postEffectInformation->TrueFlag(PostEffectInformation::Flag::FadeJudgement);
	}

	//		フェードが終了すると
	if (postEffectInformation->FlagJudgement(PostEffectInformation::Flag::FadeEnd))
	{
		//		死亡状態をFlaseにする
		FalseFlag(GameManager::DeathJudgement);
		postEffectInformation->FalseFlag(PostEffectInformation::Flag::FadeEnd);
		postEffectInformation->FalseFlag(PostEffectInformation::Flag::RedScreen);
	}

	if (FlagJudgement(GameManager::DeathJudgement))
	{
		//		画面を赤くする
		postEffectInformation->TrueFlag(PostEffectInformation::Flag::RedScreen);
	}

	//		シーンを終了するとき
	if (FlagJudgement(Flag::TimeLimitJudgement))
	{
		//		ポストエフェクトのフェード
		postEffectInformation->TrueFlag(PostEffectInformation::Flag::TimeLimitJudgement);
		
		//		画面を赤くする
		postEffectInformation->TrueFlag(PostEffectInformation::Flag::RedScreen);
	}
}

void GameManager::Finalize()
{
	m_flag = Flag::None;
	m_time = 0.0f;
	m_deathCount = 0;
	m_gameSpeed = 0.0f;
	m_limitTime = 0.0f;
}

bool GameManager::FlagJudgement(Flag flag)
{
	//		両方のビットが１の場合
	if (m_flag & flag) return true;

	return false;
}

void GameManager::TrueFlag(Flag flag)
{
    m_flag |= flag;
}

 void GameManager::FalseFlag(Flag flag)
 {
	//		フラグがオンの時はオフにする
	m_flag &= ~flag;
 }
