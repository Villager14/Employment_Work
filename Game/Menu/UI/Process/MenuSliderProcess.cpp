/*
* @file		MenuSliderProcess.cpp
* @brief	メニューのスライダーの処理
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
	//		スライダーの設定オブザーバーの生成
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
	//		当たっていない場合処理をしない
	if (m_hitType == AboveUI::Empty || !m_mouseInputJudgement)
	{
		//		当たっていない状態にする
		m_hitType = AboveUI::Empty;
		m_sliderType = Slider::UIType::Empty;

		//		入力していない状態
		m_mouseInputJudgement = false;

		return;
	}

	SliserInformationUpdate();

	AudioUpdate();

	OptionUpdate();

	//		入力していない状態
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

	//		スライダーの更新
	(*m_slider->GetInformation())[m_sliderType].slideVal =
		((*m_aboveUI->GetInformation())[m_hitType].position.x
			+ SLIDER_MIN_VAL) / SLIDER_MAX_VAL;
}

float MenuSliderProcess::SliderRatio()
{
	//		スライダーノブの更新＆ノブの割合
	return ((*m_aboveUI->GetInformation())[m_hitType].position.x + KNOB_MIN_VAL) / KNOB_MAX_VAL;
}

void MenuSliderProcess::AudioUpdate()
{
	if (m_hitType == AboveUI::MasterKnob)
	{
		//		マスターボリュームの音量を設定する & マスターボリュームのスライダーの更新
		MusicLibrary::GetInstance()->SetMastaraVolume(SliderRatio());
	}
	else if (m_hitType == AboveUI::SoundEffectKnob)
	{
		//		効果音の音量を設定する & 効果音のスライダーの更新
		MusicLibrary::GetInstance()->SetSoundEffectVolume(SliderRatio());
	}
	else if (m_hitType == AboveUI::BGMKnob)
	{
		//		BGMの音量を設定する & BGMのスライダーの更新
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
