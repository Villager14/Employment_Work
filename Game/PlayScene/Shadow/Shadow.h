/*
* @file		Shwdow.h
* @brief	影オブジェクト
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "ShadowInformation.h"

#include "Game/PlayScene/Player/PlayerInformation.h"


class Shadow
{
public:

	//		コンテキスト
	Shadow();

	//		デストラクタ
	~Shadow();

	//		初期化処理
	void Initialize();

	//		終了処理
	void Finalize();

	//		影の作成
	void CreateShadow();

	void Render();

	/*
	*	レンダーターゲットの変更
	*
	*	@param	(playerPos)	プレイヤーの座標
	*/
	void ChangeRenderTarget(const DirectX::SimpleMath::Vector3& playerpos);

private:

	//		定数バッファ１
	struct ConstantBuffer
	{
		DirectX::XMMATRIX lightViewProj;	// ライトの投影空間へ座標変換する行列
		DirectX::XMVECTOR lightPosition;	// ライトの位置
		DirectX::XMVECTOR lightDirection;	// ライトの方向
		DirectX::XMVECTOR lightAmbient;		// ライトの環境光
	};

	//		定数バッファへのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	//		定数バッファ２
	struct ConstantBuffer2
	{
		float fCosTheta;		// スポットライトのfov/2
		float pad[3];
	};

	//		定数バッファへのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer2;

	//		テクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture2D;


	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

private:

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowShaderPS;

	//		頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowShaderVS;

	//		ピクセル深度シェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowDepthShaderPS;

	//		頂点深度シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowDepthShaderVS;

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		深度ステンシル
	std::unique_ptr<DepthStencil> m_depthStencil;

	//		サンプラーの作製
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;

	//		ライトの位置
	DirectX::SimpleMath::Vector3 m_lightPosition;

	//		ライトの回転
	DirectX::SimpleMath::Quaternion m_lightRotate;

	//		ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	//		プロジェクション行列
	DirectX::SimpleMath::Matrix m_proj;

	//		ライトの方向
	DirectX::SimpleMath::Vector3 m_rightDirection;

	DirectX::SimpleMath::Vector3 playerPostion;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	std::unique_ptr<DirectX::Model> m_light;

	//		ライトの範囲
	float m_lightRange;

	//		シャドウマップサイズ
	float m_shadowSize;

	//		影の情報
	std::unique_ptr<ShadowInformation> m_information;

public:

		/*
	*	影の情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	ShadowInformation* GetInformation() { return m_information.get(); }


	/*
	*	深度バッファ用ビュー行列
	*
	*	@return ビュー行列
	*/
	const DirectX::SimpleMath::Matrix& GetDepthView() { return m_view; }

	/*
	*	深度バッファ用プロジェクション行列
	*
	*	@return	プロジェクション行列
	*/
	const DirectX::SimpleMath::Matrix& GetDpethProj() { return m_proj; }

	/*
	*	深度バッファ用ピクセルシェーダー
	*
	*	@return	ピクセルシェーダー
	*/
	const Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetDepthPSShader()
	{
		return m_shadowDepthShaderPS;
	}

	/*
	*	深度バッファ用頂点シェーダー
	*
	*	@return	頂点シェーダー
	*/
	Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetDepthVSShader()
	{
		return m_shadowDepthShaderVS;
	}

	/*
	*	影用ピクセルシェーダー
	*
	*	@return	ピクセルシェーダー
	*/
	const Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetShadowPSShader()
	{
		return m_shadowShaderPS;
	}

	/*
	*	影用頂点シェーダー
	*
	*	@return	頂点シェーダー
	*/
	Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetShadowVSShader()
	{
		return m_shadowShaderVS;
	}

	/*
	*	定数バッファ1を受け取る
	*
	*	@return 定数バッファ
	*/
	const Microsoft::WRL::ComPtr<ID3D11Buffer>& GetConstantBuffer1()
	{
		return m_constantBuffer;
	}

	/*
	*	定数バッファ2を受け取る
	*
	*	@return 定数バッファ
	*/
	const Microsoft::WRL::ComPtr<ID3D11Buffer>& GetConstantBuffer2()
	{
		return m_constantBuffer2;
	}

	/*
	*	サンプラーを受け取る
	*
	*	@return サンプラー
	*/
	const Microsoft::WRL::ComPtr<ID3D11SamplerState>& GetSamplerState()
	{
		return m_shadowMapSampler;
	}

	/*
	*	シェーダーリソースビューの取得
	*
	*	@return	シェーダーリソースビュー
	*/
	ID3D11ShaderResourceView* GetShaderResourceView()
	{
		return m_renderTexture->GetShaderResourceView();
	}
};



//class Shadow
//{
//private:
//
//	//		定数バッファ１
//	struct ConstantBufferShadow
//	{
//		DirectX::XMMATRIX lightViewProj;	// ライトの投影空間へ座標変換する行列
//		DirectX::XMVECTOR lightPosition;	// ライトの位置
//		DirectX::XMVECTOR lightDirection;	// ライトの方向
//		DirectX::XMVECTOR lightAmbient;		// ライトの環境光
//	};
//
//	//		定数バッファ２
//	struct ConstantBufferDepth
//	{
//		float fCosTheta;		// スポットライトのfov/2
//		float pad[3];
//	};
//
//public:
//
//	//		コンストラクタ
//	Shadow(PlayerInformation* playerInformation);
//
//	//		デストラクタ
//	~Shadow();
//
//	//		初期化処理
//	void Initialize();
//
//	//		ターゲットを変更する
//	void ChangeTarget();
//
//	//		影の作製
//	void CreateShadow();
//
//	//		シェーダーの作製
//	void CreateShader();
//
//	//		定数バッファの作製
//	void CreateConstBuffer();
//private:
//	//		影の情報
//	std::unique_ptr<ShadowInformation> m_information;
//
//	//		プレイヤーの情報
//	PlayerInformation* m_playerInformation;
//
//	//		定数バッファへのポインタ
//	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantShadowBuffer;
//
//	//		定数バッファへのポインタ
//	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantDepthBuffer;
//
//	//		サンプラーの作製
//	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;
//
//	//		影のピクセルシェーダー
//	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowPS;
//
//	//		影の頂点シェーダー
//	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowVS;
//
//	//		影の深度バッファピクセルシェーダー
//	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowDepthPS;
//
//	//		影の深度バッファ頂点シェーダー
//	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowDepthVS;
//
//
//
//	//		深度ステンシル
//	std::unique_ptr<DepthStencil> m_depthStencil;
//
//	//		レンダーテクスチャ
//	std::unique_ptr<DX::RenderTexture> m_renderTexture;
//
//public:
//
//	/*
//	*	影の情報を受け取る
//	* 
//	*	@return インスタンスのポインタ
//	*/
//	ShadowInformation* GetInformation() { return m_information.get(); }
//
//	/*
//*	影用ピクセルシェーダーを受け取る
//*
//*	@return ピクセルシェーダー
//*/
//	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetShadowDepthPS() { return m_shadowDepthPS; }
//
//	/*
//*
//*	影用シェーダーを受け取る
//*
//*	@return 頂点シェーダー
//*/
//	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetShadowDepthVS() { return m_shadowDepthVS; }
//
//};
//
