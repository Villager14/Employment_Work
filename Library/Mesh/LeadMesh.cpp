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
			m_object[m_object.size() - 1].push_back(m_copytriangle[index]);

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
