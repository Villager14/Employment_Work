/*
* @file		WireUseEffect.h
* @brief	ワイヤー使用エフェクト
* @author	Morita
* @date		2024/06/10
*/

#pragma once

#include "../Billboard/BillboardEffect.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

class WireUseEffect
{
public:

	//		コンストラクタ
	WireUseEffect(PlayerInformation* m_playerInformation);

	//		デストラクタ
	~WireUseEffect();

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
	void Render(DirectX::SimpleMath::Vector3 position);

	//		終了処理
	void Finalize();

private:
	//		ビルボードエフェクト
	std::unique_ptr<BillboardEffect> m_billboardEffect;

	//		プレイヤーの情報
	PlayerInformation* m_playerInformation;
};
