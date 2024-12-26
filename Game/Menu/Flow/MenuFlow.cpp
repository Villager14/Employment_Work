/*
* @file		MenuFlow.cpp
* @brief	メニューの流れ
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuFlow.h"

#include "State/MenuStandby.h"
#include "State/MenuStart.h"
#include "State/AudioSetting.h"
#include "State/OptionSetting.h"
#include "State/EndSetting.h"
#include "State/MenuClose.h"

#include "MenuFlowCommonProcess.h"

MenuFlow::MenuFlow()
	:
	m_state(),
	m_type{},
	m_mousePositionX(0),
	m_mousePositoinY(0),
	m_firstProcess(false),
	m_menuEndJudgemnet(false),
	m_meneStartJudgement(false),
	m_menuOpenKeyJudgement(false)
{
	CreateState();

	//		メニューの背景UIオブザーバーの生成
	m_menuBackGroundUIObserver = std::make_unique<MenuBackGroundUIObserver>();

	//		メニューTabUIオブザーバーの生成
	m_menuTabUIObserver = std::make_unique<MenuTabUIObserver>();

	//		メニュー共通処理の生成
	m_commonProcess = std::make_unique<MenuFlowCommonProcess>(this);

	//		選択タイプオブザーバーの生成
	m_selectTypeObserver = std::make_unique<MenuSelectTypeObserver>();

	//		メニューUIタイトルオブザーバーの生成
	m_titleUIObserver = std::make_unique<MenuTitleUIObserver>();

	//		メニューアイコンUIオブザーバーの生成
	m_menuIconUIObserver = std::make_unique<MenuIconUIObserver>();
}

MenuFlow::~MenuFlow()
{
}

void MenuFlow::Initialize()
{
	m_firstProcess = true;
	m_menuEndJudgemnet = false;
	m_mousePositionX = 0;
	m_mousePositoinY = 0;
	m_uiSubType = UISubType::Non;
	m_flag = KeyProcessFlag::None;
	m_type = MenuType::Standby;
	//		初期の状態
	m_state = m_menuStateInformation[m_type].get();
}

void MenuFlow::Update()
{
	m_state->Update();

	m_flag = KeyProcessFlag::None;
}

void MenuFlow::Finalize()
{
	m_menuEndJudgemnet = false;

	m_meneStartJudgement = false;

	m_flag = 0;
}

void MenuFlow::CreateState()
{
	//		状態の生成
	m_menuStateInformation.insert({ MenuType::Start, std::make_unique<MenuStart>(this) });
	m_menuStateInformation.insert({ MenuType::Audio, std::make_unique<AudioSetting>(this) });
	m_menuStateInformation.insert({ MenuType::Option, std::make_unique<OptionSetting>(this) });
	m_menuStateInformation.insert({ MenuType::GamePlay, std::make_unique<EndSetting>(this) });
	m_menuStateInformation.insert({ MenuType::Close, std::make_unique<MenuClose>(this) });
	m_menuStateInformation.insert({ MenuType::Standby, std::make_unique<MenuStandby>(this) });
}

void MenuFlow::MousePositionX(int x)
{
	m_mousePositionX = x;
}

void MenuFlow::MousePositionY(int y)
{
	m_mousePositoinY = y;
}

void MenuFlow::IsKeyPressed(KeyInputMouse::MouseList key)
{
	if (key == KeyInputMouse::MouseList::TabAudio)				TrueFlag(KeyProcessFlag::TabAudio);
	else if (key == KeyInputMouse::MouseList::TabGamePlay)		TrueFlag(KeyProcessFlag::TabGamePlay);
	else if (key == KeyInputMouse::MouseList::TabOption)		TrueFlag(KeyProcessFlag::TabOption);
	else if (key == KeyInputMouse::MouseList::ExitButton)		TrueFlag(KeyProcessFlag::ButtonExit);
	else if (key == KeyInputMouse::MouseList::MenuCloseButton)	TrueFlag(KeyProcessFlag::ButtonMenuClose);
}

void MenuFlow::IsKeyReleased(KeyInputMouse::MouseList key)
{
}

void MenuFlow::IsKeepPushing(KeyInputMouse::MouseList key)
{
}

void MenuFlow::IsKeyPressed(KeyboardList::KeyboardList key)
{
	//		メニューを開くかどうか
	if (key == KeyboardList::KeyboardList::MenuOpen &&
		m_type == MenuType::Standby)
	{
		//		メニューを開始する
		m_menuOpenKeyJudgement = true;
	}

	//		メニューを閉じるかどうか
	if (key == KeyboardList::KeyboardList::MenuOpen)
	{
		if (m_type == MenuType::Audio ||
			m_type == MenuType::Option ||
			m_type == MenuType::GamePlay)
		{
			//		メニューを開始する
			TrueFlag(KeyProcessFlag::K_MenuClose);
			m_firstProcess = true;
		}
	}
}

void MenuFlow::IsKeyReleased(KeyboardList::KeyboardList key)
{
}

void MenuFlow::IsKeyState(KeyboardList::KeyboardList key)
{
}

void MenuFlow::HitUIType(UISubType type)
{
	m_uiSubType = type;
}

bool MenuFlow::ButtonHitJudgement(UISubType type)
{
	if (m_uiSubType == type)
	{
		if (type == UISubType::GameExitButton)
		{
			if (FlagJudgement(KeyProcessFlag::ButtonExit))
			{
				return true;
			}
		}
		else if (type == UISubType::CloseMenuButton)
		{
			if (FlagJudgement(KeyProcessFlag::ButtonMenuClose))
			{
				return true;
			}
		}
	}

	return false;
}

bool MenuFlow::FlagJudgement(KeyProcessFlag flag)
{
	//		両方のビットが１の場合
	if (m_flag & flag) return true;

	return false;
}

void MenuFlow::TrueFlag(KeyProcessFlag flag)
{
	m_flag |= flag;
}

void MenuFlow::FalseFlag(KeyProcessFlag flag)
{
	//		フラグがオンの時はオフにする
	m_flag &= ~flag;
}

bool MenuFlow::TabProcess(MenuType type)
{
	//		UIの範囲にあり現在の状態と同じではなく押された場合に処理

	//		Audio
	if (m_uiSubType == UISubType::TabAudio &&
		FlagJudgement(KeyProcessFlag::TabAudio) &&
		type != MenuType::Audio)
	{
		NextScene(Audio);

		MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

		return true;
	}
	//		GamePlay
	else if (m_uiSubType == UISubType::TabGamePlay &&
		FlagJudgement(KeyProcessFlag::TabGamePlay) &&
		type != MenuType::GamePlay)
	{
		NextScene(GamePlay);

		MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

		return true;
	}
	//		Option
	else if (m_uiSubType == UISubType::TabOption &&
		FlagJudgement(KeyProcessFlag::TabOption) &&
		type != MenuType::Option)
	{
		NextScene(Option);

		return true;
	}

	return false;
}

void MenuFlow::NextScene(MenuType type)
{
	SetNextType(type);

	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);
}

void MenuFlow::ChangState(MenuType type)
{
	//		同じタイプの場合処理をしない
	if (m_type == type) return;

	//		終了処理
	m_state->Finalize();

	//		タイプの更新
	m_type = type;
	m_nextType = type;

	//		状態の更新
	m_state = m_menuStateInformation[type].get();

	//		初期化処理
	m_state->Initialize();
}