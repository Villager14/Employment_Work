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
#include "State/PlayerStartCamera.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "PlayerCameraInformation.h"

class DebugCamera;
class PlayerCamera;
class PlayerWallWalkCamera;
class PlayerStartCamera;

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
	void Update(PlayerInformation* playerInformation);

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

	//		プレイヤースタートカメラ
	std::unique_ptr<PlayerStartCamera> m_playerStartCamera;

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

	/*
	*	スタートカメラ状態を受け取る	
	* 
	*	@return プレイヤースタートカメラのインスタンスのポインタ
	*/
	PlayerStartCamera* GetStartCamera() { return m_playerStartCamera.get(); }

private:
	//		カメラの情報
	std::unique_ptr<PlayerCameraInformation> m_information;

	//		カメラ用プレイヤーの情報
	PlayerInformation* m_playerInformation;
	
public:

	/*
	*	カメラの情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	PlayerCameraInformation* GetInformation() { return m_information.get(); }
	
	/*
	*	プレイヤーの情報を受け取る
	* 
	*	@return プレイヤーの情報
	*/
	PlayerInformation* GetPlayerInformationCamera() { return m_playerInformation; }
};
