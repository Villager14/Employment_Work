/*
* @file		MenuUI.cpp
* @brief	���j���[��UI
* @author	Morita
* @date		2024/12/18
*/

#include "pch.h"

#include "MenuUI.h"

MenuUI::MenuUI()
{
	//		�����蔻������܂Ƃ߂�
	m_summarizeColliderInformation = std::make_unique<MenuSummarizeColliderInformation>();

	//		�㏸UI�̐���
	m_aboveUI = std::make_unique<AboveUI>();

	//		�X���C�_�[�̐���
	m_slider = std::make_unique<Slider>();

	//		���j���[TabUI�̐���
	m_menuTabUI = std::make_unique<MenuTabUI>(m_aboveUI.get(), m_summarizeColliderInformation.get());

	//		���j���[�̔w�iUI�̐���
	m_menuBackGround = std::make_unique<MenuBackGround>();

	//		�}�E�XUI�̐���
	m_mousePointer = std::make_unique<MenuMousePointerUI>();

	//		�^�C�g��UI�̐���
	m_titleUI = std::make_unique<MenuTitle>(m_aboveUI.get());

	//		�X���C�_�[�̏���
	m_sliderProcess = std::make_unique<MenuSliderProcess>(m_slider.get(), m_aboveUI.get());

	//		�I�[�f�B�IUI�̐���
	m_menuAudio = std::make_unique<MenuAudioUI>(m_aboveUI.get(), m_slider.get(), m_summarizeColliderInformation.get());

	//		�Q�[���v���CUI�̐���
	m_gamePlay = std::make_unique<MenuGamePlayUI>(m_aboveUI.get(), m_summarizeColliderInformation.get());

	//		�I�v�V����UI�̐���
	m_menuOption = std::make_unique<MenuOption>(m_aboveUI.get(), m_slider.get(), m_summarizeColliderInformation.get());
}

MenuUI::~MenuUI()
{
}

void MenuUI::Initialize()
{
	//		�㏸���j���[�̏���������
	m_aboveUI->Initialize();

	//		�X���C�_�[�̏���������
	m_slider->Initialize();

	//		���j���[�^�u����������
	m_menuTabUI->Initialize();

	//		���j���[�̔w�iUI�̏�����
	m_menuBackGround->Initialize();

	//		�}�E�X�|�C���^UI�̏�����
	m_mousePointer->Initialize();

	//		�^�C�g��UI�̏�����
	m_titleUI->Initialize();

	//		�I�[�f�B�IUI�̏���������
	m_menuAudio->Initialize();

	//		�I�v�V����UI�̏���������
	m_menuOption->Initialize();

	//		�Q�[���v���CUI�̏���������
	m_gamePlay->Initialize();

	//		�X���C�_�[�̏����̏�����
	m_sliderProcess->Initilaize();
}

void MenuUI::Update()
{
	//		���j���[Tab�̍X�V
	m_menuTabUI->Update();

	//		�I�[�f�B�I�̍X�V����
	m_menuAudio->Update();

	//		�I�v�V����UI�̍X�V����
	m_menuOption->Update();

	//		�Q�[���v���C�̍X�V����
	m_gamePlay->Update();

	//		�X���C�_�[�̏���
	m_sliderProcess->Update();
}

void MenuUI::Render()
{
	//		���j���[�̔w�iUI�̕`��
	m_menuBackGround->Render();

	//		���j���[Tab�̕`��
	m_menuTabUI->Render();

	//		�^�C�g���̕`��
	m_titleUI->Render();

	//		�I�[�f�B�I��UI�̕`��
	m_menuAudio->Render();

	//		�I�v�V������UI�̕`�揈��
	m_menuOption->Render();

	//		�Q�[���v���CUI�̕`��
	m_gamePlay->Render();

	//		�}�E�X�|�C���^UI�̕`��
	m_mousePointer->Render();
}

void MenuUI::Finalize()
{
	//		���j���[Tab�̏I������
	m_menuTabUI->Finalize();

	//		���j���[�̔w�iUI�̏I������
	m_menuBackGround->Finalize();

	//		�}�E�X�|�C���^UI�̏I������
	m_mousePointer->Finalize();

	//		�^�C�g���̏I������
	m_titleUI->Finalize();
}

void MenuUI::BackGroundBarScale(float scale)
{
	//		���j���[�̔w�i�̃o�[�̃X�P�[����ݒ肷��
	m_menuBackGround->BarScale(scale);
}

void MenuUI::MenuMoveProcess(float move)
{
	//		���j���[�̈ړ������̈ړ��ʂ�ݒ肷��
	m_menuBackGround->MenuMoveProcess(move);
}

void MenuUI::TabMove(float move)
{
	//		TabUI�̈ړ��ʂ�ݒ肷��
	m_menuTabUI->TabMove(move);
}

void MenuUI::TabUseJudgement(float judgement)
{
	m_menuTabUI->TabUserJudgement(judgement);
}

void MenuUI::MousePositionX(int x)
{
	//		�}�E�X��X���W��ݒ肷��
	m_mousePointer->SetMousePositionX(x);

	//		�X���C�_�[�̍��WX
	m_sliderProcess->SetMousePosition(x);
}

void MenuUI::MousePositionY(int y)
{
	//		�}�E�X��Y���W��ݒ肷��
	m_mousePointer->SetMousePositionY(y);
}

void MenuUI::SelectType(MenuUITaype::UIType type)
{
	//		�^�C�g���̃^�C�v��ݒ肷��
	m_titleUI->SetTitleType(type);

	//		�Q�[���^�C�v��ݒ肷��
	m_menuAudio->SetType(type);

	//		�Q�[���^�C�v��ݒ肷��
	m_menuOption->SetType(type);

	//		�Q�[���^�C�v��ݒ肷��
	m_gamePlay->SetType(type);
}

void MenuUI::TitleMoveProcess(float move)
{
	//		�^�C�g���̈ړ��ʂ�ݒ肷��
	m_titleUI->TitleMoveProcess(move);

	//		�^�C�g���̈ړ���
	m_menuAudio->TitleMoveProcess(move);

	//		�^�C�g���̈ړ���
	m_menuOption->TitleMoveProcess(move);

	//		�^�C�g���̈ړ���
	m_gamePlay->TitleMoveProcess(move);
}

void MenuUI::IconMoveProcess(float move)
{
	//		�X���C�_�[�̈ړ��ʂ�ݒ肷��
	m_menuAudio->ButtonMoveProcess(move);

	//		�X���C�_�[�̈ړ��ʂ�ݒ肷��
	m_menuOption->ButtonMoveProcess(move);

	//		�X���C�_�[�̈ړ��ʂ�ݒ肷��
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
		//		Tab�̃^�C�v��ݒ肷��
		m_menuTabUI->SetTabType(MenuUITaype::UIType::Audio);
	}
	else if (type == UISubType::TabGamePlay)
	{
		//		Tab�̃^�C�v��ݒ肷��
		m_menuTabUI->SetTabType(MenuUITaype::UIType::GamePlay);
	}
	else if (type == UISubType::TabOption)
	{
		//		Tab�̃^�C�v��ݒ肷��
		m_menuTabUI->SetTabType(MenuUITaype::UIType::Option);
	}
	//		�Q�[���v���C
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
