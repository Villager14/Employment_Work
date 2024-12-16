#pragma once

#include "IPSpeedObserver.h"

class SubjectPlayerSpeed
{
public:

	SubjectPlayerSpeed();

	~SubjectPlayerSpeed();

	void AddObserver(IPSpeedObserver* observer);

	void DeleteObserver(IPSpeedObserver* observer);

	void PlayerSpeed(float val);

	void Dalete();

private:

	std::vector<IPSpeedObserver*> m_observer;

};