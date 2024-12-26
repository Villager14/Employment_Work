/*
* @file		MenuSummarizeColliderInformation.cpp
* @brief	���j���[�̓����蔻������܂Ƃ߂�
* @author	Morita
* @date		2024/12/23
*/

#include "pch.h"

#include "MenuSummarizeColliderInformation.h"

MenuSummarizeColliderInformation::MenuSummarizeColliderInformation()
{
}

MenuSummarizeColliderInformation::~MenuSummarizeColliderInformation()
{
}

void MenuSummarizeColliderInformation::AddCollider(std::vector<MenuColliderInformation> information)
{
	for (int i = 0; i < information.size(); ++i)
	{
		m_information.insert({information[i].subType, information[i]});
	}

	m_colliderInformation.clear();

	for (const auto& e : m_information)
	{
		m_colliderInformation.push_back(e.second);
	}
}

void MenuSummarizeColliderInformation::DeleteCollider(std::vector<MenuColliderInformation> information)
{
	for (int i = 0; i < information.size(); ++i)
	{
		//	�������ĂȂ������ꍇ���������Ȃ�
		if (m_information.find(information[i].subType) == m_information.end())
		{
			continue;
		}

		//		�폜����
		m_information.erase(information[i].subType);
	}

	//		���ׂč폜����
	m_colliderInformation.clear();

	//		�ǉ�����
	for (const auto& e : m_information)
	{
		m_colliderInformation.push_back(e.second);
	}
}
