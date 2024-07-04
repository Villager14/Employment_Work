/*
* @file		BackGroundMove.h
* @brief	背景の移動
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/UIRenderManager.h"

class BackGroundMove
{
public:

	BackGroundMove();

	~BackGroundMove();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

private:

	//		UI描画マネージャー
	std::unique_ptr<UIRenderManager> m_uiRenderManager;

	//		時間
	float m_time;

	//		フェードインをするかどうか判断する
	bool m_fadeinResetJudgement;

	//		フェードアウトをするかどうか判断する
	bool m_fadeoutResetJudgement;

	ConstBuffer buffer;
};
