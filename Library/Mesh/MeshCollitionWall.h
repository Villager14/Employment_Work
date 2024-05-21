/*
* @file		MeshCollitionWall.cpp
* @brief	メッシュの当たり判定壁
* @author	Morita
* @date		2024/04/28
*/

#pragma once

#include "ObjectMesh.h"

class MeshCollitionManager;

class MeshCollitionWall
{
public:

	MeshCollitionWall(MeshCollitionManager* meshCollitionManager);

	~MeshCollitionWall();

	/*
	*	壁の当たり判定
	* 
	*	@param	(objectMesh)		オブジェクトメッシュ
	*	@param	(playerPosition)	プレイヤーの座標
	*	@param	(height)	プレイヤーの高さ
	*/
	std::vector<DirectX::SimpleMath::Vector2> WallCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition,
		float height);

	/*
	*	壁に当たった時の法線
	*
	*	@return 法線
	*/
	std::vector<DirectX::SimpleMath::Vector3> GetNormalize() { return m_normalize; }

	/*
	*	壁かどうか判断する
	* 
	*	@param	(normalize)	法線
	*	@return 壁かどうか true : 壁である false : 壁ではない
	*/
	bool WallJudgement(const DirectX::SimpleMath::Vector3& normalize);

	/*
	*	壁の高さにプレイヤーがいるかどうか
	* 
	*	@param	(vertex)	頂点
	*	@param	(height)	プレイヤーの高さ
	*	@return 高さ内にいるかどうか true : いる　false : いない
	*/
	bool WallHeight(const std::vector<DirectX::SimpleMath::Vector3>& vertex, float height);

	bool Extrusion(const DirectX::SimpleMath::Vector3& normalize);

	std::vector<DirectX::SimpleMath::Vector3>& WallWalk(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition);

private:

	MeshCollitionManager* m_meshCollitionManager;

	//		当たっているポイント
	DirectX::SimpleMath::Vector3 m_hitPoint;

	//		移動量
	std::vector<DirectX::SimpleMath::Vector2> m_moveVelocity;

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		法線
	std::vector<DirectX::SimpleMath::Vector3> m_normalize;

	//		
	DirectX::SimpleMath::Vector3 m_wallWalkHitPoint;

	std::vector<DirectX::SimpleMath::Vector3> m_hitpp;

	//		レイの開始
	DirectX::SimpleMath::Vector3 m_rayStart;

	//		レイの終了
	DirectX::SimpleMath::Vector3 m_rayEnd;
};