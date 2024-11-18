/*
* @file		BackGroundMove.h
* @brief	背景の移動
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class BackGroundMove
{
public:

	//		コンストラクタ
	BackGroundMove();

	//		デストラクタ
	~BackGroundMove();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		ウィンドウサイズ
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		回転行列
		DirectX::SimpleMath::Vector4 time;				//		時間
	};

private:

	//		背景の速度
	const float BACK_GROUND_SPEED = 0.1f;

	//		背景テクスチャのファイルパス
	const wchar_t* BACK_GROUND_TEXTURE_PATH = L"Resources/Texture/TitleScene/TitleBack.png";

	//		背景移動VSパス
	const wchar_t* BACK_GROUND_VS_PATH = L"Resources/Shader/UI/BackGroundMove/BackGroundMoveVS.cso";

	//		背景移動GSパス
	const wchar_t* BACK_GROUND_GS_PATH = L"Resources/Shader/UI/BackGroundMove/BackGroundMoveGS.cso";

	//		背景移動PSパス
	const wchar_t* BACK_GROUND_PS_PATH = L"Resources/Shader/UI/BackGroundMove/BackGroundMovePS.cso";

private:

	//		UI描画マネージャー
	std::unique_ptr<UIRenderManager> m_uiRenderManager;

	//		時間
	float m_time;

	//		コンストバッファ
	ConstBuffer buffer;
};
