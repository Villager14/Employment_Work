
#include "pch.h"

#include "SubjectPlayerCamera.h"

SubjectPlayerCamera::SubjectPlayerCamera()
{
}

SubjectPlayerCamera::~SubjectPlayerCamera()
{
}

void SubjectPlayerCamera::AddObserver(IPCameraObserver* observer)
{
	m_observer.push_back(observer);
}

void SubjectPlayerCamera::DeleteObserver(IPCameraObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void SubjectPlayerCamera::ShakeHead()
{
	for (const auto& e : m_observer)
	{
		e->ShakeHead();
	}
}

void SubjectPlayerCamera::CameraStop()
{
	for (const auto& e : m_observer)
	{
		e->CameraStop();
	}
}

void SubjectPlayerCamera::WallWalkMove(float height)
{
	for (const auto& e : m_observer)
	{
		e->WallWalkMove(height);
	}
}

void SubjectPlayerCamera::Direction(DirectX::SimpleMath::Vector3 direction)
{
	for (const auto& e : m_observer)
	{
		e->Direction(direction);
	}
}

void SubjectPlayerCamera::WallNormalize(DirectX::SimpleMath::Vector3 normalize)
{
	for (const auto& e : m_observer)
	{
		e->WallNormalize(normalize);
	}
}

void SubjectPlayerCamera::Dalete()
{
	m_observer.clear();
}
