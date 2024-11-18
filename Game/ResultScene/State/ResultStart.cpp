/*
* @file		ResultStart.cpp
* @brief	���U���g�J�n����
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultStart.h"

ResultStart::ResultStart(ResultManager* resultManager)
	:
	m_resultManager(resultManager)
{
}

ResultStart::~ResultStart()
{
}

void ResultStart::Initialize()
{
	//		�^�C�g����BGM�̍Đ�
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		���j���[���g���Ȃ��悤�ɂ���
	m_resultManager->SetMenuUseJugement(false);
}

void ResultStart::Update()
{
	if (m_resultManager->GetPostEffectManager()->GetInformation()->
		FlagJudgement(PostEffectInformation::Flag::FadeInEnd))
	{
		//		��Ԃ�؂�ւ���(�����ړ����)
		m_resultManager->ChangeState(ResultManager::State::NumberMove);
	}
}

void ResultStart::Render()
{
}

void ResultStart::Finalize()
{
	//		���j���[���g����悤�ɂ���
	m_resultManager->SetMenuUseJugement(true);
}
