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

public:

	//		カウントダウンの座標
	const DirectX::SimpleMath::Vector2 COUNT_DOWN_POSITION = { 640.0f, 360.0f };

	//		カウントダウンの最高時間
	const float MAX_TIME = 6.0f;

	//		カウントダウンの最低時間
	const float MIN_TIME = 1.0f;

	//		カウントダウンテクスチャパス
	const wchar_t* COUNT_DOWN_TEXTURE_PATH = L"Resources/Texture/UI/CountDown/CountDown.png";
	
	//		番号透明度VSパス
	const wchar_t* NUMBER_ALPHA_VS_PATH = L"Resources/Shader/UI/NumberAlpha/NumberAlphaVS.cso";

	//		番号透明度GSパス
	const wchar_t* NUMBER_ALPHA_GS_PATH = L"Resources/Shader/UI/NumberAlpha/NumberAlphaGS.cso";

	//		番号透明度PSパス
	const wchar_t* NUMBER_ALPHA_PS_PATH = L"Resources/Shader/UI/NumberAlpha/NumberAlphaPS.cso";

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
