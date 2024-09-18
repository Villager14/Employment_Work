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
	//		���b�V���̐����N���X�̐���
	m_origanization = std::make_unique<MeshOrganization>();
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

	std::vector<Triangle> triangle;

	triangle = m_origanization->Organization(vertex, vertexIndex);

	return std::move(triangle);
}