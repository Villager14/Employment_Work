/*
* @file		Bler.h
* @brief	ブラーの処理
* @author	Morita
* @date		2024/10/02
*/

#pragma once

#include "Common/RenderTexture.h"

#include "../../PostEffectManager.h"

#include "Common/DepthStencil.h"

class Bler
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(postEffectManager)	PostEffectManagerのインスタンスのポインタ
	*/
	Bler(PostEffectManager* postEffectManager);

	~Bler();

	//		初期化処理
	void Initialize();

	/*
	*	描画処理
	* 
	*	@param	(texture)	テクスチャ
	*	@return テクスチャ
	*/
	ID3D11ShaderResourceView* Render(ID3D11ShaderResourceView* texture);

	//		シェーダーの作製をする
	void CreateShader();

	//		終了処理
	void Finalize();

	//		レンダーテクスチャの作成
	void CreateRenderTexture();

public:

	//		コンストバッファ
	struct SideConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
		DirectX::SimpleMath::Vector4 blerValue;				//		ブラーの値
	};

private:

	//		テストテクスチャパス
	const wchar_t* TEST_TEXTURE_PATH = L"Resources/Texture/Test.jpg";

	//		横ブラーVSパス
	const wchar_t* SLIDER_BLER_VS_PATH = L"Resources/Shader/PostEffect/Bler/SideBler/SideBlerVS.cso";

	//		横ブラーGSパス
	const wchar_t* SLIDER_BLER_GS_PATH = L"Resources/Shader/PostEffect/Bler/SideBler/SideBlerGS.cso";

	//		横ブラーPSパス
	const wchar_t* SLIDER_BLER_PS_PATH = L"Resources/Shader/PostEffect/Bler/SideBler/SideBlerPS.cso";


	//		縦ブラーVSパス
	const wchar_t* WARP_BLER_VS_PATH = L"Resources/Shader/PostEffect/Bler/WarpBler/WarpBlerVS.cso";

	//		縦ブラーGSパス
	const wchar_t* WARP_BLER_GS_PATH = L"Resources/Shader/PostEffect/Bler/WarpBler/WarpBlerGS.cso";

	//		縦ブラーPSパス
	const wchar_t* WARP_BLER_PS_PATH = L"Resources/Shader/PostEffect/Bler/WarpBler/WarpBlerPS.cso";

	//		合成ブラーVSパス
	const wchar_t* EXPANSION_BLER_VS_PATH = L"Resources/Shader/PostEffect/Bler/Expansion/ExpansionVS.cso";

	//		合成ブラーGSパス
	const wchar_t* EXPANSION_BLER_GS_PATH = L"Resources/Shader/PostEffect/Bler/Expansion/ExpansionGS.cso";

	//		合成ブラーPSパス
	const wchar_t* EXPANSION_BLER_PS_PATH = L"Resources/Shader/PostEffect/Bler/Expansion/ExpansionPS.cso";

private:

	//		ポストエフェクトマネージャー
	PostEffectManager* m_postEffectManager;

	//		横レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_sideRenderTexture;

	//		縦レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_warpRenderTexture;

	//		拡大テクスチャ
	std::unique_ptr<DX::RenderTexture> m_expansionRenderTexture;

	//		横ブラー
	std::unique_ptr<UIRenderManager> m_sideBler;

	//		縦ブラー
	std::unique_ptr<UIRenderManager> m_warpBler;

	//		拡大ブラー
	std::unique_ptr<UIRenderManager> m_expansionBler;

	//		横コンストバッファ
	SideConstBuffer m_sideConstBuffer;

	//		横テクスチャ
	ID3D11ShaderResourceView* m_sideTexture;

	//		縦テクスチャ
	ID3D11ShaderResourceView* m_warpTexture;

	//		拡大テクスチャ
	ID3D11ShaderResourceView* m_expansionTexture;

	//		横深度バッファ
	std::unique_ptr<DepthStencil> m_sideDepthStancil;

	//		縦深度バッファ
	std::unique_ptr<DepthStencil> m_warpDepthStancil;

};