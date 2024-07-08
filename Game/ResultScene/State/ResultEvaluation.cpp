/*
* @file		ResultEvaluation.cpp
* @brief	���U���g�]������
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "ResultEvaluation.h"

ResultEvaluation::ResultEvaluation(ResultManager* resultManager)
	:
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultEvaluation::~ResultEvaluation()
{
}

void ResultEvaluation::Initialize()
{
}

void ResultEvaluation::Update()
{
	//		�o�ߎ���
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	float size = 0.0f;

	if (m_time < 0.5f)
	{
		size = 4.0f * m_time * m_time * m_time;
	}
	else
	{
		size = 1.0f - pow(-2.0f * m_time + 2.0f, 3.0f) / 2.0f;
	}

	//		�]��
	(*m_resultManager->GetStandardShader()->GetUIInformation())[ResultManager::EvaluationUI].scale = { 1, size };


	if (m_time >= 1.0f)
	{
		//		��Ԃ�؂�ւ���(�ҋ@���)
		m_resultManager->ChangeState(ResultManager::State::Stay);
	}

	//	�A�j���[�V�����̃X�L�b�v
	m_resultManager->AnimationSkip();
}

void ResultEvaluation::Render()
{
	//		�]��
	m_resultManager->GetStandardShader()->Render(ResultManager::EvaluationUI);

	//		�����̕`��
	m_resultManager->GetRiseNumberShader()->Render(4.0f);
}

void ResultEvaluation::Finalize()
{
}
