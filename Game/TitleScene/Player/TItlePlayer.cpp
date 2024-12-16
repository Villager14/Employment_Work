/*
* @file		TitlePlayer.cpp
* @brief	タイトルプレイヤーの処理
* @author	Morita
* @date		2024/12/13
*/

#include "pch.h"

#include "TItlePlayer.h"

TitlePlayer::TitlePlayer()
{
	//		プレイヤーのアニメーションの作製
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::Title);

	//		ポスエフェクトフラグ
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Initialize()
{
	//		プレイヤーのアニメーション初期化
	m_playerAnimation->Initialize();
	//		ポストエフェクトフラグ
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
	//		通常描画をするようにする
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);
	//		ブルームを掛けるようにする
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::Bloom);
	//		ブルームの深度描画は描画しない
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);
	//		フォグの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);
}

void TitlePlayer::Update()
{
	//		プレイヤーのアニメーション
	m_playerAnimation->Execute(0.0f, { 0.0f, 2.0f, 0.0f },
		{ 180.0f, 0.0f }, 2.5f);
}

void TitlePlayer::Render(PostEffectFlag::Flag flag)
{
	//		フラグがオフの場合処理をしない
	if (!m_postEffectFlag->FlagJudgement(flag)) return;

	m_playerAnimation->Render();
}

void TitlePlayer::Finalize()
{
	m_playerAnimation->Finalize();
}

void TitlePlayer::PlayAnimation()
{
	m_playerAnimation->ChangeState(AnimationManager::Stay);
}

void TitlePlayer::SettingAnimation()
{
	m_playerAnimation->ChangeState(AnimationManager::Upright);
}

void TitlePlayer::ExitAnimation()
{
	m_playerAnimation->ChangeState(AnimationManager::Sliding);
}
