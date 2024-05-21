/*
* @file		PlayerCameraManager.h
* @brief	プレイヤーのカメラのマネージャー
* @author	Morita
* @date		2024/05/08
*/

#pragma once

#include "IPlayerCamera.h"

#include "State/DebugCamera.h"
#include "State/PlayerCamera.h"
#include "State/PlayerWallWalkCamera.h"

#include "Game/PlayScene/Player/PlayerInformationCamera.h"


class DebugCamera;
class PlayerCamera;
class PlayerWallWalkCamera;

class PlayerCameraManager
{
public:
	//		コンストラクタ
	PlayerCameraManager();

	//		デストラクタ
	~PlayerCameraManager();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	* 
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void Update(PlayerInformationCamera* playerInformationCamera);

	//		終了処理
	void Finalize();

	//		カメラの移動処理
	void CameraMove();

	/*
	*	状態を切り替える
	* 
	*	@param	(state)	新しい状態
	*/
	void ChangeState(IPlayerCamera* state);

	//		視野角
	void ViewingAngle();

private:

	//		状態
	IPlayerCamera* m_state;

	//		デバックカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	//		プレイヤーカメラ
	std::unique_ptr<PlayerCamera> m_playerCamera;

	//		壁を走るカメラ
	std::unique_ptr<PlayerWallWalkCamera> m_playerWallWalkCamera;

public:
	/*
	*	デバックカメラの状態を受け取る
	* 
	*	@return デバックカメラのインスタンスのポインタ
	*/
	DebugCamera* GetDebugCamera() { return m_debugCamera.get(); }

	/*
	*	プレイヤーカメラの状態を受け取る
	* 
	*	@return プレイヤーカメラのインスタンスのポインタ
	*/
	PlayerCamera* GetPlayerCamera() { return m_playerCamera.get(); }

	/*
	*	壁走りカメラの状態を受け取る
	* 
	*	@return プレイヤー壁走りのインスタンスのポインタ
	*/
	PlayerWallWalkCamera* GetWallWalkCamera() { return m_playerWallWalkCamera.get(); }

private:

	//		最大角度Y
	const float ANGLE_Y_MAX = 50.0f;

	//		最小角度Y
	const float ANGLE_Y_MIN = -50.0f;

	//		カメラの速度
	const float CAMERA_SPEED = 5.0f;

private:

	//		カメラ用プレイヤーの情報
	PlayerInformationCamera* m_playerInformationCamera;

		//		カメラの角度
	DirectX::SimpleMath::Vector2 m_angle;
	
	//		視線ベクトル
	DirectX::SimpleMath::Vector3 m_viewVelocity;
	
public:

	/*
	*	カメラの角度を受けとる
	* 
	*	@return 角度
	*/
	const DirectX::SimpleMath::Vector2 GetAngle() { return m_angle; }

	/*
	*	カメラの角度を設定する
	* 
	*	@param	(angle)	角度
	*/
	void SetAngle(DirectX::SimpleMath::Vector2 angle) { m_angle = angle; }

	/*
	*	視線ベクトルを設定する
	* 
	*	@param	(velocity)	ベクトル
	*/
	void SetViewVelocity(const DirectX::SimpleMath::Vector3& velicity) { m_viewVelocity = velicity; }

	/*
	*	視線ベクトルを受け取る
	* 
	*	@return ベクトル
	*/
	const DirectX::SimpleMath::Vector3& GetViewVelocity() { return m_viewVelocity; }

	/*
	*	カメラ用のプレイヤーの情報を受け取る
	* 
	*	@return カメラ情報
	*/
	PlayerInformationCamera* GetPlayerInformationCamera() { return m_playerInformationCamera; }
};
