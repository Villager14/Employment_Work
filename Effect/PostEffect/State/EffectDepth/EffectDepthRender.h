/*
* @file		TransparencyDepth.h
* @brief	透明処理の深度処理
* @author	Morita
* @date		2024/10/18
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../IPostEffect.h"

class EffectDepthRender : public IPostEffect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(posteffectManager)	ポストエフェクトマネージャーのインスタンスのポインタ
	*/
	EffectDepthRender(PostEffectManager* postEffectManager);

	//		デストラクタ
	~EffectDepthRender();

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
	ID3D11ShaderResourceView* GetTexture() override { return m_texture; };

	//		レンダーターゲットの作製
	void CreateRenderTarget();

private:
	//		オブジェクトシェーダーパス
	const wchar_t* TRANSPARENCY_OBJECT_PATH = L"Resources/Shader/PostEffect/Transparency/TransparencyObject/TransparencyObject.cso";

private:

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		テクスチャ
	ID3D11ShaderResourceView* m_texture;

	//		ポストエフェクトマネージャー
	PostEffectManager* m_postEffectManager;

	//		オブジェクトに対するシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_objectShader;
};
