/*
* @file		CommonEnemyStay.cpp
* @brief	��ʓI�ȓG�ҋ@���
* @author	Morita
* @date		2024/05/01
*/

#include "pch.h"

#include "CommonEnemyStay.h"

#include "../CommonEnemy.h"

CommonEnemyStay::CommonEnemyStay(CommonEnemy* commonEnemy)
	:
	m_commonEnemy(commonEnemy)
{
}

CommonEnemyStay::~CommonEnemyStay()
{
}

void CommonEnemyStay::Initialize()
{
}

void CommonEnemyStay::Update()
{
	//		��Ԃ�J�ڂ���
	m_commonEnemy->ChangeState(m_commonEnemy->GetVigilance());
}

void CommonEnemyStay::Render()
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

void CommonEnemyStay::Finalize()
{
}
