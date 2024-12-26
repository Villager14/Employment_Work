/*
* @file		MenuSummarizeColliderInformation.h
* @brief	���j���[�̓����蔻������܂Ƃ߂�
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
	*	�����蔻��̒ǉ�
	* 
	*	@param	(information)	�����蔻����
	*/
	void AddCollider(std::vector<MenuColliderInformation> information);

	/*
	*	�����蔻��̍폜
	* 
	*	@param	(information)	�����蔻��̍폜
	*/
	void DeleteCollider(std::vector<MenuColliderInformation> information);

private:


	std::unordered_map<UISubType, MenuColliderInformation> m_information;

	std::vector<MenuColliderInformation> m_colliderInformation;

public:

	const std::vector<MenuColliderInformation>& GetInformation() { return m_colliderInformation; }
};