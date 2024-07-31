
#pragma once

#include "pch.h"

#include <vector>

//class Triangle
//{
//public:
//	//		�R���X�g���N�^
//	Triangle() {};
//	//		�f�X�g���N�^
//	~Triangle() {};
//
//public:
//	//		���_
//	std::vector<DirectX::SimpleMath::Vector3> m_vertex;
//
//	std::vector<int> m_vertexIndex;
//
//	//		�@��
//	DirectX::SimpleMath::Vector3 m_normalVector;
//};

struct Triangle
{
	//		���_
	std::vector<DirectX::SimpleMath::Vector3> m_vertex;

	//		���_�C���f�b�N�X
	std::vector<int> m_vertexIndex;

	//		�@��
	DirectX::SimpleMath::Vector3 m_normalVector;
};