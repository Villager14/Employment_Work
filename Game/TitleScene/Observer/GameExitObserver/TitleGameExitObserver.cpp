/*
* @file		TitleGameExitObserver.h
* @brief	�^�C�g���Q�[���I���I�u�U�[�o�[
* @author	Morita
* @date		2024/12/13
*/

#include "pch.h"

#include "TitleGameExitObserver.h"

TitleGameExitObserver::TitleGameExitObserver()
{
}

TitleGameExitObserver::~TitleGameExitObserver()
{
}

void TitleGameExitObserver::AddObserver(ITitleGameExitObserver* observer)
{
	//		�I�u�U�[�o�[�̒ǉ�
	m_observer.push_back(observer);
}

void TitleGameExitObserver::DeleteObserver(ITitleGameExitObserver* observer)
{
	//		�I�u�U�[�o�[�̍폜
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}


void TitleGameExitObserver::GameExit()
{
	//		�Q�[���I��
	for (const auto& e : m_observer)
	{
		e->GameExit();
	}
}

void TitleGameExitObserver::Dalete()
{
	//		�S�Ă��폜����
	m_observer.clear();
}
