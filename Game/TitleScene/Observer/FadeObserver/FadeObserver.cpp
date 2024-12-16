/*
* @file		FadeObserver.cpp
* @brief	�^�C�g��UI�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "FadeObserver.h"

FadeObserver::FadeObserver()
{
}

FadeObserver::~FadeObserver()
{
}

void FadeObserver::AddObserver(IFadeObserver* observer)
{
	//		�I�u�U�[�o�[�̒ǉ�
	m_observer.push_back(observer);
}

void FadeObserver::DeleteObserver(IFadeObserver* observer)
{
	//		�I�u�U�[�o�[�̍폜
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void FadeObserver::SceneEndFadeOut()
{
	//		�V�[���ύX�t�F�[�h�A�E�g
	for (const auto& e : m_observer)
	{
		e->SceneEndFadeOut();
	}
}

void FadeObserver::FadeOut()
{
	//		�t�F�[�h�A�E�g
	for (const auto& e : m_observer)
	{
		e->FadeOut();
	}
}

void FadeObserver::Dalete()
{
	//		�S�Ă��폜����
	m_observer.clear();
}
