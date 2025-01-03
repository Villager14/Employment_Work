/*
* @file		MenuSummarizeColliderInformation.h
* @brief	メニューの当たり判定情報をまとめる
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "../../Collider/MenuColliderInformation.h"

class MenuSummarizeColliderInformation
{
public:

	MenuSummarizeColliderInformation();

	~MenuSummarizeColliderInformation();

	/*
	*	当たり判定の追加
	* 
	*	@param	(information)	当たり判定情報
	*/
	void AddCollider(std::vector<MenuColliderInformation> information);

	/*
	*	当たり判定の削除
	* 
	*	@param	(information)	当たり判定の削除
	*/
	void DeleteCollider(std::vector<MenuColliderInformation> information);

private:


	std::unordered_map<UISubType, MenuColliderInformation> m_information;

	std::vector<MenuColliderInformation> m_colliderInformation;

public:

	const std::vector<MenuColliderInformation>& GetInformation() { return m_colliderInformation; }
};