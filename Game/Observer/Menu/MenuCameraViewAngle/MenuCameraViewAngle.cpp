/*
* @file		MenuCameraViewAngle.cpp
* @brief	���j���[�̃J�����̎���p���󂯎��I�u�U�[�o�[
* @author	Morita
* @date		2024/12/23
*/

#include "pch.h"

#include "MenuCameraViewAngle.h"

MenuCameraViewAngle::MenuCameraViewAngle()
{
}

MenuCameraViewAngle::~MenuCameraViewAngle()
{
}

void MenuCameraViewAngle::AddObserver(IMenuCameraViewAngle* observer)
{
	m_observer.push_back(observer);
}

void MenuCameraViewAngle::DeleteObserver(IMenuCameraViewAngle* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuCameraViewAngle::GetMenuCameraViewAngle(float angle)
{
	for (const auto& e : m_observer)
	{
		e->GetMenuCameraViewAngle(angle);
	}
}

void MenuCameraViewAngle::Dalete()
{
	m_observer.clear();
}
