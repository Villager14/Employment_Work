/*
* @file		CommonEnemyAttack.cpp
* @brief	一般的な敵の攻撃
* @author	Morita
* @date		2024/05/01
*/

#include "pch.h"

#include "CommonEnemyAttack.h"

#include "../CommonEnemy.h"

CommonEnemyAttack::CommonEnemyAttack(CommonEnemy* commonEnemy)
	:
	m_commonEnemy(commonEnemy),
	m_attackTime(0.0f)
{
}

CommonEnemyAttack::~CommonEnemyAttack()
{
}

void CommonEnemyAttack::Initialize()
{
	//		攻撃する方向を設定する
	m_commonEnemy->GetInformation()->SetAttackDirection(m_commonEnemy->GetInformation()->GetPlayerPosition() - m_commonEnemy->GetInformation()->GetPosition());

	//		攻撃状態にする
	m_commonEnemy->GetInformation()->SetAttackJudgement(true);
}

void CommonEnemyAttack::Update()
{
	//DirectX::SimpleMath::Vector3 velocity = m_commonEnemy->GetPlayerPosition() - m_commonEnemy->GetPosition();

	//DirectX::SimpleMath::Vector3 angleVelocity = DirectX::SimpleMath::Vector3
	//(sinf(m_commonEnemy->GetRotation()), 0.0f, cosf(m_commonEnemy->GetRotation()));

	//DirectX::SimpleMath::Vector3 move = velocity - angleVelocity;

	//angleVelocity += move * 0.1f * m_commonEnemy->GetTimeSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

	//m_commonEnemy->SetRotation(atan2(angleVelocity.x, angleVelocity.z));

	////		攻撃時間
	//m_attackTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	//if (m_attackTime > 0.f)
	//{
	
	//		状態を遷移する
	m_commonEnemy->ChangeState(CommonEnemy::State::Vigilance);
	//}
}

void CommonEnemyAttack::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateScale(5.0f);

	world *= DirectX::SimpleMath::Matrix::CreateRotationY(m_commonEnemy->GetInformation()->GetRotation());

	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_commonEnemy->GetInformation()->GetPosition());

	//		モデルの描画
	//m_commonEnemy->GetModel()->Draw(LibrarySingleton::GetInstance()
	//	->GetDeviceResources()->GetD3DDeviceContext(),
	//*LibrarySingleton::GetInstance()->GetCommonState(),
	//	world, LibrarySingleton::GetInstance()->GetView(),
	//LibrarySingleton::GetInstance()->GetProj());

	//m_commonEnemy->GetPlayerAnimation()->Render();
}

void CommonEnemyAttack::Finalize()
{
	m_attackTime = 0.0f;
}
