/*
* @file		EffectManager.h
* @brief	エフェクトマネージャー
* @author	Morita
* @date		2024/06/10
*/

#pragma once

#include "WireUseEffect/WireUseEffect.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "../Player/PlayerInformation.h"

class EffectManager
{
public:

	//		コンストラクタ
	EffectManager(PlayerInformation* playerInformation);

	//		デストラクタ
	~EffectManager();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	*
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void Update(PlayerCameraInformation* cameraInformation);

	/*
	*	描画処理
	*
	*	@param	(cameraVelocity)	視線ベクトル
	*/
	void Render();

	//		終了処理
	void Finalize();

private:

	//		ワイヤーエフェクト
	std::unique_ptr<WireUseEffect> m_wireUseEffect;

	//		プレイヤーの情報
	PlayerInformation* m_playerInformation;

	std::vector<DirectX::SimpleMath::Vector3> m_wirePosition;

public:

	void SetWirePosition(const std::vector<DirectX::SimpleMath::Vector3>& position) { m_wirePosition = position; }
};
