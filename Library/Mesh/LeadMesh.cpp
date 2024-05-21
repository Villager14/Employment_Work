/*
* @file		LeadMesh.cpp
* @brief	���b�V���̓ǂݍ���
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
	//		���_
	std::vector<DirectX::SimpleMath::Vector3> vertex;

	//		���_�C���f�b�N�X
	std::vector<int> vertexIndex;

	//		�t�@�C�����J��
	std::ifstream ifs(filePath);

	std::string str;

	while (std::getline(ifs, str))
	{
		//		���_�̏ꍇ
		if (str[0] == 'v' && str[1] == ' ')
		{
			DirectX::SimpleMath::Vector3 val;

			//		�t�@�C������󂯂Ƃ����l��float�֕ϊ�&�������
			sscanf_s(str.data(), "v %f %f %f", &val.x, &val.y, &val.z);

			//		���_���󂯎��
			vertex.push_back(val);
		}

		//		�C���f�b�N�X�̏ꍇ
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

	//		�t�@�C�������
	ifs.close();

	//		�O�p�`���b�V���̍쐻
	CreateTrinangle(vertex, vertexIndex);

	//		�@�����쐬
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

		//		���_��������
		triangle->m_vertex.push_back(vertex[vertexIndex[i]]);
		triangle->m_vertex.push_back(vertex[vertexIndex[i + 1]]);
		triangle->m_vertex.push_back(vertex[vertexIndex[i + 2]]);

		//		���_���v�b�V��back����
		m_triangle.push_back(std::move(triangle));

		//		3�̒��_���i�߂�
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

		//		�O�ς���@�������߂�
		DirectX::SimpleMath::Vector3 cross = velocity1.Cross(velocity2);

		//		���K��
		cross.Normalize();

		//		�@����ݒ肷��
		m_triangle[i]->m_normalVector = cross;
	}
}
