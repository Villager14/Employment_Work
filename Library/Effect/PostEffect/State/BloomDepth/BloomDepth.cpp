/*
* @file		BloomDepth.cpp
* @brief	ブルームの深度処理
* @author	Morita
* @date		2024/10/14
*/

#include "pch.h"

#include "BloomDepth.h"

BloomDepth::BloomDepth(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
	//		レンダーテクスチャの作製
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_depthRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();

	m_depthShaderView = std::make_unique<UIRenderManager>();

}

BloomDepth::~BloomDepth()
{
}

void BloomDepth::Initialize()
{
	CreateDepth();

	//		合成用
	m_depthShaderView->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/Bloom/BloomUnaffectedDepth/BloomUnaffectedDepthVS.cso",
		L"Resources/Shader/PostEffect/Bloom/BloomUnaffectedDepth/BloomUnaffectedDepthGS.cso",
		L"Resources/Shader/PostEffect/Bloom/BloomUnaffectedDepth/BloomUnaffectedDepthPS.cso",
		m_constBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		定数バッファの値
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
}

void BloomDepth::Update()
{
}

void BloomDepth::ObjectRender()
{
	//		オブジェクトに対してシェーダーを掛けないようにする
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		レンダーターゲットを切り替える
	m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(), m_depthStencilView.Get());
}

void BloomDepth::PostEffectRender()
{
	m_texture = m_postEffectManager->ChangeRenderTarget(m_depthRenderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());

	m_depthShaderView->SetTextureSize(static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	m_depthShaderView->SetTexture(m_depthSRV);

	//		描画処理
	m_depthShaderView->Render(m_constBuffer);

	//m_postEffectManager->SetShaderTexture(m_texture);
}

void BloomDepth::Filanize()
{
}

void BloomDepth::CreateDepth()
{
	//		サイズ
	RECT rect = { 0,0, static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().x),
				  static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().y) };

	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	auto const width = size_t(std::max<LONG>(rect.right - rect.left, 1));
	auto const height = size_t(std::max<LONG>(rect.bottom - rect.top, 1));

	// 深度テクスチャの設定
	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = width; // テクスチャの幅
	depthTextureDesc.Height = height; // テクスチャの高さ
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.Format = DXGI_FORMAT_R32_TYPELESS; // 深度フォーマット
	depthTextureDesc.SampleDesc.Count = 1; // マルチサンプリングのカウント
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	// テクスチャを作成
	HRESULT hr = device->CreateTexture2D(&depthTextureDesc, nullptr, &m_depthTexture);
	if (FAILED(hr))
	{
		// エラーハンドリング
		exit;
	}

	// 深度ステンシルビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = device->CreateDepthStencilView(m_depthTexture.Get(), &dsvDesc, &m_depthStencilView);
	if (FAILED(hr))
	{
		// エラーハンドリング
		exit;
	}

	// シェーダーリソースビューの作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(m_depthTexture.Get(), &srvDesc, &m_depthSRV);
	if (FAILED(hr))
	{
		// エラーハンドリング
		exit;
	}
	/*
	//		サイズ
	RECT rect = { 0,0, static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().x),
				  static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().y) };

	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	auto const width = size_t(std::max<LONG>(rect.right - rect.left, 1));
	auto const height = size_t(std::max<LONG>(rect.bottom - rect.top, 1));

	// 深度テクスチャの設定
	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = width; // テクスチャの幅
	depthTextureDesc.Height = height; // テクスチャの高さ
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.Format = DXGI_FORMAT_R32_TYPELESS; // 深度フォーマット
	depthTextureDesc.SampleDesc.Count = 1; // マルチサンプリングのカウント
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	// テクスチャを作成
	HRESULT hr = device->CreateTexture2D(&depthTextureDesc, nullptr, &m_depthTexture);
	if (FAILED(hr))
	{
		// エラーハンドリング
		exit;
	}

	// 深度ステンシルビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = device->CreateDepthStencilView(m_depthTexture.Get(), &dsvDesc, &m_depthStencilView);
	if (FAILED(hr))
	{
		// エラーハンドリング
		exit;
	}

	// シェーダーリソースビューの作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(m_depthTexture.Get(), &srvDesc, &m_depthSRV);
	if (FAILED(hr))
	{
		// エラーハンドリング
		exit;
	}
	*/
}
