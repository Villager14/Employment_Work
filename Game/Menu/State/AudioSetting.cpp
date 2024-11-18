/*
* @file		AudioSetting.cpp
* @brief	音の設定
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "AudioSetting.h"

AudioSetting::AudioSetting(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
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
	if (m_menuManager->GetFirstAudioMenuJudgement())
	{
		m_transitionTitleTime = 1.0f;
		m_transitionSettingUITime = 1.0f;
		m_startJudgement = false;
		m_endJudgement = false;
		m_menuManager->SetFirstAudioMenuJudgement(false);
	}
}

void AudioSetting::Update()
{
	//		メニューの遷移処理
	if (m_menuManager->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, m_endJudgement, m_menuCloseJudgement)) return;

	//		ESCでメニューをとじる処理
	if (m_menuManager->GetCommonProcess()->MenuEscCloseProcess())
	{
		//		メニューを閉じる状態にする
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}

	//		大まかなメニューボタンの処理
	if (m_menuManager->GetCommonProcess()->ButtonCollider(MenuInformation::MenuType::Audio))
	{
		m_endJudgement = true;
	}

	//		スライダーの更新処理
	SliderUpdate();
}

void AudioSetting::Render()
{
	m_menuManager->MenuBackRneder();

	//		大まかなメニューの描画
	m_menuManager->RoughMenuViwe(m_menuManager->EasingIcon(m_transitionRoughTime));
	
	//		メニュー選択中の描画
	if (!m_menuCloseJudgement) m_menuManager->MenuSelectView();

	//		Audioのタイトル描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::AudioTitle,
		m_menuManager->EasingIcon(m_transitionTitleTime));

	//		スライダーの描画
	SliderView(m_menuManager->EasingIcon(m_transitionSettingUITime));

	//		マウスポインタの描画
	m_menuManager->GetCommonProcess()->MousePointa();
}

void AudioSetting::Finalize()
{
	m_transitionTitleTime = 0.0f;
	m_transitionSettingUITime = 0.0f;
	m_startJudgement = true;
	m_endJudgement = false;
	m_transitionRoughTime = 1.0f;
	m_menuCloseJudgement = false;
}

void AudioSetting::SliderView(float transitionTime)
{
	//		マスターボリュームの描画
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = MASTER_SLIDER_POSITION;
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MastarVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::MastarVolum, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MasterKnob, transitionTime);

	//		BGMボリュームの描画
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = BGM_SLIDER_POSITION;
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::BGMVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::BGMVolum, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::BGMKnob, transitionTime);

	//		効果音の描画
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = SOUND_EFFECT_SLIDER_POSITION;
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SoundEffectVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::SoundEffect, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SoundEffectKnob, transitionTime);
}

void AudioSetting::SliderUpdate()
{
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::MasterKnob);
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::BGMKnob);
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::SoundEffectKnob);

	//		マスターボリュームの音量を設定する & マスターボリュームのスライダーの更新
	MusicLibrary::GetInstance()->SetMastaraVolume(m_menuManager->GetCommonProcess()->
				SliderVal(AboveUI::UIType::MasterKnob, Slider::UIType::MastarVolum));	

	//		BGMの音量を設定する & BGMのスライダーの更新
	MusicLibrary::GetInstance()->SetBGMVolume(m_menuManager->GetCommonProcess()->
				SliderVal(AboveUI::UIType::BGMKnob, Slider::UIType::BGMVolum));

	//		効果音の音量を設定する & 効果音のスライダーの更新
	MusicLibrary::GetInstance()->SetSoundEffectVolume(m_menuManager->GetCommonProcess()->
		SliderVal(AboveUI::UIType::SoundEffectKnob, Slider::UIType::SoundEffect));
}
