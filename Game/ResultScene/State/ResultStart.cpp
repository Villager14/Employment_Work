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
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultStart::~ResultStart()
{
}

void ResultStart::Initialize()
{
}

void ResultStart::Update()
{
	//		�o�ߎ���
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_time >= 1.0f)
	{
		//		��Ԃ�؂�ւ���(�����ړ����)
		m_resultManager->ChangeState(m_resultManager->GetNumberMove());
	}
}

void ResultStart::Render()
{
	//		UI�w�i�̕`��
	//m_resultManager->UIViewProcess(0);

	//		�t�F�[�h
	m_resultManager->FadeViewProcess(m_time);
}

void ResultStart::Finalize()
{
}
