/*
* @file		ScreenObjectView.h
* @brief	スクリーンにオブジェクトを描画するの処理
* @author	Morita
* @date		2024/11/11
*/

#pragma once

#include "../../PostEffectManager.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"

class ScreenObjectView : public IPostEffect
{
public:

	ScreenObjectView(PostEffectManager* postEffectManager);

	~ScreenObjectView();
	
	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		オブジェクト描画
	void ObjectRender() override;

	//		ポストエフェクト後の描画
	void PostEffectRender() override;

	//		終了処理
	void Filanize() override;

	//		テクスチャを受け取る
	ID3D11ShaderResourceView* GetTexture() override { return nullptr; };

public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
	};

private:

	//		時計背景テクスチャパス
	const wchar_t* CLOCK_BACK_GROUND_TEXTURE_PATH = L"Resources/Texture/UI/Clock/ClockBackGround.png";

	//		スクリーンオブジェクト描画VSパス
	const wchar_t* SCREEN_OBJECT_VIEW_VS_PATH = L"Resources/Shader/PostEffect/ScreenObjectView/ScreenObjectViewVS.cso";

	//		スクリーンオブジェクト描画GSパス
	const wchar_t* SCREEN_OBJECT_VIEW_GS_PATH = L"Resources/Shader/PostEffect/ScreenObjectView/ScreenObjectViewGS.cso";

	//		スクリーンオブジェクト描画PSパス
	const wchar_t* SCREEN_OBJECT_VIEW_PS_PATH = L"Resources/Shader/PostEffect/ScreenObjectView/ScreenObjectViewPS.cso";

private:

	//		ポストエフェクトマネージャーのポインタのインスタンス
	PostEffectManager* m_postEffectManager;

	//		テクスチャ
	ID3D11ShaderResourceView* m_texture;
	ID3D11ShaderResourceView* m_objectTexture;

	//		レンダーマネージャー
	std::unique_ptr<UIRenderManager> m_screenObjectShader;

	//		コンストバッファ
	ConstBuffer m_constBuffer;

	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	std::unique_ptr<DX::RenderTexture> m_objectrenderTexture;

};