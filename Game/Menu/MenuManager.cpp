/*
* @file		MenuManager.cpp
* @brief	メニューのマネージャー
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuManager.h"

MenuManager::MenuManager()
	:
	m_state()
{
}

MenuManager::~MenuManager()
{
}

void MenuManager::Initialize()
{
	//		状態の生成
	m_menuStateInformation.insert({ Start, std::make_unique<MenuStart>(this) });
	m_menuStateInformation.insert({ Audio, std::make_unique<AudioSetting>(this) });

	m_type = Start;

	//		初期の状態
	m_state = m_menuStateInformation[m_type].get();

	//		初期化処理
	m_state->Initialize();

	//		バー１
	CreateUIRender(Bar1, L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, 13.0f }, { 0.0f, 1.0f });

	//		バー２
	CreateUIRender(Bar2, L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, -13.0f }, { 0.0f, 1.0f });

	//		背景
	CreateUIRender(BackGround, L"Resources/Texture/UI/GameClear/messegeBack.png",
		{ 0.0f, 0.0f }, { 1.0f, 0.0f });

	//		Audio選択
	CreateUIRender(AudioSelect, L"Resources/Texture/Menu/Select/Audio.png",
		{ -380.0f, -200.0f }, { 1.0f, 1.0f });

	//		GamePlay選択
	CreateUIRender(GamePlaySelect, L"Resources/Texture/Menu/Select/GamePlay.png",
		{ -380.0f, -80.0f }, { 1.0f, 1.0f });

	//		Opetion選択
	CreateUIRender(OptionSelect, L"Resources/Texture/Menu/Select/Opetion.png",
		{ -380.0f, 40.0f }, { 1.0f, 1.0f });

	//		スライダー選択
	CreateUIRender(Slide, L"Resources/Texture/Menu/Slide/SlideBack.png",
		{ 0.0f, 0.0f }, { 0.8f, 0.8f });

	//		Audioタイトル
	CreateUIRender(AudioTitle, L"Resources/Texture/Menu/Title/AudioSetting.png",
		{ 200.0f, -240.0f }, { 1.0f, 1.0f });


	
}

void MenuManager::Update()
{
	//		更新処理
	m_state->Update();
}

void MenuManager::Render()
{
	//		描画処理
	m_state->Render();
}

void MenuManager::Finalize()
{
}

void MenuManager::MenuBackRneder()
{
	m_uiRender[BackGround]->Render();
	m_uiRender[Bar1]->Render();
	m_uiRender[Bar2]->Render();
}

void MenuManager::SliderRender(DirectX::SimpleMath::Vector2 position)
{
	m_uiRender[Slide]->SetPosition(position);
	m_uiRender[Slide]->Render();
}

void MenuManager::ChangState(MenuType type)
{
	//		同じタイプの場合処理をしない
	if (m_type == type) return;

	//		終了処理
	m_state->Finalize();

	//		タイプの更新
	m_type = type;

	//		状態の更新
	m_state = m_menuStateInformation[type].get();

	//		初期化処理
	m_state->Initialize();
}

void MenuManager::CreateUIRender(UIType type, const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 size)
{
	//		UIRenderの生成
	std::unique_ptr<UIRender> uiRender = std::make_unique<UIRender>();

	//		UIRenderの作成
	uiRender->Create(path, position, size);

	//		UiRenderに代入数
	m_uiRender.insert({type, move(uiRender)});
}
