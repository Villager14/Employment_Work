#pragma once

#include "IPHeightObserver.h"

class SubjectPlayerHeight
{
public:

	SubjectPlayerHeight();

	~SubjectPlayerHeight();

	void AddObserver(IPHeightObserver* observer);

	void DeleteObserver(IPHeightObserver* observer);

	void PlayerHeight(DirectX::SimpleMath::Vector3 height);

	void Dalete();

private:

	std::vector<IPHeightObserver*> m_observer;

};