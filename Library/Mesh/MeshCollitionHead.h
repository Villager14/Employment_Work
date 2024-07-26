/*
* @file		MeshCollitionHead.h
* @brief	メッシュの当たり判定頭
* @author	Morita
* @date		2024/07/22
*/

#pragma once

#include "ObjectMesh.h"

class MeshCollitionHead
{
public:

	//		コンストラクタ
	MeshCollitionHead();

	//		デストラクタ
	~MeshCollitionHead();


	void HeadCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition);

	//		天井かどうか
	bool CeilingJudgement(const DirectX::SimpleMath::Vector3& normalize);

};