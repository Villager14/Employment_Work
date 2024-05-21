/*
* @file		EnemyManager.cpp
* @brief	エネミーマネージャー
* @author	Morita
* @date		2024/04/29
*/

#include "pch.h"

#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Initialize()
{
	//		一般エネミーの生成
	m_commonEnemy.push_back(std::make_unique<CommonEnemy>());

	//		一般エネミーの初期化処理
	for (int i = 0, max = static_cast<int>(m_commonEnemy.size()); i < max; ++i)
	{
		m_commonEnemy[i]->Initialize();
	}

	//		一般エネミーの弾のマネージャーの生成
	m_commonEnemyBulletManager = std::make_unique<CommonEnemyBulletManager>();

	//		一般エネミー弾のマネージャーの初期化
	m_commonEnemyBulletManager->Initialize(static_cast<int>(m_commonEnemy.size()));
}

void EnemyManager::Update(const float& timeSpeed,
	const DirectX::SimpleMath::Vector3& playerPosition)
{
	for (int i = 0, max = static_cast<int>(m_commonEnemy.size()); i < max; ++i)
	{
		//		更新処理
		m_commonEnemy[i]->Update(playerPosition, timeSpeed);

		//		攻撃状態かどうか
		if (m_commonEnemy[i]->GetAttackJudgement())
		{
			m_commonEnemyBulletManager->Firing(m_commonEnemy[i]->GetAttackPosition(),
				m_commonEnemy[i]->GetAttackDirection());

			//		攻撃状態を終了する
			m_commonEnemy[i]->SetAttackJudgement(false);
		}
	}

	//		弾管理クラスの更新
	m_commonEnemyBulletManager->Update(timeSpeed);
}

void EnemyManager::Render()
{
	for (int i = 0, max = static_cast<int>(m_commonEnemy.size()); i < max; ++i)
	//		描画処理
	m_commonEnemy[i]->Render();

	//		弾管理クラスの描画
	m_commonEnemyBulletManager->Render();
}
