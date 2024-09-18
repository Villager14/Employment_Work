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

#include "Game/PlayScene/ObjectManager/WireObject/WireObjectInformation.h"

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

	//		ワイヤーの情報
	std::vector<WireObjectInformation>* m_wireInformation;

public:

	void SetWireInformation(std::vector<WireObjectInformation>* wire) { m_wireInformation = wire; }
};
