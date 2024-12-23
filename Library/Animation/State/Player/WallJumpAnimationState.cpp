/*
* @file		WallJumpAnimationState.cpp
* @brief	壁ジャンプのアニメーション
* @author	Morita
* @date		2024/06/25
*/

#include "pch.h"

#include "WallJumpAnimationState.h"

#include "../../AnimationManager.h"


WallJumpAnimationState::WallJumpAnimationState(AnimationManager* playerAnimation)
	:
	m_elapsedTime(0.0f),
	m_animationTransration(0.0f),
	m_playerAnimation(playerAnimation)
{
}

WallJumpAnimationState::~WallJumpAnimationState()
{
}

void WallJumpAnimationState::Initialize()
{
	m_animationTransration = 1.0f;

	m_elapsedTime = 0.0f;
}

void WallJumpAnimationState::Update(float speed, DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Vector2 angle, float height,
	std::vector<PlayerBonsInformation>* bonesInformation)
{
	UNREFERENCED_PARAMETER(speed);

	(*bonesInformation)[BonsType::Body].position = position;
	(*bonesInformation)[BonsType::Body].position.y += height - 1.8f;

	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 10.0f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	DirectX::SimpleMath::Quaternion Body =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });

	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(60.0f), DirectX::XMConvertToRadians(90.0f),
				m_elapsedTime), DirectX::XMConvertToRadians(50.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(90.0f) });

	DirectX::SimpleMath::Quaternion RArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ Library::Lerp(DirectX::XMConvertToRadians(60.0f), DirectX::XMConvertToRadians(90.0f),
				m_elapsedTime), DirectX::XMConvertToRadians(-50.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(45.0f), DirectX::XMConvertToRadians(-45.0f), DirectX::XMConvertToRadians(-90.0f) });


	m_animationTransration -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransration = Library::Clamp(m_animationTransration, 0.0f, 1.0f);

	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LArmUp, bonesInformation, LArmUp, (*bonesInformation)[BonsType::LArmUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LArmDown, bonesInformation, LArmDown, (*bonesInformation)[BonsType::LArmDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RArmUp, bonesInformation, RArmUp, (*bonesInformation)[BonsType::RArmUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RArmDown, bonesInformation, RArmDown, (*bonesInformation)[BonsType::RArmDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::Body, bonesInformation, Body, (*bonesInformation)[BonsType::Body].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationLegInitialValue(bonesInformation, m_animationTransration);
}

void WallJumpAnimationState::Finalize()
{
}
