/*
* @file		IMenuColliderObserver.h
* @brief	���j���[�̓����蔻��I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/22
*/
#pragma once

#include "pch.h"

#include "../../Collider/MenuColliderInformation.h"

class IMenuColliderObserver
{
public:

	//		�f�X�g���N�^
	~IMenuColliderObserver() = default;

	/*
	*	��������UI�̃^�C�v
	* 
	*	@param	(type)	UI�̃^�C�v
	*/
	virtual void HitUIType(UISubType type) = 0;
};