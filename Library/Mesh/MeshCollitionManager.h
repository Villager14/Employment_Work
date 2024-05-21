/*
* @file		MeshCollitionManager.h
* @brief	メッシュの当たり判定マネージャー
* @author	Morita
* @date		2024/04/16
*/

#pragma once

#include "Triangle.h"

#include "ObjectMesh.h"

#include "MeshCollitionFloor.h"

#include "MeshCollitionWall.h"

class MeshCollitionManager
{
public:
	//		コンストラクタ
	MeshCollitionManager();

	//		デストラクタ
	~MeshCollitionManager();
	
	//		初期化処理
	void Initialize();

	//		メッシュの当たり判定
	/*
	*	メッシュの当たり判定
	* 
	*	@param	(objctMesh)			オブジェクトメッシュ
	*	@param	(playerPosition)	プレイヤーの座標
	*	@param	(height)			高さ
	*	@param	(slidingJudgement)	スライディングをしているかどうか
	*/
	void MeshCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition,
		float height, bool slidingJudgement);

	/*
	*	円と円の当たり判定
	* 
	*	@param	(vertex)	メッシュの頂点
	*	@param	(playerPos)	プレイヤーの座標
	*	@param	(rayStart)	プレイヤーの長さ
	*	@return 当たったかどうか true : 当たった false : 当たっていない
	*/
	bool CollitionCC(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
					 const DirectX::SimpleMath::Vector3& playerPos,
					 const float& playerLength);

	/*
	*	同一平面上にいるかどうか
	* 
	*	@param	(vertex)	メッシュの頂点
	*	@param	(rayStart)	レイの始点
	*	@param	(rayEnd)	レイの終点
	*	@param	(normalize)	メッシュの法線
	*	@param	(hitPoint)	当たった場所
	*	@return 含まれているかどうか	true : 含まれている false : 含まれていない
	*/
	bool OnTheSamePlane(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
						const DirectX::SimpleMath::Vector3& rayStart,
						const DirectX::SimpleMath::Vector3& rayEnd,
						const DirectX::SimpleMath::Vector3& normalize,
						DirectX::SimpleMath::Vector3* hitPoint);

	/*
	*	三角形の内側にいるかどうか
	* 
	*	@param	(vertex)	メッシュの頂点
	*	@param	(normalize)	メッシュの法線
	*	@param	(hitPoint)	当たった場所
	*	@return 内側にいるかどうか true : 内側 false : 外側
	*/
	bool InsideTriangle(const std::vector<DirectX::SimpleMath::Vector3>& vertex,
						const DirectX::SimpleMath::Vector3& normalize,
						const DirectX::SimpleMath::Vector3& hitPoint);

	void MeshHitPointClear();
private:

	//		プレイヤーのレイの長さ上
	const float PLAYER_ABOVE_RAY_LENGTH = 2.0f;

private:

	float playerUnderRayLength = 0.5f;
	
	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		メッシュの当たったポイント
	std::vector<DirectX::SimpleMath::Vector3> m_meshHitPoint;

	//		壁の当たり判定
	std::vector<DirectX::SimpleMath::Vector2> m_wallHit;

	//		壁の法線の当たり判定
	std::vector<DirectX::SimpleMath::Vector3> m_wallHitNormalize;

	//		メッシュ床の当たり判定
	std::unique_ptr<MeshCollitionFloor> m_meshCollitionFloor;

	//		メッシュの壁当たり判定
	std::unique_ptr<MeshCollitionWall> m_meshCollitionWall;

	//		壁歩き法線
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;

	//		壁歩き時のプレイヤーの座標
	std::vector<DirectX::SimpleMath::Vector3> m_wallWalkPlayerPosition;

public:

	/*
	*	メッシュの当たったポイントを受け取る
	* 
	*	@return		座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetMeshHitPoint() { return m_meshHitPoint; }

	/*
	*	メッシュが壁に当たったポイントを受け取る
	*
	*	@return		移動量
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetMeshWallHit() { return m_wallHit; }

	/*
	*	メッシュ壁に当たった時の法線を受け取る
	* 
	*	@return 法線
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWallHitNormalize() { return m_wallHitNormalize; }

	/*
	*	壁の歩き法線を設定する
	*
	*	@param	(normalize) 法線
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	壁の歩き法線を受け取る
	*
	*	@return 法線
	*/
	const DirectX::SimpleMath::Vector3& GetWallWalkNormalize() { return m_wallWalkNormalize; }

	/*
	*	壁歩き時のプレイヤーの座標を受け取る
	* 
	*	@return 壁歩き時のプレイヤーの座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWallWalkPlayerPosition() { return m_wallWalkPlayerPosition; }

	/*
	*	床の法線を受け取る
	* 
	*	@return 法線
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetFloorNormalize() { return m_meshCollitionFloor->GetNormalize(); }
};