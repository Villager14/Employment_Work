/*
* @file		CameraViewVelocityObserver.cpp
* @brief	カメラのビューベクトルオブザーバー
* @author	Morita
* @date		2024/12/16
*/

#include "pch.h"

#include "CameraViewVelocityObserver.h"

CameraViewVelocityObserver::CameraViewVelocityObserver()
{
}

CameraViewVelocityObserver::~CameraViewVelocityObserver()
{
}

void CameraViewVelocityObserver::AddObserver(ICameraViewVelocityObserver* observer)
{
	m_observer.push_back(observer);
}

void CameraViewVelocityObserver::DeleteObserver(ICameraViewVelocityObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void CameraViewVelocityObserver::CameraViewVelocity(DirectX::SimpleMath::Vector3 velocity)
{
	for (const auto& e : m_observer)
	{
		e->CameraViewVelocity(velocity);
	}
}

void CameraViewVelocityObserver::CameraView(DirectX::SimpleMath::Vector3 view)
{
	for (const auto& e : m_observer)
	{
		e->CameraView(view);
	}
}

void CameraViewVelocityObserver::CameraUp(DirectX::SimpleMath::Vector3 up)
{
	for (const auto& e : m_observer)
	{
		e->CameraUp(up);
	}
}

void CameraViewVelocityObserver::Dalete()
{
	m_observer.clear();
}
