/*
* @file		TitlePlayerAnimationObserver.cpp
* @brief	�v���C���[�̃A�j���V�����I�u�U�[�o�[
* @author	Morita
* @date		2024/12/16
*/

#include "pch.h"

#include "TitlePlayerAnimationObserver.h"

TitlePlayerAnimationObserver::TitlePlayerAnimationObserver()
{
}

TitlePlayerAnimationObserver::~TitlePlayerAnimationObserver()
{
}

void TitlePlayerAnimationObserver::AddObserver(ITitlePlayerAnimationObserver* observer)
{
	//		�I�u�U�[�o�[��ǉ�����
	m_observer.push_back(observer);
}

void TitlePlayerAnimationObserver::DeleteObserver(ITitlePlayerAnimationObserver* observer)
{
	//		�I�u�U�[�o�[���폜����
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void TitlePlayerAnimationObserver::Dalete()
{
	//		�S�Ă��폜����
	m_observer.clear();
}

void TitlePlayerAnimationObserver::PlayAnimation()
{
	//		�v���C�A�j���[�V����
	for (const auto& e : m_observer)
	{
		e->PlayAnimation();
	}
}

void TitlePlayerAnimationObserver::SettingAnimation()
{
	//		�ݒ�A�j���[�V����
	for (const auto& e : m_observer)
	{
		e->SettingAnimation();
	}
}

void TitlePlayerAnimationObserver::ExitAnimation()
{
	//		�I���A�j���[�V����
	for (const auto& e : m_observer)
	{
		e->ExitAnimation();
	}
}
