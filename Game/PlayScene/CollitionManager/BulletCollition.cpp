/*
* @file		BulletCollition.cpp
* @brief	弾の当たり判定
* @author	Morita
* @date		2024/05/06
*/

#include "pch.h"

#include "BulletCollition.h"

BulletCollition::BulletCollition()
{
}

BulletCollition::~BulletCollition()
{
}

void BulletCollition::Initialize()
{
}

bool BulletCollition::Collition(const DirectX::SimpleMath::Vector3& playerPosition,
								const DirectX::SimpleMath::Vector3& playerHeadPosition,
								const std::vector<DirectX::SimpleMath::Vector3>& bulletPosition)
{
	//		弾の半径を３とする
	//		プレイヤーの高さは７

	float bulletRadian = 1.5f;
	float height = 7.0f;
	float playerRadian = 1.0f;

	for (int i = 0, max = static_cast<int>(bulletPosition.size()); i < max; ++i)
	{
		//		
		if ((bulletPosition[i] - playerPosition).Length() > height + bulletRadian)
		{
			continue;
		}

		if (playerPosition.y > bulletPosition[i].y + 3.0f ||
			playerHeadPosition.y < bulletPosition[i].y - 3.0f)
		{
			continue;
		}

		DirectX::SimpleMath::Vector2 ppos = { playerPosition.x, playerPosition.z };

		DirectX::SimpleMath::Vector2 bulletP = { bulletPosition[i].x, bulletPosition[i].z };

		if ((ppos - bulletP).Length() < playerRadian + bulletRadian)
		{
			//		当たっている
			return true;
		}
	}

	return false;
}
