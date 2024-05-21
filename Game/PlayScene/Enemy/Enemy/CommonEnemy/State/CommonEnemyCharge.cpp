/*
* @file		CommonEnemyCharge.cpp
* @brief	��ʓI�ȓG�̃`���[�W
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

	//		�`���[�W����
	m_chargeTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�`���[�W���Ԉ�莞�Ԉȏ�ɂȂ�����
	if (m_chargeTime >= 1.0f)
	{
		//		��Ԃ�J�ڂ���
		m_commonEnemy->ChangeState(m_commonEnemy->GetAttack());
	}
}

void CommonEnemyCharge::Render()
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateScale(5.0f);

	world *= DirectX::SimpleMath::Matrix::CreateRotationY(m_commonEnemy->GetRotation());

	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_commonEnemy->GetPosition());

	//		���f���̕`��
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
