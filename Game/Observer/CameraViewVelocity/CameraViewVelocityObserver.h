/*
* @file		CameraViewVelocityObserver.h
* @brief	カメラのビューベクトルオブザーバー
* @author	Morita
* @date		2024/12/16
*/

#pragma once

#include "ICameraViewVelocityObserver.h"

class CameraViewVelocityObserver
{
public:

	//		コンストラクタ
	CameraViewVelocityObserver();

	//		デストラクタ
	~CameraViewVelocityObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(ICameraViewVelocityObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(ICameraViewVelocityObserver* observer);

	/*
	*	カメラのViewベクトル
	* 
	*	@param	(velocity)	カメラのViewベクトル
	*/
	void CameraViewVelocity(DirectX::SimpleMath::Vector3 velocity);

	/*
	*	カメラのView
	*
	*	@param	(view)	カメラのView
	*/
	void CameraView(DirectX::SimpleMath::Vector3 view);

	/*
	*	カメラのUp
	* 
	*	@param	(up)	カメラのUp
	*/
	void CameraUp(DirectX::SimpleMath::Vector3 up);

	//		全削除
	void Dalete();
private:

	std::vector<ICameraViewVelocityObserver*> m_observer;

};