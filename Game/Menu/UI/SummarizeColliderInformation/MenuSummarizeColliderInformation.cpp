/*
* @file		MenuSummarizeColliderInformation.cpp
* @brief	メニューの当たり判定情報をまとめる
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
		//	検索してなかった場合処理をしない
		if (m_information.find(information[i].subType) == m_information.end())
		{
			continue;
		}

		//		削除する
		m_information.erase(information[i].subType);
	}

	//		すべて削除する
	m_colliderInformation.clear();

	//		追加する
	for (const auto& e : m_information)
	{
		m_colliderInformation.push_back(e.second);
	}
}
