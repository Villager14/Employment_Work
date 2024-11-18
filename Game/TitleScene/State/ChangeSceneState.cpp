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
	m_titleSelectManager(titleSelectManager)
{
}

ChangeSceneState::~ChangeSceneState()
{
}

void ChangeSceneState::Initialize()
{
	//		���j���[���g����悤�ɂ���
	m_titleSelectManager->GetInformation()->SetMenuUseJudgement(false);

	//		���ʉ�
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);

	//		�t�F�[�h�A�E�g�̏���
	m_titleSelectManager->GetPostEffectManager()->GetInformation()->
		TrueFlag(PostEffectInformation::Flag::SceneEndFade);
}

void ChangeSceneState::Update()
{
	if (m_titleSelectManager->GetPostEffectManager()->GetInformation()->FlagJudgement(PostEffectInformation::Flag::SceneEnd))
	{
		//		�v���C�V�[���ɐ؂�ւ���
		m_titleSelectManager->GetInformation()->SetChangeSceneJudgement(true);
	}
}

void ChangeSceneState::Render()
{	
}

void ChangeSceneState::Finalize()
{
	m_titleSelectManager->GetInformation()->SetKeyInput(false);
}
