
#pragma once

#include "pch.h"

#include <vector>

class Triangle
{
public:
	//		�R���X�g���N�^
	Triangle() {};
	//		�f�X�g���N�^
	~Triangle() {};

public:
	//		���_
	std::vector<DirectX::SimpleMath::Vector3> m_vertex;

	//		�@��
	DirectX::SimpleMath::Vector3 m_normalVector;
};