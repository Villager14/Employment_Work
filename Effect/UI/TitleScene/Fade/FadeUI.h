/*
* @file		FadeUI.h
* @brief	フェードUI
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class FadeUI
{
public:

	//		コンストラクタ
	FadeUI();

	//		デストラクタ
	~FadeUI();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		フェードアウトを使う
	void FadeOutUse();

private:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		アスペクト比
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		回転行列
		float time = 0.0f;								//		時間
		DirectX::SimpleMath::Vector3 pad;
	};

private:

	//		フェードテクスチャパス
	const wchar_t* FADE_TEXTURE_PATH = L"Resources/Texture/UI/Fade/BlackTexture.png";

	//		フェードVSパス
	const wchar_t* FADE_VS_PATH = L"Resources/Shader/UI/Fade/FadeShaderVS.cso";

	//		フェードGSパス
	const wchar_t* FADE_GS_PATH = L"Resources/Shader/UI/Fade/FadeShaderGS.cso";

	//		フェードPSパス
	const wchar_t* FADE_PS_PATH = L"Resources/Shader/UI/Fade/FadeShaderPS.cso";

private:

	ConstBuffer m_buffer;

	float m_time;

	//		フェードアウト
	bool m_fadeOutFlag;

	//		フェードイン
	bool m_fadeInFlag;

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_shader;
};