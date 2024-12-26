/*
* @file		MenuManager.cpp
* @brief	メニューのマネージャー
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuManager.h"

#include <Windows.h>

#include "Scene/SceneManager.h"

#include "Library/Mouse/MouseList.h"

MenuManager::MenuManager(SceneManager* sceneManager)
	:
	m_firstAudioMenuJudgement(true),
	m_sceneManager(sceneManager),
	m_menuUseJudgement(false),
	m_menuOpenJudgement(false)
{	
	//		メニューのUIの生成
	m_menuUI = std::make_unique<MenuUI>();

	//		メニューの流れの生成
	m_menuFlow = std::make_unique<MenuFlow>();

	//		メニューの流れの初期化
	m_menuFlow->Initialize();

	//		マウスの処理の生成
	m_mousePorcess = std::make_unique<MenuMouseProcess>();

	//		UIのマウスの当たり判定の生成
	m_collider = std::make_unique<UIMouseCollider>();

	//		ゲームの設定の生成
	m_gameSetting = std::make_unique<GameSetting>();

	//		メニューが開いているか判断するオブザーバの生成
	m_menuOpenObserver = std::make_unique<MenuOpenJudgementObserver>();

	//		オブザーバーを追加する
	AddObserver();
}

MenuManager::~MenuManager()
{
}

void MenuManager::Initialize()
{
	//		メニューUIの初期化処理
	m_menuUI->Initialize();

	//		マウスの処理の初期化
	m_mousePorcess->Initialize();

	AddMouseObserver();
}

void MenuManager::Update()
{
	//		メニューを使用することができるかどうか
	if (!m_menuUseJudgement) return;

	if (m_menuFlow->GetMenuStartJudgement())
	{
		//		メニューのオープン処理
		m_menuOpenObserver->MenuOpen();

		m_menuFlow->SetMenuStartJudgement(false);

		//		初期化処理
		Initialize();

		//		メニューを使用するかどうか
		m_menuOpenJudgement = true;
	}

	//		メニューの流れの更新
	m_menuFlow->Update();

	//		メニューを使用するかどうか
	if (!m_menuOpenJudgement)
	{
		return;
	}

	//		マウスの処理の更新
	m_mousePorcess->Update();

	//		メニューUIの更新処理
	m_menuUI->Update();

	//		当たり判定
	m_collider->CollitionProcess(m_menuUI->GetColliderInformation());

	//		メニューモードを終了するか
	if (m_menuFlow->GetMenuEndJugement())
	{
		//		終了処理
		Finalize();

		//		メニューを閉じる処理
		m_menuOpenObserver->MenuClose();
	}
}

void MenuManager::Render()
{
	//		メニューを使用しているかどうか
	if (!m_menuOpenJudgement) return;

	m_menuUI->Render();

	//		デバックフォント
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionX",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x), 0, 0);
	LibrarySingleton::GetInstance()->DebugFont(L"MousePositionY",
		static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y), 0, 30);
}

void MenuManager::Finalize()
{
	//		メニューの流れの終了処理
	m_menuFlow->Finalize();

	//		メニューのUIの終了処理
	m_menuUI->Finalize();

	//		マウスの処理の終了処理
	m_mousePorcess->Finalize();

	m_menuOpenJudgement = false;

	//		マウスキーの削除
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::MenuAudio);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::TabAudio);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::TabOption);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::TabGamePlay);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::ExitButton);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeletePressedObserver(KeyInputMouse::MouseList::MenuCloseButton);
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->DeleteKeepPushingObserver(KeyInputMouse::MouseList::Knob);
}

void MenuManager::KeyboardAddObserver()
{
	//		キーボードオブザーバーに追加する
	AddKeyboardObserver();
}

void MenuManager::AddObserver()
{
	//		メニュー背景オブザーバーに追加する（メニューUI）
	m_menuFlow->GetMenuBackGroundUIObserver()->AddObserver(m_menuUI.get());
	//		メニューTabオブザーバーに追加する（メニューUI）
	m_menuFlow->GetMenuTabUIObserver()->AddObserver(m_menuUI.get());
	//		マウスオブザーバーに追加する（メニュー）
	m_mousePorcess->AddMenuMouseObserver(m_menuUI.get());
	//		マウスオブザーバーに追加する（流れ）
	m_mousePorcess->AddMenuMouseObserver(m_menuFlow.get());
	//		メニュー選択オブザーバーに追加する(メニューUI)
	m_menuFlow->GetSelectTypeObserver()->AddObserver(m_menuUI.get());
	//		メニュータイトルオブザーバーに追加する(メニューUI)
	m_menuFlow->GetTitleUIUObserver()->AddObserver(m_menuUI.get());
	//		メニューアイコンUIオブザーバーに追加する（メニューUI）
	m_menuFlow->AddMenuIconUIObserver(m_menuUI.get());
	//		マウスオブザーバーに追加する（マウス当たり判定）
	m_mousePorcess->AddMenuMouseObserver(m_collider.get());

	//		当たり判定オブザーバーに追加する（メニューの流れ）
	m_collider->AddColliderObserver(m_menuFlow.get());
	//		当たり判定オブザーバーに追加する（メニューUI）
	m_collider->AddColliderObserver(m_menuUI.get());

	//		スライダーの値を設定に送るオブザーバーを追加する（設定）
	m_menuUI->AddSliderSettingValObserver(m_gameSetting.get());
}

void MenuManager::AddMouseObserver()
{
	//		マウス入力処理（メニューAudio）
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::MenuAudio);

	//		マウス入力処理（メニューTabAudio）
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::TabAudio);
	//		マウス入力処理（メニューTabOption）
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::TabOption);
	//		マウス入力処理（メニューTabGamePlay）
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::TabGamePlay);

	//		マウス入力処理（メニューButtonExit）
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::ExitButton);
	//		マウス入力処理（メニューButtonMenuClose）
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddPressedObserver(m_menuFlow.get(),
			KeyInputMouse::MouseState::leftButton,
			KeyInputMouse::MouseList::MenuCloseButton);

	//		マウス入力処理（メニューKnob）
	m_sceneManager->GetInformation()->GetMouseKeyInput()
		->GetMouseKeyInputObserver()->AddKeepPushingObserver(m_menuUI.get(),
			KeyInputMouse::MouseState::keepLeftButton,
			KeyInputMouse::MouseList::Knob);
}

void MenuManager::AddKeyboardObserver()
{
	//		キーボードの処理の追加
	m_sceneManager->GetInformation()->GetKeyboardManager()->
		AddKeyboard(m_menuFlow.get(), DirectX::Keyboard::Keys::Tab,
		KeyboardList::MenuOpen, KeyboardManager::Pressed);

	m_sceneManager->GetInformation()->GetKeyboardManager()->
		AddKeyboard(m_menuFlow.get(), DirectX::Keyboard::Keys::Tab,
			KeyboardList::MenuClose, KeyboardManager::Pressed);
}

void MenuManager::MenuUseJudgement(bool judgement)
{
	m_menuUseJudgement = judgement;
}

void MenuManager::MenuOpen()
{
	//		メニューを開く
	m_menuOpenJudgement = true;
}
