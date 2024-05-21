/*
* @file		CommonEnemyVigilance.h
* @brief	ˆê”Ê“I‚È“GŒx‰úó‘Ô
* @author	Morita
* @date		2024/05/01
*/

#include "pch.h"

#include "CommonEnemyVigilance.h"

#include "../CommonEnemy.h"

CommonEnemyVigilance::CommonEnemyVigilance(CommonEnemy* commonEnemy)
	:
	m_commonEnemy(commonEnemy),
	m_coolTime(0.0f)
{
}

CommonEnemyVigilance::~CommonEnemyVigilance()
{
}

void CommonEnemyVigilance::Initialize()
{
}

void CommonEnemyVigilance::Update()
{
	DirectX::SimpleMath::Vector3 velocity = m_commonEnemy->GetPlayerPosition() - m_commonEnemy->GetPosition();
	
	DirectX::SimpleMath::Vector3 angleVelocity = DirectX::SimpleMath::Vector3
	(sinf(m_commonEnemy->GetRotation()), 0.0f, cosf(m_commonEnemy->GetRotation()));

	DirectX::SimpleMath::Vector3 move = velocity - angleVelocity;

	angleVelocity += move * 0.1f * m_commonEnemy->GetTimeSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_commonEnemy->SetRotation(atan2(angleVelocity.x, angleVelocity.z));

	//		ƒN[ƒ‹ƒ^ƒCƒ€
	m_coolTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_coolTime >= 1.0f)
	{
		//		ó‘Ô‚ð‘JˆÚ‚·‚é
		m_commonEnemy->ChangeState(m_commonEnemy->GetCharge());
	}
}

void CommonEnemyVigilance::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateScale(5.0f);

	world *= DirectX::SimpleMath::Matrix::CreateRotationY(m_commonEnemy->GetRotation());

	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_commonEnemy->GetPosition());

	//		ƒ‚ƒfƒ‹‚Ì•`‰æ
	m_commonEnemy->GetModel()->Draw(LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDeviceContext(),
	*LibrarySingleton::GetInstance()->GetCommonState(),
		world, LibrarySingleton::GetInstance()->GetView(),
	LibrarySingleton::GetInstance()->GetProj());
}

void CommonEnemyVigilance::Finalize()
{
	m_coolTime = 0.0f;
}
