/*
* @file		DashAnimationState.cpp
* @brief	ダッシュのアニメーション
* @author	Morita
* @date		2024/06/25
*/

#include "pch.h"

#include "DashAnimationState.h"

#include "../../AnimationManager.h"

DashAnimationState::DashAnimationState(AnimationManager* playerAnimation)
	:
	m_elapsedTime(0.0f),
	m_animationTransration(0.0f),
	m_playerAnimation(playerAnimation)
{
}

DashAnimationState::~DashAnimationState()
{
}

void DashAnimationState::Initialize()
{
	m_animationTransration = 1.0f;

	m_elapsedTime = 0.0f;
}

void DashAnimationState::Update(float speed, DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Vector2 angle, float height,
	std::vector<PlayerBonsInformation>* bonesInformation)
{
	UNREFERENCED_PARAMETER(speed);

	(*bonesInformation)[BonsType::Body].position = position;
	(*bonesInformation)[BonsType::Body].position.y += height - 1.8f;
	(*bonesInformation)[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });


	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 6.0f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 2.0f);

	DirectX::SimpleMath::Quaternion LArmUp;
	DirectX::SimpleMath::Quaternion LArmDown;
	DirectX::SimpleMath::Quaternion RArmUp;
	DirectX::SimpleMath::Quaternion RArmDown;


	if (m_elapsedTime <= 1.0f)
	{
		LArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(120.0f), DirectX::XMConvertToRadians(-20.0f) , DirectX::XMConvertToRadians(0.0f) });

		LArmDown =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(10.0f), DirectX::XMConvertToRadians(70.0f) });

		RArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(120.0f), DirectX::XMConvertToRadians(20.0f) , 0.0f });

		RArmDown =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-10.0f), DirectX::XMConvertToRadians(-60.0f) });
	}
	else
	{
		LArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ Library::Lerp(DirectX::XMConvertToRadians(120.0f), DirectX::XMConvertToRadians(90.0f),m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(-20.0f), DirectX::XMConvertToRadians(00.0f),m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-30.0f),m_elapsedTime - 1.0f) });

		LArmDown = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(10.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(70.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f) });


		RArmUp =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
				{ Library::Lerp(DirectX::XMConvertToRadians(120.0f), DirectX::XMConvertToRadians(90.0f),m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(20.0f), DirectX::XMConvertToRadians(00.0f),m_elapsedTime - 1.0f),
				Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(30.0f),m_elapsedTime - 1.0f) });


		RArmDown = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(-10.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f),
			Library::Lerp(DirectX::XMConvertToRadians(-60.0f), DirectX::XMConvertToRadians(0.0f),m_elapsedTime - 1.0f) });
	}


	m_animationTransration -= LibrarySingleton::GetInstance()->GetElpsedTime() * 7.0f;

	m_animationTransration = Library::Clamp(m_animationTransration, 0.0f, 1.0f);

	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LArmUp, bonesInformation, LArmUp, (*bonesInformation)[BonsType::LArmUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LArmDown, bonesInformation, LArmDown, (*bonesInformation)[BonsType::LArmDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RArmUp, bonesInformation, RArmUp, (*bonesInformation)[BonsType::RArmUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RArmDown, bonesInformation, RArmDown, (*bonesInformation)[BonsType::RArmDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationLegInitialValue(bonesInformation, m_animationTransration);
}

void DashAnimationState::Finalize()
{
}
