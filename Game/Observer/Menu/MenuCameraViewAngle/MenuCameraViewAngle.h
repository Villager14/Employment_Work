/*
* @file		MenuCameraViewAngle.h
* @brief	メニューのカメラの視野角を受け取るオブザーバー
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "IMenuCameraViewAngle.h"

class MenuCameraViewAngle
{
public:

	//		コンストラクタ
	MenuCameraViewAngle();

	//		デストラクタ
	~MenuCameraViewAngle();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(IMenuCameraViewAngle* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(IMenuCameraViewAngle* observer);

	//		メニューのカメラの視野角を受け取る
	void GetMenuCameraViewAngle(float angle);

	//		全削除
	void Dalete();
private:

	std::vector<IMenuCameraViewAngle*> m_observer;

};