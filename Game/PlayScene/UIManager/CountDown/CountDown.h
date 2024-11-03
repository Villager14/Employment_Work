/*
* @file		CountDown.h
* @brief	カウントダウンの処理
* @author	Morita
* @date		2024/11/01
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/UIRenderManager.h"

class CountDown
{
public:

	CountDown();

	~CountDown();

	void Initialize();

	void Update(float time);

	void Render();

	void Finalize();

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		int time = 0;
		DirectX::SimpleMath::Vector3 pad;
		float alpha = 0.0f;
		DirectX::SimpleMath::Vector3 pad2;
	};

private:

	//		時間
	float m_time;
	
	//		アルファ
	float m_alpha;

	//		コンストバッファ
	ConstBuffer buffer;

	//		フェードの描画
	std::unique_ptr<UIRenderManager> m_numberAlpha;
};
