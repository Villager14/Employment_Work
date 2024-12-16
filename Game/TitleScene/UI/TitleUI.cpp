/*
* @file		TitleUI.h
* @brief	タイトルのUI
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitleUI.h"

TitleUI::TitleUI()
{
	//		タイトルの背景の生成
	m_backGround = std::make_unique<BackGroundMove>();

	//		選択バーの生成
	m_selectionBar = std::make_unique<SelectionBar>();

	//		キーガイダンスの生成
	m_keyGuidance = std::make_unique<TitleKeyGuidance>();

	//		フェードUIの生成
	m_fadeUI = std::make_unique<FadeUI>();
}

TitleUI::~TitleUI()
{
}

void TitleUI::Initalize()
{
	Generation();

	//		タイトルの背景の移動処理の初期化
	m_backGround->Initialize();

	//		選択バーの初期化
	m_selectionBar->Initialize();

	//		キーガイダンスの初期化
	m_keyGuidance->Initialize();

	//		フェードUIの初期化
	m_fadeUI->Initialize();
}

void TitleUI::Update()
{
	//		背景の更新処理
	m_backGround->Update();

	//		フェードアウトの更新
	m_fadeUI->Update();
}

void TitleUI::Render(int postEffectType)
{
	if (postEffectType == PostEffectFlag::PostEffectFlag::UI)
	{
		//		フェードUIの描画
		m_fadeUI->Render();
	}
	else if (postEffectType == PostEffectFlag::PostEffectFlag::UIBack)
	{
		//		タイトルロゴの描画
		m_standardShader->Render(TitleUIType::TitleRogo);

		//		選択バーの描画
		m_selectionBar->Render();

		//		キーガイダンスの描画
		m_keyGuidance->Render();
	}
}

void TitleUI::Generation()
{
	//		タイトルUIマネージャーの生成
	m_standardShader = std::make_unique<StandardShader<TitleUIType>>();

	//		タイトルUIマネージャの初期化
	m_standardShader->Initialize();

	//		タイトルロゴの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/TitleRogo.png",
		TITLE_POINT, { MAX_SCALE, MAX_SCALE },
		TitleUIType::TitleRogo);
}

void TitleUI::Finalize()
{
	//		背景の終了処理
	m_backGround->Finalize();

	//		選択バーの終了処理
	m_selectionBar->Finalize();

	//		キーガイドの終了処理
	m_keyGuidance->Finalize();

	//		フェードUIの終了処理
	m_fadeUI->Finalize();
}

void TitleUI::DownSelect(float processingTime)
{
	//		選択バーの下移動処理
	m_selectionBar->DownSelect(processingTime);

	//		キーガイドの下移動処理
	m_keyGuidance->DownSelect(processingTime);
}

void TitleUI::UpSelect(float processingTime)
{
	//		選択バーの上移動処理
	m_selectionBar->UpSelect(processingTime);

	//		キーガイドの上移動処理
	m_keyGuidance->UpSelect(processingTime);
}

void TitleUI::SceneEndFadeOut()
{

}

void TitleUI::FadeOut()
{
	//		フェードアウトを行う
	m_fadeUI->FadeOutUse();
}
