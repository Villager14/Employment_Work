/*
* @file		MenuCameraSpeed.cpp
* @brief	メニューのカメラの速度を受け取るオブザーバー
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "IMenuCameraSpeed.h"

class MenuCameraSpeed
{
public:

	//		コンストラクタ
	MenuCameraSpeed();

	//		デストラクタ
	~MenuCameraSpeed();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuCameraSpeed* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuCameraSpeed* observer);

	//		メニューのカメラの速度
	void GetMenuCameraSpeed(float speed);

	//		全削除
	void Dalete();
private:

	std::vector<IMenuCameraSpeed*> m_observer;

};