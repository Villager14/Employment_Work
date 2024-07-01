/*
* @file		UprightAnimationState.cpp
* @brief	�����̃A�j���[�V����
* @author	Morita
* @date		2024/06/27
*/

#include "pch.h"

#include "UprightAnimationState.h"

#include "../PlayerAnimation.h"


UprightAnimationState::UprightAnimationState(PlayerAnimation* PlayerAnimation)
	:
	m_elapsedTime(0.0f),
	m_animationTransration(0.0f),
	m_playerAnimation(PlayerAnimation)
{
}

UprightAnimationState::~UprightAnimationState()
{
}

void UprightAnimationState::Initialize()
{
	m_animationTransration = 1.0f;

	m_elapsedTime = 0.0f;
}

void UprightAnimationState::Update(float speed, DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Vector2 angle, float height,
	std::vector<PlayerBonsInformation>* bonesInformation)
{
	UNREFERENCED_PARAMETER(speed);

	(*bonesInformation)[BonsType::Body].position = position;
	(*bonesInformation)[BonsType::Body].position.y += height - 1.8f;
	(*bonesInformation)[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(-angle.x + 180.0f), 0.0f });

	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 4.0f;

	m_animationTransration -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransration = Library::Clamp(m_animationTransration, 0.0f, 1.0f);

	m_playerAnimation->AnimationMovement(BonsType::LArmUp, bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*bonesInformation)[BonsType::LArmUp].rotation, m_animationTransration);
	m_playerAnimation->AnimationMovement(BonsType::LArmDown, bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*bonesInformation)[BonsType::LArmDown].rotation, m_animationTransration);
	m_playerAnimation->AnimationMovement(BonsType::RArmUp, bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*bonesInformation)[BonsType::RArmUp].rotation, m_animationTransration);
	m_playerAnimation->AnimationMovement(BonsType::RArmDown, bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*bonesInformation)[BonsType::RArmDown].rotation, m_animationTransration);
	m_playerAnimation->AnimationLegInitialValue(bonesInformation, m_animationTransration);
}

void UprightAnimationState::Finalize()
{
}