
#include "pch.h"

#include "SubjectPlayerHeight.h"

SubjectPlayerHeight::SubjectPlayerHeight()
{
}

SubjectPlayerHeight::~SubjectPlayerHeight()
{
}

void SubjectPlayerHeight::AddObserver(IPHeightObserver* observer)
{
	m_observer.push_back(observer);
}

void SubjectPlayerHeight::DeleteObserver(IPHeightObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void SubjectPlayerHeight::PlayerHeight(DirectX::SimpleMath::Vector3 height)
{
	for (const auto& e : m_observer)
	{
		e->PlayerHeght(height);
	}
}

void SubjectPlayerHeight::Dalete()
{
	m_observer.clear();
}
