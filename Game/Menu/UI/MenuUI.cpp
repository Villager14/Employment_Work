/*
* @file		MenuUI.cpp
* @brief	メニューのUI
* @author	Morita
* @date		2024/12/18
*/

#include "pch.h"

#include "MenuUI.h"

MenuUI::MenuUI()
{
	//		当たり判定情報をまとめる
	m_summarizeColliderInformation = std::make_unique<MenuSummarizeColliderInformation>();

	//		上昇UIの生成
	m_aboveUI = std::make_unique<AboveUI>();

	//		スライダーの生成
	m_slider = std::make_unique<Slider>();

	//		メニューTabUIの生成
	m_menuTabUI = std::make_unique<MenuTabUI>(m_aboveUI.get(), m_summarizeColliderInformation.get());

	//		メニューの背景UIの生成
	m_menuBackGround = std::make_unique<MenuBackGround>();

	//		マウスUIの生成
	m_mousePointer = std::make_unique<MenuMousePointerUI>();

	//		タイトルUIの生成
	m_titleUI = std::make_unique<MenuTitle>(m_aboveUI.get());

	//		スライダーの処理
	m_sliderProcess = std::make_unique<MenuSliderProcess>(m_slider.get(), m_aboveUI.get());

	//		オーディオUIの生成
	m_menuAudio = std::make_unique<MenuAudioUI>(m_aboveUI.get(), m_slider.get(), m_summarizeColliderInformation.get());

	//		ゲームプレイUIの生成
	m_gamePlay = std::make_unique<MenuGamePlayUI>(m_aboveUI.get(), m_summarizeColliderInformation.get());

	//		オプションUIの生成
	m_menuOption = std::make_unique<MenuOption>(m_aboveUI.get(), m_slider.get(), m_summarizeColliderInformation.get());
}

MenuUI::~MenuUI()
{
}

void MenuUI::Initialize()
{
	//		上昇メニューの初期化処理
	m_aboveUI->Initialize();

	//		スライダーの初期化処理
	m_slider->Initialize();

	//		メニュータブ初期化処理
	m_menuTabUI->Initialize();

	//		メニューの背景UIの初期化
	m_menuBackGround->Initialize();

	//		マウスポインタUIの初期化
	m_mousePointer->Initialize();

	//		タイトルUIの初期化
	m_titleUI->Initialize();

	//		オーディオUIの初期化処理
	m_menuAudio->Initialize();

	//		オプションUIの初期化処理
	m_menuOption->Initialize();

	//		ゲームプレイUIの初期化処理
	m_gamePlay->Initialize();

	//		スライダーの処理の初期化
	m_sliderProcess->Initilaize();
}

void MenuUI::Update()
{
	//		メニューTabの更新
	m_menuTabUI->Update();

	//		オーディオの更新処理
	m_menuAudio->Update();

	//		オプションUIの更新処理
	m_menuOption->Update();

	//		ゲームプレイの更新処理
	m_gamePlay->Update();

	//		スライダーの処理
	m_sliderProcess->Update();
}

void MenuUI::Render()
{
	//		メニューの背景UIの描画
	m_menuBackGround->Render();

	//		メニューTabの描画
	m_menuTabUI->Render();

	//		タイトルの描画
	m_titleUI->Render();

	//		オーディオのUIの描画
	m_menuAudio->Render();

	//		オプションのUIの描画処理
	m_menuOption->Render();

	//		ゲームプレイUIの描画
	m_gamePlay->Render();

	//		マウスポインタUIの描画
	m_mousePointer->Render();
}

void MenuUI::Finalize()
{
	//		メニューTabの終了処理
	m_menuTabUI->Finalize();

	//		メニューの背景UIの終了処理
	m_menuBackGround->Finalize();

	//		マウスポインタUIの終了処理
	m_mousePointer->Finalize();

	//		タイトルの終了処理
	m_titleUI->Finalize();
}

void MenuUI::BackGroundBarScale(float scale)
{
	//		メニューの背景のバーのスケールを設定する
	m_menuBackGround->BarScale(scale);
}

void MenuUI::MenuMoveProcess(float move)
{
	//		メニューの移動処理の移動量を設定する
	m_menuBackGround->MenuMoveProcess(move);
}

void MenuUI::TabMove(float move)
{
	//		TabUIの移動量を設定する
	m_menuTabUI->TabMove(move);
}

void MenuUI::TabUseJudgement(float judgement)
{
	m_menuTabUI->TabUserJudgement(judgement);
}

void MenuUI::MousePositionX(int x)
{
	//		マウスのX座標を設定する
	m_mousePointer->SetMousePositionX(x);

	//		スライダーの座標X
	m_sliderProcess->SetMousePosition(x);
}

void MenuUI::MousePositionY(int y)
{
	//		マウスのY座標を設定する
	m_mousePointer->SetMousePositionY(y);
}

void MenuUI::SelectType(MenuUITaype::UIType type)
{
	//		タイトルのタイプを設定する
	m_titleUI->SetTitleType(type);

	//		ゲームタイプを設定する
	m_menuAudio->SetType(type);

	//		ゲームタイプを設定する
	m_menuOption->SetType(type);

	//		ゲームタイプを設定する
	m_gamePlay->SetType(type);
}

void MenuUI::TitleMoveProcess(float move)
{
	//		タイトルの移動量を設定する
	m_titleUI->TitleMoveProcess(move);

	//		タイトルの移動量
	m_menuAudio->TitleMoveProcess(move);

	//		タイトルの移動量
	m_menuOption->TitleMoveProcess(move);

	//		タイトルの移動量
	m_gamePlay->TitleMoveProcess(move);
}

void MenuUI::IconMoveProcess(float move)
{
	//		スライダーの移動量を設定する
	m_menuAudio->ButtonMoveProcess(move);

	//		スライダーの移動量を設定する
	m_menuOption->ButtonMoveProcess(move);

	//		スライダーの移動量を設定する
	m_gamePlay->ButtonMoveProcess(move);
}

void MenuUI::IsKeyPressed(KeyInputMouse::MouseList key)
{
	if (KeyInputMouse::MouseList::Knob)
	{
		m_sliderProcess->MouseInputJudgement(true);
	}
}

void MenuUI::IsKeyReleased(KeyInputMouse::MouseList key)
{
}

void MenuUI::IsKeepPushing(KeyInputMouse::MouseList key)
{
}

void MenuUI::HitUIType(UISubType type)
{
	if (type == UISubType::TabAudio)
	{
		//		Tabのタイプを設定する
		m_menuTabUI->SetTabType(MenuUITaype::UIType::Audio);
	}
	else if (type == UISubType::TabGamePlay)
	{
		//		Tabのタイプを設定する
		m_menuTabUI->SetTabType(MenuUITaype::UIType::GamePlay);
	}
	else if (type == UISubType::TabOption)
	{
		//		Tabのタイプを設定する
		m_menuTabUI->SetTabType(MenuUITaype::UIType::Option);
	}
	//		ゲームプレイ
	else if (type == UISubType::GameExitButton ||
			 type == UISubType::CloseMenuButton)
	{
		m_gamePlay->HitBunnton(type);
	}
	else if (type == UISubType::BGMKnob ||
			 type == UISubType::SoundEffectKnob ||
			 type == UISubType::MastarVolumKnob ||
			 type == UISubType::MouseSpeedKnob ||
			 type == UISubType::FovKnob)
	{
		m_sliderProcess->HitBunnton(type);
	}
}
