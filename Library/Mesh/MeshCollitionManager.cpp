/*
* @file		MeshCollitionManaager.cpp
* @brief	メッシュの当たり判定マネージャー
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "MeshCollitionManager.h"

MeshCollitionManager::MeshCollitionManager()
{
}

MeshCollitionManager::~MeshCollitionManager()
{
}

void MeshCollitionManager::Initialize()
{
	//		メッシュ床の当たり判定の生成
	m_meshCollitionFloor = std::make_unique<MeshCollitionFloor>(this);

	//		メッシュの壁の当たり判定
	m_meshCollitionWall = std::make_unique<MeshCollitionWall>(this);
}

void MeshCollitionManager::MeshCollition(ObjectMesh* objectMesh,
			const DirectX::SimpleMath::Vector3& playerPosition,
			float height, bool slidingJudgement,
			GameManager* gameManager)
{
	//		スライディング状態かどうか
	if (slidingJudgement)
	{
		playerUnderRayLength = 1.0f;
	}
	else
	{
		playerUnderRayLength = 0.5f;
	}

	//		レイの長さを設定する
	m_meshCollitionFloor->SetRayLength(playerUnderRayLength, PLAYER_ABOVE_RAY_LENGTH);

	//		壁の当たり判定
	m_wallHit = m_meshCollitionWall->WallCollition(objectMesh, playerPosition, height);

	//		オブジェクトタイプが壁の時
	if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::Wall)
	{
		//		壁に当たった法線
		m_wallHitNormalize = m_meshCollitionWall->GetNormalize();
	}

	m_wallWalkPlayerPosition = m_meshCollitionWall->WallWalk(objectMesh, playerPosition);

	if (m_wallHit.size() == 0)
	{
		m_playerPosition = playerPosition;
	}
	else
	{
		m_playerPosition = { m_wallHit[0].x, playerPosition.y, m_wallHit[0].y };
	}

	//		床の当たり判定を更新する
	m_meshHitPoint = m_meshCollitionFloor->FloorCollition(objectMesh, m_playerPosition);

	if (m_meshHitPoint.size() != 0)
	{
		//		ゴールに当たっている場合
		if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::Goal)
		{
			//		ゴールを設定する
			gameManager->SetGoalJudgement(true);
		}
	}
}

bool MeshCollitionManager::CollitionCC(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
									   const DirectX::SimpleMath::Vector3& playerPos,
									   const float& playerLength)
{
	//		メッシュの最大の辺の長さを求める
	float meshLength = std::max((vertex[0] - vertex[1]).Length(),
		std::max((vertex[0] - vertex[2]).Length(),
			(vertex[1] - vertex[2]).Length()));

	//		メッシュの中心点を求める
	DirectX::SimpleMath::Vector3 m_centerPoint = (vertex[0] + vertex[1] + vertex[2]) / 3.0f;

	//		プレイヤーとメッシュの中心の座標がメッシュの長さとプレイヤーのレイの長さより小さい時
	if ((m_centerPoint - playerPos).Length() <= meshLength + playerLength)
	{
		//		当たっている
		return true;
	}

	//		当たっていない
	return false;
}

bool MeshCollitionManager::OnTheSamePlane(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& rayStart, const DirectX::SimpleMath::Vector3& rayEnd,
	const DirectX::SimpleMath::Vector3& normalize, DirectX::SimpleMath::Vector3* hitPoint)
{
	//		三角形の中心を求める
	DirectX::SimpleMath::Vector3 center =
		(vertex[0] + vertex[1] + vertex[2]) / 3;

	//		レイの方向に向いているベクトルを出す
	DirectX::SimpleMath::Vector3 velocityS = rayStart - center;
	DirectX::SimpleMath::Vector3 velocityE = rayEnd - center;

	//		内積を取る
	float dotS = normalize.Dot(velocityS);
	float dotE = normalize.Dot(velocityE);

	//		値が０以上の場合処理をしない
	if (dotS * dotE <= 0)
	{
		//		平面上の点を求める
		float m = abs(dotS);
		float n = abs(dotE);

		//		当たっているポイント
		*hitPoint = (rayStart * n + rayEnd * m) / (m + n);

		//		含まれている
		return true;
	}

	//		含まれていない
	return false;

}

bool MeshCollitionManager::InsideTriangle(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const DirectX::SimpleMath::Vector3& normalize, const DirectX::SimpleMath::Vector3& hitPoint)
{
	for (int i = 0; i < 3; ++i)
	{
		//		当たった座標に向かうベクトル
		DirectX::SimpleMath::Vector3 hitVelocity = hitPoint - vertex[i];

		//		別の頂点に向かうベクトル
		DirectX::SimpleMath::Vector3 meshVelocity = vertex[(i + 2) % 3] - vertex[i];

		//		外積を求める
		DirectX::SimpleMath::Vector3 cross = hitVelocity.Cross(meshVelocity);

		//		正規化
		cross.Normalize();

		//		法線と外積の内積を取る
		float d = normalize.Dot(cross);

		//		0以下の場合三角形の外側にいる
		if (d < 0)
		{
			//		外側
			return false;
		}
	}

	//		内側
	return true;
}


void MeshCollitionManager::MeshHitPointClear()
{
	m_meshHitPoint.clear();
	//		壁の当たり判定を
	m_wallHit.clear();

}

