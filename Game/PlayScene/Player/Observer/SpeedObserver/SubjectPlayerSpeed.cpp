
#include "pch.h"

#include "SubjectPlayerSpeed.h"

SubjectPlayerSpeed::SubjectPlayerSpeed()
{
}

SubjectPlayerSpeed::~SubjectPlayerSpeed()
{
}

void SubjectPlayerSpeed::AddObserver(IPSpeedObserver* observer)
{
	m_observer.push_back(observer);
}

void SubjectPlayerSpeed::DeleteObserver(IPSpeedObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void SubjectPlayerSpeed::PlayerSpeed(float val)
{
	for (const auto& e : m_observer)
	{
		e->NowSpeed(val);
	}
}

void SubjectPlayerSpeed::Dalete()
{
	m_observer.clear();
}
