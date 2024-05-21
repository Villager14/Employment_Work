/*
* @file		PlayerInformationCamera
* @brief	カメラ用プレイヤーの情報
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "pch.h"

class PlayerInformationCamera
{
public:
	//		コンストラクタ
	PlayerInformationCamera()
		:
		m_headWallMove(0.0f)
	{};

	//		デストラクタ
	~PlayerInformationCamera() {};


private:
	//		加速度
	DirectX::SimpleMath::Vector3 m_acceleration;

	//		プレイヤーの高さ
	DirectX::SimpleMath::Vector3 m_playerHeight;

	//		壁移動時の法線
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;

	//		頭の動き
	float m_headWallMove;

public:

	/*
	*	プレイヤーの加速度を受け取る
	*
	*	@return 加速度
	*/
	const DirectX::SimpleMath::Vector3& GetAcceleration() { return m_acceleration; }

	/*
	*	プレイヤーの座標を設定する
	*
	*	@param	(acceleration)	加速度
	*/
	void SetAccelaration(DirectX::SimpleMath::Vector3 acceleration) { m_acceleration = acceleration; }

	/*
	*	プレイヤーの高さを受け取る
	*
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerHeight() { return m_playerHeight; }

	/*
	*	プレイヤーの高さを設定する
	*
	*	@param	(position)	座標
	*/
	void SetPlayerHeight(DirectX::SimpleMath::Vector3 position) { m_playerHeight = position; }

	/*
	*	壁移動時の法線を受け取る
	*
	*	@return 法線
	*/
	const DirectX::SimpleMath::Vector3& GetWallWalkNormalize() { return m_wallWalkNormalize; }

	/*
	*	壁移動時の法線を設定する
	*
	*	@param	(normalize)	法線
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	頭の動きを受け取る
	*
	*	@return 移動量
	*/
	float GetHeadMove() { return m_headWallMove; }

	/*
	*	頭の動きを設定する
	*
	*	@parma	移動量
	*/
	void SetHeadMove(float headWallMove) { m_headWallMove = headWallMove; }

};
