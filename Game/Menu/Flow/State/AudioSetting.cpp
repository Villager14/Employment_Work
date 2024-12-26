/*
* @file		AudioSetting.cpp
* @brief	���̐ݒ�
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "AudioSetting.h"

#include "../MenuFlowCommonProcess.h"

#include "../../UI/MenuUITabEnums.h"

AudioSetting::AudioSetting(MenuFlow* menuFlow)
	:
	m_menuFlow(menuFlow),
	m_transitionTitleTime(1.0f),
	m_transitionSettingUITime(1.0f),
	m_startJudgement(false),
	m_endJudgement(false),
	m_transitionRoughTime(1.0f),
	m_menuCloseJudgement(false)
{
}

AudioSetting::~AudioSetting()
{
}

void AudioSetting::Initialize()
{
	//		�I�[�f�B�I��I������
	m_menuFlow->GetSelectTypeObserver()->SelectType(MenuUITaype::Audio);

	if (m_menuFlow->GetFirstProcess())
	{
		m_transitionTitleTime = 1.0f;
		m_transitionSettingUITime = 1.0f;
		m_startJudgement = false;
		m_endJudgement = false;
		m_transitionRoughTime = 1.0f;
		m_menuFlow->SetFirestProcess(false);
		m_menuCloseJudgement = false;
	}
	else
	{
		m_transitionTitleTime = 0.0f;
		m_transitionSettingUITime = 0.0f;
		m_startJudgement = true;
		m_endJudgement = false;
		m_transitionRoughTime = 1.0f;
		m_menuCloseJudgement = false;
	}
}

void AudioSetting::Update()
{
	//		���j���[�̑J�ڏ���
	if (m_menuFlow->GetMenuFlowCommonProcess()->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, m_endJudgement, m_menuCloseJudgement))
	{
		//		�^�C�g���I�u�W�F�N�g�̈ړ�����
		m_menuFlow->GetTitleUIUObserver()->TitleMoveProcess(m_transitionSettingUITime);

		//		Tab�I�u�W�F�N�g�̈ړ�����
		m_menuFlow->GetMenuTabUIObserver()->TabMove(m_transitionRoughTime);

		return;
	}

	//		TabUI��I��������
	if (m_menuFlow->TabProcess(MenuFlow::Audio))
	{
		m_endJudgement = true;
	}

	//		���j���[����邩�ǂ���
	if (m_menuFlow->FlagJudgement(MenuFlow::K_MenuClose))
	{
		//		���j���[������Ԃɂ���
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}

	//		�V�[����؂�ւ��邩
	//if (m_menuFlow->ChangeStateJudgement())
	//{
	//	m_endJudgement = true;
	//}

	/*
	//		ESC�Ń��j���[���Ƃ��鏈��
	if (m_menuManager->GetCommonProcess()->MenuEscCloseProcess())
	{
		//		���j���[������Ԃɂ���
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}
	
	//		��܂��ȃ��j���[�{�^���̏���
	if (m_menuManager->GetCommonProcess()->ButtonCollider(MenuInformation::MenuType::Audio))
	{
		m_endJudgement = true;
	}

	//		�X���C�_�[�̍X�V����
	SliderUpdate();
	*/
}

void AudioSetting::Render()
{
	/*
	m_menuManager->MenuBackRneder();

	//		��܂��ȃ��j���[�̕`��
	m_menuManager->RoughMenuViwe(m_menuManager->EasingIcon(m_transitionRoughTime));
	
	//		���j���[�I�𒆂̕`��
	if (!m_menuCloseJudgement) m_menuManager->MenuSelectView();

	//		Audio�̃^�C�g���`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::AudioTitle,
		m_menuManager->EasingIcon(m_transitionTitleTime));

	//		�X���C�_�[�̕`��
	SliderView(m_menuManager->EasingIcon(m_transitionSettingUITime));

	//		�}�E�X�|�C���^�̕`��
	m_menuManager->GetCommonProcess()->MousePointa();
	*/
}

void AudioSetting::Finalize()
{
}

void AudioSetting::SliderView(float transitionTime)
{
	/*
	//		�}�X�^�[�{�����[���̕`��
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = MASTER_SLIDER_POSITION;
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MastarVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::MastarVolum, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MasterKnob, transitionTime);

	//		BGM�{�����[���̕`��
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = BGM_SLIDER_POSITION;
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::BGMVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::BGMVolum, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::BGMKnob, transitionTime);

	//		���ʉ��̕`��
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = SOUND_EFFECT_SLIDER_POSITION;
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SoundEffectVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::SoundEffect, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SoundEffectKnob, transitionTime);
	*/
}

void AudioSetting::SliderUpdate()
{
	/*
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::MasterKnob);
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::BGMKnob);
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::SoundEffectKnob);

	//		�}�X�^�[�{�����[���̉��ʂ�ݒ肷�� & �}�X�^�[�{�����[���̃X���C�_�[�̍X�V
	MusicLibrary::GetInstance()->SetMastaraVolume(m_menuManager->GetCommonProcess()->
				SliderVal(AboveUI::UIType::MasterKnob, Slider::UIType::MastarVolum));	

	//		BGM�̉��ʂ�ݒ肷�� & BGM�̃X���C�_�[�̍X�V
	MusicLibrary::GetInstance()->SetBGMVolume(m_menuManager->GetCommonProcess()->
				SliderVal(AboveUI::UIType::BGMKnob, Slider::UIType::BGMVolum));

	//		���ʉ��̉��ʂ�ݒ肷�� & ���ʉ��̃X���C�_�[�̍X�V
	MusicLibrary::GetInstance()->SetSoundEffectVolume(m_menuManager->GetCommonProcess()->
		SliderVal(AboveUI::UIType::SoundEffectKnob, Slider::UIType::SoundEffect));
		*/
}
