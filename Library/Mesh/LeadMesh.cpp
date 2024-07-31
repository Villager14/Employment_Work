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

#include <algorithm>

LeadMesh::LeadMesh()
{
}

LeadMesh::~LeadMesh()
{
}

std::vector<Triangle> LeadMesh::Lead
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

	//		オブジェクトごとの情報にする
	ObjectInformation();

	return std::move(m_triangle);
}

void LeadMesh::CreateTrinangle(
	const std::vector<DirectX::SimpleMath::Vector3>& vertex,
	const std::vector<int> vertexIndex)
{
	for (int i = 0; i < vertexIndex.size(); ++i)
	{
		Triangle triangle; 

		for (int j = 0; j < 3; j++)
		{
			//		頂点インデックス
			triangle.m_vertexIndex.push_back(vertexIndex[i + j]);

			//		頂点
			triangle.m_vertex.push_back(vertex[triangle.m_vertexIndex[j]]);
		}

		//		頂点をプッシュbackする
		m_triangle.push_back(triangle);

		//		3つの頂点分進める
		i = i + 2;
	}
}

void LeadMesh::CreateNormalize()
{
	for (int i = 0, max = static_cast<int>(m_triangle.size());
		i < max; ++i)
	{
		DirectX::SimpleMath::Vector3 velocity1 = m_triangle[i].m_vertex[1] - m_triangle[i].m_vertex[0];
		DirectX::SimpleMath::Vector3 velocity2 = m_triangle[i].m_vertex[2] - m_triangle[i].m_vertex[0];

		//		外積から法線を求める
		DirectX::SimpleMath::Vector3 cross = velocity1.Cross(velocity2);

		//		正規化
		cross.Normalize();

		//		法線を設定する
		m_triangle[i].m_normalVector = cross;
	}
}

void LeadMesh::ObjectInformation()
{
	m_copytriangle = m_triangle;

	AddObject();

	//		最初の要素を削除する
	m_copytriangle.erase(m_copytriangle.begin());


	for (;;)
	{
		for (int i = 0; i < m_copytriangle.size(); ++i)
		{
			if (Sort(i)) i--;
		}

		if (m_copytriangle.size() != 0)
		{
			codNumber.clear();
			
			AddObject();

			//		最初の要素を削除する
			m_copytriangle.erase(m_copytriangle.begin());
		}
		else
		{
			//		頂点インデックスの情報を削除する
			ClearVertexIndex();

			//		オブジェクトの半径を作成する
			CreateRadius();

			break;
		}
	}
}

bool LeadMesh::Sort(int index)
{
	for (int i = 0; i < 3; ++i)
	{
		if (std::find(codNumber.begin(), codNumber.end(),
			m_copytriangle[index].m_vertexIndex[i]) !=
			codNumber.end())
		{
			m_object[static_cast<int>(m_object.size()) - 1].push_back(m_copytriangle[index]);

			AddCodNumber(index);

			m_copytriangle.erase(m_copytriangle.begin() + index);

			return true;
		}
	}

	return false;
}

void LeadMesh::AddCodNumber(int index)
{
	std::vector<int> result;

	std::sort(codNumber.begin(), codNumber.end());
	std::sort(m_copytriangle[index].m_vertexIndex.begin(), m_copytriangle[index].m_vertexIndex.end());

	std::set_difference(m_copytriangle[index].m_vertexIndex.begin(),
		m_copytriangle[index].m_vertexIndex.end(),
		codNumber.begin(),
		codNumber.end(),
		std::back_inserter(result));

	for (int i = 0; i < result.size(); ++i)
	{
		codNumber.push_back(result[i]);
	}
}

void LeadMesh::AddObject()
{
	for (int i = 0; i < 3; ++i)
	{
		codNumber.push_back(m_copytriangle[0].m_vertexIndex[i]);
	}

	std::vector<Triangle> triangle;

	triangle.push_back(m_copytriangle[0]);

	m_object.insert({ m_object.size(), triangle });
}

void LeadMesh::ClearVertexIndex()
{
	for (auto& e : m_object)
	{
		for (int i = 0; i < e.second.size(); ++i)
		{
			e.second[i].m_vertexIndex.clear();
		}
	}
}

void LeadMesh::CreateRadius()
{
	for (auto& e : m_object)
	{
		std::vector<DirectX::SimpleMath::Vector3> m_max;
		std::vector<DirectX::SimpleMath::Vector3> m_min;

		for (int i = 0; i < e.second.size(); ++i)
		{
			m_max.push_back(ObjectMax(e.second[i].m_vertex));
			m_min.push_back(ObjectMin(e.second[i].m_vertex));
		}

		//		オブジェクトの長さ
		Objectlength(ObjectMax(m_max), ObjectMin(m_min));
	}
}

DirectX::SimpleMath::Vector3 LeadMesh::ObjectMax(std::vector<DirectX::SimpleMath::Vector3> max)
{
	auto maxZ = std::max_element(max.begin(), max.end(),
		[&](const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b)
		{
			return a.x < b.x;
		});

	auto maxy = std::max_element(max.begin(), max.end(),
		[&](const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b)
		{
			return a.y < b.y;
		});

	auto maxz = std::max_element(max.begin(), max.end(),
		[&](const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b)
		{
			return a.z < b.z;
		});
	
	return { maxZ->x, maxy->y, maxz->z };
}

DirectX::SimpleMath::Vector3 LeadMesh::ObjectMin(std::vector<DirectX::SimpleMath::Vector3> min)
{
	auto minx = std::min_element(min.begin(), min.end(),
		[](const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b)
		{
			return a.x < b.x;
		});

	auto miny = std::min_element(min.begin(), min.end(),
		[](const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b)
		{
			return a.y < b.y;
		});

	auto minz = std::min_element(min.begin(), min.end(),
		[](const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b)
		{
			return a.z < b.z;
		});

	return { minx->x, miny->y, minz->z };
}

void LeadMesh::Objectlength(DirectX::SimpleMath::Vector3 max, DirectX::SimpleMath::Vector3 min)
{
	//		メッシュの中心
	m_meshCenter.push_back((max + min) / 2.0f);

	//		長さを求める
	float length = (max - min).Length();

	//		半径が欲しいので計算する
	length /= 2.0f;

	m_meshLength.push_back(length);
}
