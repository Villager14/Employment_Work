

#pragma once

#include "../UIManager.h"

#include "Library/Shader/UIRenderManager.h"

class SpeedLine
{
public:

	SpeedLine(UIManager* uiManager);

	~SpeedLine();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update(float speed);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		アスペクト比
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		回転行列
		DirectX::SimpleMath::Vector4 time;				//		時間
		float backTime = 0.0f;
		DirectX::SimpleMath::Vector3 pad;
		float alphaPower = 0.0f;
		DirectX::SimpleMath::Vector3 pad2;
	};

private:

	const float LINE_LENGTH = 0.1f;

	//		最低速度
	const float MINIMUM_SPEED = 40.0f;

	//		最高速度
	const float MAXIMUM_SPEED = 110.0f;

	//		最低アルファパワー
	const float MIN_ALPHA_POWER = 0.5f;

	//		最高アルファパワー
	const float MAX_ALPHA_POWER = 0.7f;

	//		レイ最低速度
	const float RAY_SPEED_MIN = 1.5f;

	//		レイ最高速度
	const float RAY_SPEED_MAX = 3.0f;

	//		背景速度
	const float BACK_SPEED = 0.1f;

	//		UI速度テクスチャパス
	const wchar_t* UI_SPEED_TEXTURE_PATH = L"Resources/Texture/UI/Speed/UISpeed.png";

	//		速度ラインVSパス
	const wchar_t* SPEED_LINE_VS_PATH = L"Resources/Shader/UI/SpeedLine/SpeedLineVS.cso";

	//		速度ラインGSパス
	const wchar_t* SPEED_LINE_GS_PATH = L"Resources/Shader/UI/SpeedLine/SpeedLineGS.cso";

	//		速度ラインPSパス
	const wchar_t* SPEED_LINE_PS_PATH = L"Resources/Shader/UI/SpeedLine/SpeedLinePS.cso";

	//		スピードテクスチャパス
	const wchar_t* SPEED_TEXTURE_PATH = L"Resources/Texture/UI/Speed/Speed01.png";

private:

	//		UIマネージャのインスタンスのポインタ
	UIManager* m_uiManager;

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_shader;
	
	//		コンストバッファ
	ConstBuffer buffer;

	//		時間
	float m_time;

	//		前時間
	float m_frontTime;

	//		後ろ時間
	bool frontFlag;

	//		速度
	float m_speed;

	//		背景の速度
	float m_backTime;

	//		プレイヤーの速度
	float m_playerSpeed;
};