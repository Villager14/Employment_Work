/*
* @file		TitleEffectManager.cpp
* @brief	タイトルエフェクトマネージャー
* @author	Morita
* @date		2024/12/13
*/

#pragma once

#include "Effect/Effect/DigitalRain/DegitalRain.h"

#include "Game/Observer/CameraViewVelocity/ICameraViewVelocityObserver.h"

class TitleEffectManager : public ICameraViewVelocityObserver
{
public:

	//		コンストラクタ
	TitleEffectManager();

	//		デストラクタ
	~TitleEffectManager();

	//		初期化処理
	void Initialize();
	
	//		更新処理
	void Update();

	//		描画処理
	void Render(PostEffectFlag::Flag flag);

	//		終了処理
	void Finalize();

	//		カメラのビューベクトル
	void CameraViewVelocity(DirectX::SimpleMath::Vector3 velocity) override;

	//		カメラのビュー
	void CameraView(DirectX::SimpleMath::Vector3 view) override;

	//		カメラのアップ
	void CameraUp(DirectX::SimpleMath::Vector3 up) override;

private:

	//		デジタル雨
	std::unique_ptr<DegitalRain> m_degitalRain;

};