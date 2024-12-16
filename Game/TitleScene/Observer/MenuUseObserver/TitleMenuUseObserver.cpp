/*
* @file		TitleUIObserver.cpp
* @brief	�^�C�g��UI�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitleMenuUseObserver.h"

TitleMenuUseObserver::TitleMenuUseObserver()
{
}

TitleMenuUseObserver::~TitleMenuUseObserver()
{
}

void TitleMenuUseObserver::AddObserver(ITitleMenuUseObserver* observer)
{
	//		�I�u�U�[�o�[�̒ǉ�
	m_observer.push_back(observer);
}

void TitleMenuUseObserver::DeleteObserver(ITitleMenuUseObserver* observer)
{
	//		�I�u�U�[�o�[�̍폜
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void TitleMenuUseObserver::MenuUse()
{
	//		���j���[���J��
	for (const auto& e : m_observer)
	{
		e->OpenMenu();
	}
}

void TitleMenuUseObserver::EnableMenu()
{
	//		���j���[���g�p�ł���悤�ɂ���
	for (const auto& e : m_observer)
	{
		e->EnableMenu();
	}
}

void TitleMenuUseObserver::DisableMenu()
{
	//		���j���[���g�p�o���Ȃ��悤�ɂ���
	for (const auto& e : m_observer)
	{
		e->DisableMenu();
	}
}

void TitleMenuUseObserver::Dalete()
{
	//		�S�Ă��폜����
	m_observer.clear();
}
