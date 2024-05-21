/*
* @file		MeshCollitionWall.cpp
* @brief	メッシュの当たり判定壁
* @author	Morita
* @date		2024/04/28
*/

#include "pch.h"

#include "MeshCollitionWall.h"

#include "MeshCollitionManager.h"

MeshCollitionWall::MeshCollitionWall(MeshCollitionManager* meshCollitionManager)
	:
	m_meshCollitionManager(meshCollitionManager)
{
}

MeshCollitionWall::~MeshCollitionWall()
{
}

std::vector<DirectX::SimpleMath::Vector2> MeshCollitionWall::WallCollition(ObjectMesh* objectMesh,
	const DirectX::SimpleMath::Vector3& playerPosition, float height)
{
	m_playerPosition = playerPosition;

	m_normalize.clear();

	bool m_wallHitJudgement = false;

	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	//		壁の当たり判定
	for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	{
		//		壁かどうか判断する
		if (!WallJudgement(objectMesh->GetNormalizePosition(i))) continue;

		//		頂点の座標を受け取る
		vertex[0] = objectMesh->GetVertexPosition(i, 0);
		vertex[1] = objectMesh->GetVertexPosition(i, 1);
		vertex[2] = objectMesh->GetVertexPosition(i, 2);

		//		円の当たり判定
		if (!m_meshCollitionManager->CollitionCC(vertex, m_playerPosition, height)) continue;

		//		壁の高さの当たり判定
		if (!WallHeight(vertex, height)) continue;

		
		//		レイの開始地点
		m_rayStart = m_playerPosition;

		
		m_rayStart.y = std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y));

		m_rayStart.y += 0.01f;
		
		if (m_rayStart.y > m_playerPosition.y + 7.0f)
		{
			continue;
		}
		
		m_rayEnd = m_rayStart;

		m_rayEnd += -objectMesh->GetNormalizePosition(i) * 2.0f;

		//		同一平面上にいるかどうか
		if (!m_meshCollitionManager->OnTheSamePlane(vertex, m_rayStart, m_rayEnd,
			objectMesh->GetNormalizePosition(i), &m_hitPoint)) continue;

		//		メッシュの三角形の内側かどうか
		if (!m_meshCollitionManager->InsideTriangle(vertex,
			objectMesh->GetNormalizePosition(i),
			m_hitPoint)) continue;
		
		//		個々の中にいる場合当たっている
		if (!Extrusion(objectMesh->GetNormalizePosition(i))) continue;

		//		当たっている
		m_wallHitJudgement = true;
	}

	m_moveVelocity.clear();

	//		壁と当たっている場合
	if (m_wallHitJudgement)
	{
		m_moveVelocity.push_back({ m_playerPosition.x, m_playerPosition.z });
	}

	return m_moveVelocity;
}

bool MeshCollitionWall::WallJudgement(const DirectX::SimpleMath::Vector3& normalize)
{
	//		45度以上の法線は壁とする
	if (DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).
		Dot(normalize) >= 0.5f)
	{
		//		壁ではない
		return false;
	}

	return true;
}

bool MeshCollitionWall::WallHeight(const std::vector<DirectX::SimpleMath::Vector3>& vertex, float height)
{
	//		プレイヤーがメッシュの高さ内にいない場合処理をしない
	if (std::max(vertex[0].y, std::max(vertex[1].y, vertex[2].y)) <= m_playerPosition.y + 0.3f  ||
		std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y)) >= m_playerPosition.y + height)
	{
		//		壁の高さ外
		return false;
	}

	//		壁の高さ内
	return true;
}


bool MeshCollitionWall::Extrusion(const DirectX::SimpleMath::Vector3& normalize)
{
	//		当たったポイントとプレイヤーの座標の長さ
	float length = (m_rayStart - m_hitPoint).Length();

	//		距離がプレイヤーの半径より大きければ処理をしない
	if (length > 2.0f)
	{
		return false;
	}

	//		法線を二次元にする
	DirectX::SimpleMath::Vector2 normalizeV2 = { normalize.x, normalize.z };
	//		正規化する
	normalizeV2.Normalize();

	//		値が距離以上にならないようにする
	float change = Library::Clamp(length, 0.0f, 2.0f);

	change *= 0.5f;

	//		変化量
	normalizeV2 *= Library::Lerp(2.0f, 0.0f, change);

	//		めり込んだ分移動させる
	m_playerPosition.x += normalizeV2.x;
	m_playerPosition.z += normalizeV2.y;

	m_normalize.push_back(normalize);

	return true;
}



std::vector<DirectX::SimpleMath::Vector3>& MeshCollitionWall::WallWalk
(ObjectMesh* objectMesh, const DirectX::SimpleMath::Vector3& playerPosition)
{
	//		この値から法線を作成する
	m_meshCollitionManager->GetWallWalkNormalize();

	DirectX::SimpleMath::Vector2 normalize = 
	{ m_meshCollitionManager->GetWallWalkNormalize().x,
		m_meshCollitionManager->GetWallWalkNormalize().z };

	normalize.Normalize();

	normalize *= -1;

	//		レイの開始
	DirectX::SimpleMath::Vector3 rayStart = playerPosition;

	//		レイの終了
	DirectX::SimpleMath::Vector3 rayEnd = playerPosition;

	normalize *= 3.0f;

	rayEnd += {normalize.x, 0.0f, normalize.y};

	m_hitpp.clear();

	//		頂点
	std::vector<DirectX::SimpleMath::Vector3> vertex(3);

	for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	{
		//		壁かどうか判断する
		if (!WallJudgement(objectMesh->GetNormalizePosition(i))) continue;

		//		頂点の座標を受け取る
		vertex[0] = objectMesh->GetVertexPosition(i, 0);
		vertex[1] = objectMesh->GetVertexPosition(i, 1);
		vertex[2] = objectMesh->GetVertexPosition(i, 2);

		//		プレイーの伸長より小さい場合処理をしない
		if (std::max(vertex[0].y, std::max(vertex[1].y, vertex[2].y)) - std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y)) < 7.0f)
		{
			continue;
		}

		//		円の当たり判定が当たっていない場合これ以上処理をしない
		if (!m_meshCollitionManager->CollitionCC(vertex, rayStart, 2.0f))continue;

		//		同一平面上にいるかどうか
		if (!m_meshCollitionManager->OnTheSamePlane(vertex, rayStart, rayEnd,
			objectMesh->GetNormalizePosition(i), &m_wallWalkHitPoint)) continue;

		//		メッシュの三角形の内側かどうか
		if (m_meshCollitionManager->InsideTriangle(vertex,
			objectMesh->GetNormalizePosition(i),
			m_wallWalkHitPoint))
		{
			//		当たっている部分を追加する
			m_hitpp.push_back(m_wallWalkHitPoint);
		}
	}

	if (m_hitpp.size() == 1)
	{
		DirectX::SimpleMath::Vector3 pplayerPosition = { m_meshCollitionManager->GetWallWalkNormalize().x,
			0.0f, m_meshCollitionManager->GetWallWalkNormalize().z };

		pplayerPosition *= 2.0f;

		m_hitpp[0] += pplayerPosition;
	}

	return m_hitpp;
}
