/*
* @file		TitleUIObserver.cpp
* @brief	�^�C�g��UI�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitleUIObserver.h"

TitleUIObserver::TitleUIObserver()
{
}

TitleUIObserver::~TitleUIObserver()
{
}

void TitleUIObserver::AddObserver(ITitleUIObserver* observer)
{
	//		�I�u�U�[�o�[�̒ǉ�
	m_observer.push_back(observer);
}

void TitleUIObserver::DeleteObserver(ITitleUIObserver* observer)
{
	//		�I�u�U�[�o�[�̍폜
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void TitleUIObserver::DownSelect(float processingTime)
{
	//		���I������
	for (const auto& e : m_observer)
	{
		e->DownSelect(processingTime);
	}
}

void TitleUIObserver::UpSelect(float processingTime)
{
	//		��I������
	for (const auto& e : m_observer)
	{
		e->UpSelect(processingTime);
	}
}

void TitleUIObserver::Dalete()
{
	//		�S�Ă��폜����
	m_observer.clear();
}
