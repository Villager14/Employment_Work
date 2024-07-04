/*
* @file		AudioSetting.cpp
* @brief	‰¹‚ÌÝ’è
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

	//		Audio‚Ì•`‰æ
	(*m_menuManager->GetUIRender())[m_menuManager->AudioSelect]->Render();

	//		Opetion‚Ì•`‰æ
	(*m_menuManager->GetUIRender())[m_menuManager->OptionSelect]->Render();

	//		GamePlay‚Ì•`‰æ
	(*m_menuManager->GetUIRender())[m_menuManager->GamePlaySelect]->Render();

	//		Audio‚Ìƒ^ƒCƒgƒ‹•`‰æ
	(*m_menuManager->GetUIRender())[m_menuManager->AudioTitle]->Render();


	//		ƒXƒ‰ƒCƒ_[‚Ì•`‰æ
	m_menuManager->SliderRender({ 200.0f, -130.0f });
}

void AudioSetting::Finalize()
{
}
