/*
* @file		SetSliderSettingValObserver.cpp
* @brief	スライダーの値を設定に送るオブザーバー
* @author	Morita
* @date		2024/12/26
*/

#include "pch.h"

#include "SetSliderSettingValObserver.h"

SetSliderSettingValObserver::SetSliderSettingValObserver()
{
}

SetSliderSettingValObserver::~SetSliderSettingValObserver()
{
}

void SetSliderSettingValObserver::AddObserver(ISetSliderSettingValObserver* observer)
{
	m_observer.push_back(observer);
}

void SetSliderSettingValObserver::DeleteObserver(ISetSliderSettingValObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void SetSliderSettingValObserver::SetFov(float val)
{
	for (const auto& e : m_observer)
	{
		e->SetFov(val);
	}
}

void SetSliderSettingValObserver::SetMouseSensitivity(float val)
{
	for (const auto& e : m_observer)
	{
		e->SetMouseSensitivity(val);
	}
}

void SetSliderSettingValObserver::Dalete()
{
	m_observer.clear();
}
