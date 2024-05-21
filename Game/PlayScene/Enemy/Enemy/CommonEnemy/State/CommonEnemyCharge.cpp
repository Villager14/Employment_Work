/*
* @file		CommonEnemyCharge.cpp
* @brief	一般的な敵のチャージ
* @author	Morita
* @date		2024/05/01
*/

#include "pch.h"

#include "CommonEnemyCharge.h"

#include "../CommonEnemy.h"

CommonEnemyCharge::CommonEnemyCharge(CommonEnemy* commonEnemy)
	:
	m_commonEnemy(commonEnemy),
	m_chargeTime(0.0f)
{
}

CommonEnemyCharge::~CommonEnemyCharge()
{
}

void CommonEnemyCharge::Initialize()
{
}

void CommonEnemyCharge::Update()
{
	DirectX::SimpleMath::Vector3 velocity = m_commonEnemy->GetPlayerPosition() - m_commonEnemy->GetPosition();

	DirectX::SimpleMath::Vector3 angleVelocity = DirectX::SimpleMath::Vector3
	(sinf(m_commonEnemy->GetRotation()), 0.0f, cosf(m_commonEnemy->GetRotation()));

	DirectX::SimpleMath::Vector3 move = velocity - angleVelocity;

	angleVelocity += move * 0.1f * m_commonEnemy->GetTimeSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_commonEnemy->SetRotation(atan2(angleVelocity.x, angleVelocity.z));

	//		チャージ時間
	m_chargeTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		チャージ時間一定時間以上になった時
	if (m_chargeTime >= 1.0f)
	{
		//		状態を遷移する
		m_commonEnemy->ChangeState(m_commonEnemy->GetAttack());
	}
}

void CommonEnemyCharge::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateScale(5.0f);

	world *= DirectX::SimpleMath::Matrix::CreateRotationY(m_commonEnemy->GetRotation());

	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_commonEnemy->GetPosition());

	//		モデルの描画
	m_commonEnemy->GetModel()->Draw(LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDeviceContext(),
	*LibrarySingleton::GetInstance()->GetCommonState(),
		world, LibrarySingleton::GetInstance()->GetView(),
	LibrarySingleton::GetInstance()->GetProj());
}

void CommonEnemyCharge::Finalize()
{
	m_chargeTime = 0.0f;
}
