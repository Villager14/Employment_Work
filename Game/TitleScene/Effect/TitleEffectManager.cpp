#include "pch.h"

#include "TitleEffectManager.h"

TitleEffectManager::TitleEffectManager()
{
	m_degitalRain = std::make_unique<DegitalRain>();
}

TitleEffectManager::~TitleEffectManager()
{
}

void TitleEffectManager::Initialize()
{
	m_degitalRain->Initialzie();
}

void TitleEffectManager::Update()
{
	m_degitalRain->Update();
}

void TitleEffectManager::Render(PostEffectFlag::Flag flag)
{
	m_degitalRain->Render(flag);
}

void TitleEffectManager::Finalize()
{
	m_degitalRain->Finalize();
}

void TitleEffectManager::CameraViewVelocity(DirectX::SimpleMath::Vector3 velocity)
{
	m_degitalRain->SetCameraViewVelocity(velocity);
}

void TitleEffectManager::CameraView(DirectX::SimpleMath::Vector3 view)
{
	m_degitalRain->SetCameraEye(view);
}

void TitleEffectManager::CameraUp(DirectX::SimpleMath::Vector3 up)
{
	m_degitalRain->SetCameraUp(up);
}
