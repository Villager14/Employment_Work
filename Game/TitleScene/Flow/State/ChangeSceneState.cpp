/*
* @file		ChangeSceneState.cpp
* @brief	�V�[���؂�ւ����������
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "ChangeSceneState.h"

ChangeSceneState::ChangeSceneState(TitleFlowManager* titleFlowManager)
	:
	m_titleFlow(titleFlowManager)
{
}

ChangeSceneState::~ChangeSceneState()
{
}

void ChangeSceneState::Initialize()
{
	//		���j���[���g�p�ł��Ȃ��悤�ɂ���
	m_titleFlow->MenuDisableMenu();

	//		���ʉ�
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);
}

void ChangeSceneState::Update()
{
	//		�t�F�[�h�A�E�g���J�n����
	m_titleFlow->GetFadeObserver()->SceneEndFadeOut();
}

void ChangeSceneState::Finalize()
{
	//m_titleSelectManager->GetInformation()->SetKeyInput(false);
}
