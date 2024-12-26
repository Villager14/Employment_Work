/*
* @file		IMenuColliderObserver.h
* @brief	メニューの当たり判定オブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/22
*/
#pragma once

#include "pch.h"

#include "../../Collider/MenuColliderInformation.h"

class IMenuColliderObserver
{
public:

	//		デストラクタ
	~IMenuColliderObserver() = default;

	/*
	*	当たったUIのタイプ
	* 
	*	@param	(type)	UIのタイプ
	*/
	virtual void HitUIType(UISubType type) = 0;
};