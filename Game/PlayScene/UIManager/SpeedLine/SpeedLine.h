

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
	void Update();

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
	};

private:

	const float LINE_LENGTH = 0.1f;

	const float SPEED = 2.0f;

private:

	//		UIマネージャのインスタンスのポインタ
	UIManager* m_uiManager;

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_shader;
	
	//		コンストバッファ
	ConstBuffer buffer;

	//		時間
	float m_time;

	float m_frontTime;

	bool frontFlag;
};