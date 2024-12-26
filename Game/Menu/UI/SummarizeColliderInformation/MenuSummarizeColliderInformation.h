/*
* @file		MenuSummarizeColliderInformation.h
* @brief	ƒƒjƒ…[‚Ì“–‚½‚è”»’èî•ñ‚ğ‚Ü‚Æ‚ß‚é
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
	*	“–‚½‚è”»’è‚Ì’Ç‰Á
	* 
	*	@param	(information)	“–‚½‚è”»’èî•ñ
	*/
	void AddCollider(std::vector<MenuColliderInformation> information);

	/*
	*	“–‚½‚è”»’è‚Ìíœ
	* 
	*	@param	(information)	“–‚½‚è”»’è‚Ìíœ
	*/
	void DeleteCollider(std::vector<MenuColliderInformation> information);

private:


	std::unordered_map<UISubType, MenuColliderInformation> m_information;

	std::vector<MenuColliderInformation> m_colliderInformation;

public:

	const std::vector<MenuColliderInformation>& GetInformation() { return m_colliderInformation; }
};