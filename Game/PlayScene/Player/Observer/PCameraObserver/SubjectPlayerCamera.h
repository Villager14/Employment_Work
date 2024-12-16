#pragma once

#include "IPCameraObserver.h"

class SubjectPlayerCamera
{
public:

	SubjectPlayerCamera();

	~SubjectPlayerCamera();

	void AddObserver(IPCameraObserver* observer);

	void DeleteObserver(IPCameraObserver* observer);

	void ShakeHead();

	void CameraStop();

	void WallWalkMove(float height);

	void Direction(DirectX::SimpleMath::Vector3 direction);

	void WallNormalize(DirectX::SimpleMath::Vector3 normalize);

	void Dalete();

private:

	std::vector<IPCameraObserver*> m_observer;

};