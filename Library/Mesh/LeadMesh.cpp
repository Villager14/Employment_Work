/*
* @file		LeadMesh.cpp
* @brief	メッシュの読み込み
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "LeadMesh.h"

#include <fstream>

#include <Effects.h>

LeadMesh::LeadMesh()
{
}

LeadMesh::~LeadMesh()
{
}

std::vector<std::unique_ptr<Triangle>> LeadMesh::Lead
							(const wchar_t* filePath)
{
	//		頂点
	std::vector<DirectX::SimpleMath::Vector3> vertex;

	//		頂点インデックス
	std::vector<int> vertexIndex;

	//		ファイルを開く
	std::ifstream ifs(filePath);

	std::string str;

	while (std::getline(ifs, str))
	{
		//		頂点の場合
		if (str[0] == 'v' && str[1] == ' ')
		{
			DirectX::SimpleMath::Vector3 val;

			//		ファイルから受けとった値をfloatへ変換&代入する
			sscanf_s(str.data(), "v %f %f %f", &val.x, &val.y, &val.z);

			//		頂点を受け取る
			vertex.push_back(val);
		}

		//		インデックスの場合
		if (str[0] == 'f')
		{
			int a, b, c;

			sscanf_s(str.data(), "f %d %d %d", &a, &b, &c);

			if (a != b && a != c && b != c)
			{
				vertexIndex.push_back(a - 1);
				vertexIndex.push_back(b - 1);
				vertexIndex.push_back(c - 1);
			}
		}
	}

	//		ファイルを閉じる
	ifs.close();

	//		三角形メッシュの作製
	CreateTrinangle(vertex, vertexIndex);

	//		法線を作成
	CreateNormalize();

	return std::move(m_triangle);
}

void LeadMesh::CreateTrinangle(
	const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const std::vector<int> vertexIndex)
{
	for (int i = 0; i < vertexIndex.size(); ++i)
	{
		std::unique_ptr<Triangle> triangle = std::make_unique<Triangle>();

		//		頂点を代入する
		triangle->m_vertex.push_back(vertex[vertexIndex[i]]);
		triangle->m_vertex.push_back(vertex[vertexIndex[i + 1]]);
		triangle->m_vertex.push_back(vertex[vertexIndex[i + 2]]);

		//		頂点をプッシュbackする
		m_triangle.push_back(std::move(triangle));

		//		3つの頂点分進める
		i = i + 2;
	}
}

void LeadMesh::CreateNormalize()
{
	for (int i = 0, max = static_cast<int>(m_triangle.size());
		i < max; ++i)
	{
		DirectX::SimpleMath::Vector3 velocity1 = m_triangle[i]->m_vertex[1] - m_triangle[i]->m_vertex[0];
		DirectX::SimpleMath::Vector3 velocity2 = m_triangle[i]->m_vertex[2] - m_triangle[i]->m_vertex[0];

		//		外積から法線を求める
		DirectX::SimpleMath::Vector3 cross = velocity1.Cross(velocity2);

		//		正規化
		cross.Normalize();

		//		法線を設定する
		m_triangle[i]->m_normalVector = cross;
	}
}
