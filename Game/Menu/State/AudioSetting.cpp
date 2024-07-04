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
	m_menuManager(menuManager)
{
}

AudioSetting::~AudioSetting()
{
}

void AudioSetting::Initialize()
{
}

void AudioSetting::Update()
{
}

void AudioSetting::Render()
{
	m_menuManager->MenuBackRneder();

	//		Audioの描画
	(*m_menuManager->GetUIRender())[m_menuManager->AudioSelect]->Render();

	//		Opetionの描画
	(*m_menuManager->GetUIRender())[m_menuManager->OptionSelect]->Render();

	//		GamePlayの描画
	(*m_menuManager->GetUIRender())[m_menuManager->GamePlaySelect]->Render();

	//		Audioのタイトル描画
	(*m_menuManager->GetUIRender())[m_menuManager->AudioTitle]->Render();


	//		スライダーの描画
	m_menuManager->SliderRender({ 200.0f, -130.0f });
}

void AudioSetting::Finalize()
{
}
