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

	//		�I�u�W�F�N�g���Ƃ̏��ɂ���
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
			//		���_�C���f�b�N�X
			triangle.m_vertexIndex.push_back(vertexIndex[i + j]);

			//		���_
			triangle.m_vertex.push_back(vertex[triangle.m_vertexIndex[j]]);
		}

		//		���_���v�b�V��back����
		m_triangle.push_back(triangle);

		//		3�̒��_���i�߂�
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

		//		�O�ς���@�������߂�
		DirectX::SimpleMath::Vector3 cross = velocity1.Cross(velocity2);

		//		���K��
		cross.Normalize();

		//		�@����ݒ肷��
		m_triangle[i].m_normalVector = cross;
	}
}

void LeadMesh::ObjectInformation()
{
	m_copytriangle = m_triangle;

	AddObject();

	//		�ŏ��̗v�f���폜����
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

			//		�ŏ��̗v�f���폜����
			m_copytriangle.erase(m_copytriangle.begin());
		}
		else
		{
			//		���_�C���f�b�N�X�̏����폜����
			ClearVertexIndex();

			//		�I�u�W�F�N�g�̔��a���쐬����
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

		//		�I�u�W�F�N�g�̒���
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
	//		���b�V���̒��S
	m_meshCenter.push_back((max + min) / 2.0f);

	//		���������߂�
	float length = (max - min).Length();

	//		���a���~�����̂Ōv�Z����
	length /= 2.0f;

	m_meshLength.push_back(length);
}
