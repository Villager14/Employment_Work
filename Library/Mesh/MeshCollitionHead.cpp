/*
* @file		MeshCollitionHead.h
* @brief	メッシュの当たり判定頭
* @author	Morita
* @date		2024/07/22
*/

#include "pch.h"
#include "MeshCollitionHead.h"

MeshCollitionHead::MeshCollitionHead()
{
}

MeshCollitionHead::~MeshCollitionHead()
{
}

void MeshCollitionHead::HeadCollition(ObjectMesh* objectMesh,
	const DirectX::SimpleMath::Vector3& playerPosition)
{
	////		頂点の数だけ処理をする
	//for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	//{
	//	//		天井かどうか判断する
	//	if (CeilingJudgement(objectMesh->GetNormalizePosition(i))) continue;



	//}
}

bool MeshCollitionHead::CeilingJudgement(const DirectX::SimpleMath::Vector3& normalize)
{
	//		下向きの法線とメッシュの法線で内積を取る
	float dot = DirectX::SimpleMath::Vector3(0, -1, 0).Dot(normalize);

	//		法線の方向が下を向いていない場合
	if (dot < 0.2f)
	{
		//		天井ではない
		return false;
	}

	return true;
}
