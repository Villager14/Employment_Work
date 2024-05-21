
#pragma once

#include "pch.h"

#include <vector>

class Triangle
{
public:
	//		コンストラクタ
	Triangle() {};
	//		デストラクタ
	~Triangle() {};

public:
	//		頂点
	std::vector<DirectX::SimpleMath::Vector3> m_vertex;

	//		法線
	DirectX::SimpleMath::Vector3 m_normalVector;
};