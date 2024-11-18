/*
* @file		ResultEnd.cpp
* @brief	���U���g�I������
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "ResultEnd.h"

ResultEnd::ResultEnd(ResultManager* resultManager)
	:
	m_resultManager(resultManager)
{
}

ResultEnd::~ResultEnd()
{
}

void ResultEnd::Initialize()
{
	//		���j���[���g���Ȃ��悤�ɂ���
	m_resultManager->SetMenuUseJugement(false);

	//		�t�F�[�h�A�E�g�̏���
	m_resultManager->GetPostEffectManager()->GetInformation()->
		TrueFlag(PostEffectInformation::Flag::SceneEndFade);
}

void ResultEnd::Update()
{
	if (m_resultManager->GetPostEffectManager()->GetInformation()->FlagJudgement(PostEffectInformation::Flag::SceneEnd))
	{
		//		�v���C�V�[���ɐ؂�ւ���
		m_resultManager->GetInformation()->SetChangeSceneJudgement(true);
	}
}

void ResultEnd::Render()
{
	//		�]��
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::EvaluationUI);

	//		�J�ڗU���摜
	m_resultManager->GetInformation()->GetStandardShader()->Render(ResultInformation::Button);

	//		�����̕`��
	m_resultManager->GetInformation()->GetRiseNumber()->Render(4.0f);
}

void ResultEnd::Finalize()
{
}
