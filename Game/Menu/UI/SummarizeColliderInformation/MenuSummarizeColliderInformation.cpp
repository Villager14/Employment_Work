/*
* @file		MenuSummarizeColliderInformation.cpp
* @brief	ƒƒjƒ…[‚Ì“–‚½‚è”»’èî•ñ‚ğ‚Ü‚Æ‚ß‚é
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
		//	ŒŸõ‚µ‚Ä‚È‚©‚Á‚½ê‡ˆ—‚ğ‚µ‚È‚¢
		if (m_information.find(information[i].subType) == m_information.end())
		{
			continue;
		}

		//		íœ‚·‚é
		m_information.erase(information[i].subType);
	}

	//		‚·‚×‚Äíœ‚·‚é
	m_colliderInformation.clear();

	//		’Ç‰Á‚·‚é
	for (const auto& e : m_information)
	{
		m_colliderInformation.push_back(e.second);
	}
}
