
#include "pch.h"

#include "SubjectPlayer.h"

SubjectPlayer::SubjectPlayer()
{
}

SubjectPlayer::~SubjectPlayer()
{
}

void SubjectPlayer::AddObserver(IPObserver* observer)
{
	m_observer.push_back(observer);
}

void SubjectPlayer::DeleteObserver(IPObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void SubjectPlayer::DashCoolTime(float val)
{
	for (const auto& e : m_observer)
	{
		e->DashCoolTime(val);
	}
}

void SubjectPlayer::Dalete()
{
	m_observer.clear();
}
