/*
* @file		MeshCollitionHead.h
* @brief	���b�V���̓����蔻�蓪
* @author	Morita
* @date		2024/07/22
*/

#pragma once

#include "ObjectMesh.h"

class MeshCollitionHead
{
public:

	//		�R���X�g���N�^
	MeshCollitionHead();

	//		�f�X�g���N�^
	~MeshCollitionHead();


	void HeadCollition(ObjectMesh* objectMesh,
		const DirectX::SimpleMath::Vector3& playerPosition);

	//		�V�䂩�ǂ���
	bool CeilingJudgement(const DirectX::SimpleMath::Vector3& normalize);

};