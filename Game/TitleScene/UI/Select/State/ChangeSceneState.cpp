/*
* @file		ChangeSceneState.cpp
* @brief	�V�[���؂�ւ����������
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "ChangeSceneState.h"

ChangeSceneState::ChangeSceneState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(1.0f)
{
}

ChangeSceneState::~ChangeSceneState()
{
}

void ChangeSceneState::Initialize()
{
	m_time = 1.0f;

	//		���ʉ�
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);
}

void ChangeSceneState::Update()
{
	m_time -= LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�Q�[���I�����̉��ʂ̃{�����[������
	MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

	if (m_time <= 0.0f)
	{
		//		�v���C�V�[���ɐ؂�ւ���
		m_titleSelectManager->SetChangeSceneJudgement(true);
	}
}

void ChangeSceneState::Render()
{
	m_titleSelectManager->FadeViewProcess(m_time);
}

void ChangeSceneState::Finalize()
{
	m_titleSelectManager->SetKeyInput(false);
	m_time = 0.0f;
}
