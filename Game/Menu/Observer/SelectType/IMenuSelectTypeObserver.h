/*
* @file		iMenuSelectTypeObserver.h
* @brief	���j���[�̑I���^�C�v�I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/19
*/
#pragma once

#include "pch.h"

#include "../../UI/MenuUITabEnums.h"

class IMenuSelectTypeObserver
{
public:

	//		�f�X�g���N�^
	~IMenuSelectTypeObserver() = default;

	/*
	*	�I���^�C�v
	* 
	*	@param	(type)�@�^�C�v
	*/
	virtual void SelectType(MenuUITaype::UIType type) = 0;
};