#pragma once

#include "IPObserver.h"

class SubjectPlayer
{
public:

	SubjectPlayer();

	~SubjectPlayer();

	void AddObserver(IPObserver* observer);

	void DeleteObserver(IPObserver* observer);

	void DashCoolTime(float val);

	void Dalete();
private:

	std::vector<IPObserver*> m_observer;

};