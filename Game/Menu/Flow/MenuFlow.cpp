/*
* @file		MenuFlow.cpp
* @brief	���j���[�̗���
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

	//		���j���[�̔w�iUI�I�u�U�[�o�[�̐���
	m_menuBackGroundUIObserver = std::make_unique<MenuBackGroundUIObserver>();

	//		���j���[TabUI�I�u�U�[�o�[�̐���
	m_menuTabUIObserver = std::make_unique<MenuTabUIObserver>();

	//		���j���[���ʏ����̐���
	m_commonProcess = std::make_unique<MenuFlowCommonProcess>(this);

	//		�I���^�C�v�I�u�U�[�o�[�̐���
	m_selectTypeObserver = std::make_unique<MenuSelectTypeObserver>();

	//		���j���[UI�^�C�g���I�u�U�[�o�[�̐���
	m_titleUIObserver = std::make_unique<MenuTitleUIObserver>();

	//		���j���[�A�C�R��UI�I�u�U�[�o�[�̐���
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
	//		�����̏��
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
	//		��Ԃ̐���
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
	//		���j���[���J�����ǂ���
	if (key == KeyboardList::KeyboardList::MenuOpen &&
		m_type == MenuType::Standby)
	{
		//		���j���[���J�n����
		m_menuOpenKeyJudgement = true;
	}

	//		���j���[����邩�ǂ���
	if (key == KeyboardList::KeyboardList::MenuOpen)
	{
		if (m_type == MenuType::Audio ||
			m_type == MenuType::Option ||
			m_type == MenuType::GamePlay)
		{
			//		���j���[���J�n����
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
	//		�����̃r�b�g���P�̏ꍇ
	if (m_flag & flag) return true;

	return false;
}

void MenuFlow::TrueFlag(KeyProcessFlag flag)
{
	m_flag |= flag;
}

void MenuFlow::FalseFlag(KeyProcessFlag flag)
{
	//		�t���O���I���̎��̓I�t�ɂ���
	m_flag &= ~flag;
}

bool MenuFlow::TabProcess(MenuType type)
{
	//		UI�͈̔͂ɂ��茻�݂̏�ԂƓ����ł͂Ȃ������ꂽ�ꍇ�ɏ���

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
	//		�����^�C�v�̏ꍇ���������Ȃ�
	if (m_type == type) return;

	//		�I������
	m_state->Finalize();

	//		�^�C�v�̍X�V
	m_type = type;
	m_nextType = type;

	//		��Ԃ̍X�V
	m_state = m_menuStateInformation[type].get();

	//		����������
	m_state->Initialize();
}