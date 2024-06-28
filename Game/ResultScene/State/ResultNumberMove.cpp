/*
* @file		ResultNumberMove.cpp
* @brief	���U���g�����ړ�����
* @author	Morita
* @date		2024/05/29
*/

#include "pch.h"

#include "ResultNumberMove.h"

ResultNumberMove::ResultNumberMove(ResultManager* resultManager)
	:
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultNumberMove::~ResultNumberMove()
{
}

void ResultNumberMove::Initialize()
{

}

void ResultNumberMove::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_time = Library::Clamp(m_time, 0.0f, 4.0f);

	if (m_time >= 4.0f)
	{
		//		��Ԃ�؂�ւ���(�]�����)
		m_resultManager->ChangeState(m_resultManager->GetEvaluation());
	}

	//	�A�j���[�V�����̃X�L�b�v
	m_resultManager->AnimationSkip();
}

void ResultNumberMove::Render()
{
	//		UI�w�i�̕`��
	//m_resultManager->UIViewProcess(0);

	m_resultManager->NumberRender(m_time);
}

void ResultNumberMove::Finalize()
{
}
