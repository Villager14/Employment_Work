/*
* @file		TitlePostEffectObserver.cpp
* @brief	�|�X�g�G�t�F�N�g�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitlePostEffectObserver.h"

TitlePostEffectObserver::TitlePostEffectObserver()
{
}

TitlePostEffectObserver::~TitlePostEffectObserver()
{
}

void TitlePostEffectObserver::AddObserver(ITitlePostEffectObserver* observer)
{
	//		�I�u�U�[�o�[��ǉ�����
	m_observer.push_back(observer);
}

void TitlePostEffectObserver::DeleteObserver(ITitlePostEffectObserver* observer)
{
	//		�I�u�U�[�o�[���폜����
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void TitlePostEffectObserver::FadeIn()
{
	//		�t�F�[�h�C���̏���
	for (const auto& e : m_observer)
	{
		e->FadeIn();
	}
}

void TitlePostEffectObserver::FadeOut()
{
	//		�t�F�[�h�A�E�g�̏���
	for (const auto& e : m_observer)
	{
		e->FadeOut();
	}
}

void TitlePostEffectObserver::Dalete()
{
	//		�S�Ă��폜����
	m_observer.clear();
}
