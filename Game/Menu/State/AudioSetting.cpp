/*
* @file		AudioSetting.cpp
* @brief	���̐ݒ�
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

	//		Audio�̕`��
	(*m_menuManager->GetUIRender())[m_menuManager->AudioSelect]->Render();

	//		Opetion�̕`��
	(*m_menuManager->GetUIRender())[m_menuManager->OptionSelect]->Render();

	//		GamePlay�̕`��
	(*m_menuManager->GetUIRender())[m_menuManager->GamePlaySelect]->Render();

	//		Audio�̃^�C�g���`��
	(*m_menuManager->GetUIRender())[m_menuManager->AudioTitle]->Render();


	//		�X���C�_�[�̕`��
	m_menuManager->SliderRender({ 200.0f, -130.0f });
}

void AudioSetting::Finalize()
{
}
