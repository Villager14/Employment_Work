/*
* @file		MeshCollitionHead.h
* @brief	���b�V���̓����蔻�蓪
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
	////		���_�̐���������������
	//for (int i = 0; i < objectMesh->GetVertexSize(); ++i)
	//{
	//	//		�V�䂩�ǂ������f����
	//	if (CeilingJudgement(objectMesh->GetNormalizePosition(i))) continue;



	//}
}

bool MeshCollitionHead::CeilingJudgement(const DirectX::SimpleMath::Vector3& normalize)
{
	//		�������̖@���ƃ��b�V���̖@���œ��ς����
	float dot = DirectX::SimpleMath::Vector3(0, -1, 0).Dot(normalize);

	//		�@���̕��������������Ă��Ȃ��ꍇ
	if (dot < 0.2f)
	{
		//		�V��ł͂Ȃ�
		return false;
	}

	return true;
}
