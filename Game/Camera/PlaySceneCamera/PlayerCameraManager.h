/*
* @file		PlayerCameraManager.h
* @brief	プレイヤーのカメラのマネージャー
* @author	Morita
* @date		2024/05/08
*/

#pragma once

#include "IPlayerCamera.h"

#include "PlayerCameraInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/PlayScene/Player/Observer/HeightObserver/IPHeightObserver.h"

#include "Game/PlayScene/Player/Observer/SpeedObserver/IPSpeedObserver.h"

#include "Game/PlayScene/Player/Observer/PCameraObserver/IPCameraObserver.h"

#include "Game/Observer/CameraViewVelocity/CameraViewVelocityObserver.h"

#include <unordered_map>

class PlayerCameraManager : public IPHeightObserver,
							public IPSpeedObserver,
							public IPCameraObserver
{
public:
	//		コンストラクタ
	PlayerCameraManager(GameManager* gameManager);

	//		デストラクタ
	~PlayerCameraManager();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	* 
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void Update();

	//		終了処理
	void Finalize();

	//		カメラの移動処理
	void CameraMove();

	//		視野角
	void ViewingAngleUpdate();

	/*
	*	プロジェクトションの作製
	* 
	*	@param	(fov)			視野角
	*	@param	(nearPlane)　	最短視野距離
	*	@param	(farPlane)		最長視野距離
	*/
	void CreateProj(float fov, float nearPlane, float farPlane);

	//		eyeの作製
	void CreateEye(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY);

	//		視点の揺れ
	void ShakingView();

	//		横揺れ
	void HorizontalShaking();

	//		縦揺れ
	void VerticalShaking();

	void PlayerHeght(DirectX::SimpleMath::Vector3 height) override;

	void NowSpeed(float speed) override;

	void ShakeHead() override;

	void CameraStop() override;

	void WallWalkMove(float height) override;

	void Direction(DirectX::SimpleMath::Vector3 direction) override;

	void WallNormalize(DirectX::SimpleMath::Vector3 noramlize) override;

public:

	//		カメラのタイプ
	enum CameraType
	{
		Debug,
		Standard,
		WallWalk,
		Start,
		Stop,
		Goal,
		Death,
	};

private:

	//		状態
	IPlayerCamera* m_state;

	//		カメラの情報
	std::unique_ptr<PlayerCameraInformation> m_information;
	
	//		ゲームマネージャー
	GameManager* m_gameManager;

	//		派生クラスの格納
	std::unordered_map<CameraType, std::unique_ptr<IPlayerCamera>> m_stateInformation;

	//		カメラのビューVelocityオブザーバー
	std::unique_ptr<CameraViewVelocityObserver> m_cameraViewVelocityObserver;

	//		現在のカメラタイプ
	CameraType m_cameraType;

	//		揺れ時間
	float m_shakingTime;

	//		頭を振る割合
	float m_shakingRatio;

	//		頭を動かす速度
	float m_shakingSpeed;

public:
	/*
	*	カメラの状態の切り替え
	* 
	*	@param	(type)	カメラの種類
	*/
	void ChangeState(CameraType type);


	/*
	*	ゲームマネージャーを受け取る
	* 
	*	@return ゲームマネージャーのインスタンスのポインタ
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	/*
	*	カメラの情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	PlayerCameraInformation* GetInformation() { return m_information.get(); }
	
	/*
	*	オブザーバーの追加
	* 
	*	@param	(observer)	オブザーバーのポインタのインスタンス
	*/
	void AddCameraObserver(ICameraViewVelocityObserver* observer) { m_cameraViewVelocityObserver->AddObserver(observer); }
};
