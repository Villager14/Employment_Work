/*
* @file		ShwdowInformation.h
* @brief	影オブジェクトの情報
* @author	Morita
* @date		2024/05/24
*/
#pragma once

#include "Common/DepthStencil.h"

#include "Common/RenderTexture.h"

class ShadowInformation
{
public:

	//		コンストラクタ
	ShadowInformation();

	//		デストラクタ
	~ShadowInformation();

	//		深度ステンシルを作成する
	void CreateDepthStencil();

	//		レンダーテクスチャを作成する
	void CreateRenderTexture();

public:


	//		定数バッファへのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantShadowBuffer;

	//		定数バッファへのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantDepthBuffer;

private:

	//		プロジェクション行列
	DirectX::SimpleMath::Matrix m_proj;

	//		ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	//		ライトの方向
	DirectX::SimpleMath::Vector3 m_lightDirection;

	//		深度ステンシル
	std::unique_ptr<DepthStencil> m_depthStencil;

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		影のピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowPS;
	
	//		影の頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowVS;

	//		影の深度バッファピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowDepthPS;

	//		影の深度バッファ頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowDepthVS;

	//		サンプラーの作製
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;

public:

	/*
	*	プロジェクション行列を設定する
	* 
	*	@param	(proj)	行列
	*/
	void SetProj(DirectX::SimpleMath::Matrix proj) { m_proj = proj; }

	/*
	*	プロジェクション行列を受け取る
	* 
	*	@return 行列
	*/
	const DirectX::SimpleMath::Matrix& GetProj() { return m_proj; }

	/*
	*	ビュー行列を設定する
	*
	*	@param	(view)	行列
	*/
	void SetView(DirectX::SimpleMath::Matrix view) { m_view = view; }

	/*
	*	ビュー行列を受け取る
	* 
	*	@return 行列
	*/
	const DirectX::SimpleMath::Matrix& GetView() { return m_view; }

	/*
	*	ライトの方向を受け取る
	* 
	*	@return　方向
	*/
	const DirectX::SimpleMath::Vector3& GetLightDirection() { return m_lightDirection; }

	/*
	*	ライトの方向を設定する
	* 
	*	@param	(direction)	方向
	*/
	void SetLightDirection(const DirectX::SimpleMath::Vector3 direction) { m_lightDirection = direction; }

	/*
	*	深度ステンシルを受け取る
	* 
	*	@return 深度ステンシルのインスタンスのポインタ
	*/
	DepthStencil* GetDepthStencil() { return m_depthStencil.get(); }

	/*
	*	レンダーテクスチャを受け取る
	* 
	*	@return レンダーテクスチャのインスタンスのポインタ
	*/
	DX::RenderTexture* GetRenderTexture() { return m_renderTexture.get(); }

	/*
	*	影用ピクセルシェーダー
	*
	*	@param	(ps)	ピクセルシェーダー
	*/
	void SetShadowPS(Microsoft::WRL::ComPtr<ID3D11PixelShader> ps)
	{
		m_shadowPS = ps;
	}

	/*
	*	影用ピクセルシェーダーを受け取る
	* 
	*	@return ピクセルシェーダー
	*/
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetShadowPS() { return m_shadowPS; }

	/*
	*	影用頂点シェーダー
	*
	*	@param	(vs)	頂点シェーダー
	*/
	void SetShadowVS(Microsoft::WRL::ComPtr<ID3D11VertexShader> vs)
	{
		m_shadowVS = vs;
	}
	
	/*
	* 
	*	影用シェーダーを受け取る
	* 
	*	@return 頂点シェーダー
	*/
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetShadowVS() { return m_shadowVS; }

	/*
	*	深度用ピクセルシェーダー
	*
	*	@param	(ps)	ピクセルシェーダー
	*/
	void SetShadowDepthPS(Microsoft::WRL::ComPtr<ID3D11PixelShader> ps)
	{
		m_shadowDepthPS = ps;
	}

	/*
	*	影用ピクセルシェーダーを受け取る
	*
	*	@return ピクセルシェーダー
	*/
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetShadowDepthPS() { return m_shadowDepthPS; }

	/*
	*	影用頂点シェーダー
	*
	*	@param	(vs)	頂点シェーダー
	*/
	void SetShadowDepthVS(Microsoft::WRL::ComPtr<ID3D11VertexShader> vs)
	{
		m_shadowDepthVS = vs;
	}

	/*
	*
	*	影用シェーダーを受け取る
	*
	*	@return 頂点シェーダー
	*/
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetShadowDepthVS() { return m_shadowDepthVS; }

	/*
	*	影定数バッファを設定する
	* 
	*	@param	(buffer)	コンストバッファ
	*/
	void SetConstBufferShadow(Microsoft::WRL::ComPtr<ID3D11Buffer> buffer)
	{
		m_constantShadowBuffer = buffer;
	}

	/*
	*	影定数バッファを受け取る
	* 
	*	@return コンストバッファ
	*/
	Microsoft::WRL::ComPtr<ID3D11Buffer> GetConstBufferShadow() { return m_constantDepthBuffer; }

	/*
	*	深度定数バッファを設定する
	* 
	*	@param	(buffer)	コンストバッファ
	*/
	void SetConstBufferDepth(Microsoft::WRL::ComPtr<ID3D11Buffer> buffer)
	{
		m_constantDepthBuffer = buffer;
	}

	/*
	*	深度定数バッファを受け取る
	*
	*	@return コンストバッファ
	*/
	Microsoft::WRL::ComPtr<ID3D11Buffer> GetConstBufferDepth() { return m_constantDepthBuffer; }

	/*
	*	シャドウマップのサンプラーの作製
	* 
	*	@param	(sampler)	サンプラー
	*/
	void SetShadowMapSampler(Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler)
	{
		m_shadowMapSampler = sampler;
	}

	/*
	*	シャドウマップサンプラーを受け取る
	* 
	*	@return サンプラー
	*/
	Microsoft::WRL::ComPtr<ID3D11SamplerState> GetShadowMapSampler() { return m_shadowMapSampler; }
};