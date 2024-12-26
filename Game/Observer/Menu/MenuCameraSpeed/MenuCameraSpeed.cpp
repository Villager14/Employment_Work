/*
* @file		MenuCameraSpeed.cpp
* @brief	メニューのカメラの速度を受け取るオブザーバー
* @author	Morita
* @date		2024/12/23
*/

#include "pch.h"

#include "MenuCameraSpeed.h"

MenuCameraSpeed::MenuCameraSpeed()
{
}

MenuCameraSpeed::~MenuCameraSpeed()
{
}

void MenuCameraSpeed::AddObserver(IMenuCameraSpeed* observer)
{
	m_observer.push_back(observer);
}

void MenuCameraSpeed::DeleteObserver(IMenuCameraSpeed* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuCameraSpeed::GetMenuCameraSpeed(float speed)
{
	for (const auto& e : m_observer)
	{
		e->GetMenuCameraSpeed(speed);
	}
}

void MenuCameraSpeed::Dalete()
{
	m_observer.clear();
}
