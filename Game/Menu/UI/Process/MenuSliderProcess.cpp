/*
* @file		MenuSliderProcess.cpp
* @brief	���j���[�̃X���C�_�[�̏���
* @author	Morita
* @date		2024/12/25
*/

#include "pch.h"

#include "MenuSliderProcess.h"

MenuSliderProcess::MenuSliderProcess(Slider* slider, AboveUI* aboveUI)
	:
	m_mousePositionX(0),
	m_slider(slider),
	m_aboveUI(aboveUI),
	m_mouseInputJudgement(false),
	m_sliderType(Slider::UIType::Empty),
	m_hitType(AboveUI::Empty)
{
	//		�X���C�_�[�̐ݒ�I�u�U�[�o�[�̐���
	m_settingObserver = std::make_unique<SetSliderSettingValObserver>();
}

MenuSliderProcess::~MenuSliderProcess()
{
}

void MenuSliderProcess::Initilaize()
{
	m_hitType = AboveUI::MouseKnob;
	SliderRatio();
	OptionUpdate();
	m_hitType = AboveUI::FOVKnob;
	SliderRatio();
	OptionUpdate();
	m_hitType = AboveUI::Empty;
}

void MenuSliderProcess::Update()
{
	//		�������Ă��Ȃ��ꍇ���������Ȃ�
	if (m_hitType == AboveUI::Empty || !m_mouseInputJudgement)
	{
		//		�������Ă��Ȃ���Ԃɂ���
		m_hitType = AboveUI::Empty;
		m_sliderType = Slider::UIType::Empty;

		//		���͂��Ă��Ȃ����
		m_mouseInputJudgement = false;

		return;
	}

	SliserInformationUpdate();

	AudioUpdate();

	OptionUpdate();

	//		���͂��Ă��Ȃ����
	m_mouseInputJudgement = false;
}

void MenuSliderProcess::HitBunnton(UISubType type)
{
	if (type == UISubType::MastarVolumKnob)
	{
		m_hitType = AboveUI::MasterKnob;
		m_sliderType = Slider::MastarVolum;
	}
	else if (type == UISubType::BGMKnob)
	{
		m_hitType = AboveUI::BGMKnob;
		m_sliderType = Slider::BGMVolum;
	}
	else if (type == UISubType::SoundEffectKnob)
	{
		m_hitType = AboveUI::SoundEffectKnob;
		m_sliderType = Slider::SoundEffect;
	}
	else if (type == UISubType::FovKnob)
	{
		m_hitType = AboveUI::FOVKnob;
		m_sliderType = Slider::FOV;
	}
	else if (type == UISubType::MouseSpeedKnob)
	{
		m_hitType = AboveUI::MouseKnob;
		m_sliderType = Slider::Mouse;
	}
}

void MenuSliderProcess::SliserInformationUpdate()
{
	(*m_aboveUI->GetInformation())[m_hitType].position.x = static_cast<float>
		(m_mousePositionX)-640.0f;

	(*m_aboveUI->GetInformation())[m_hitType].position.x = Library::Clamp
	((*m_aboveUI->GetInformation())[m_hitType].position.x,
		-81.0f, 480.0f);

	//		�X���C�_�[�̍X�V
	(*m_slider->GetInformation())[m_sliderType].slideVal =
		((*m_aboveUI->GetInformation())[m_hitType].position.x
			+ SLIDER_MIN_VAL) / SLIDER_MAX_VAL;
}

float MenuSliderProcess::SliderRatio()
{
	//		�X���C�_�[�m�u�̍X�V���m�u�̊���
	return ((*m_aboveUI->GetInformation())[m_hitType].position.x + KNOB_MIN_VAL) / KNOB_MAX_VAL;
}

void MenuSliderProcess::AudioUpdate()
{
	if (m_hitType == AboveUI::MasterKnob)
	{
		//		�}�X�^�[�{�����[���̉��ʂ�ݒ肷�� & �}�X�^�[�{�����[���̃X���C�_�[�̍X�V
		MusicLibrary::GetInstance()->SetMastaraVolume(SliderRatio());
	}
	else if (m_hitType == AboveUI::SoundEffectKnob)
	{
		//		���ʉ��̉��ʂ�ݒ肷�� & ���ʉ��̃X���C�_�[�̍X�V
		MusicLibrary::GetInstance()->SetSoundEffectVolume(SliderRatio());
	}
	else if (m_hitType == AboveUI::BGMKnob)
	{
		//		BGM�̉��ʂ�ݒ肷�� & BGM�̃X���C�_�[�̍X�V
		MusicLibrary::GetInstance()->SetBGMVolume(SliderRatio());
	}
}

void MenuSliderProcess::OptionUpdate()
{
	if (m_hitType == AboveUI::FOVKnob)
	{
		m_settingObserver->SetFov(SliderRatio());
	}
	else if (m_hitType == AboveUI::MouseKnob)
	{
		m_settingObserver->SetMouseSensitivity(SliderRatio());
	}
}
