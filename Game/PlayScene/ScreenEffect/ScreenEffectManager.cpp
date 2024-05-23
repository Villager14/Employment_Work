/*
* @file		ScreenEffectManager.cpp
* @brief	スクリーンエフェクトのマネージャー
* @author	Morita
* @date		2024/05/22
*/

#include "pch.h"

#include "ScreenEffectManager.h"


ScreenEffectManager::ScreenEffectManager(GameManager* gameManager)
	:
	m_gameManager(gameManager)
{
}

ScreenEffectManager::~ScreenEffectManager()
{
}

void ScreenEffectManager::Initialize()
{
	CreateRenderTexture();

	m_redScreen = std::make_unique<RedScreen>();

	m_redScreen->Create({ LibrarySingleton::GetInstance()
		->GetScreenSize().x, 0.0f}, {1.0f, 1.0f});
}

void ScreenEffectManager::Update()
{
	m_redScreen->Update(m_gameManager);
}

void ScreenEffectManager::Render()
{
	m_redScreen->Render(m_shaderResouceView);
}

void ScreenEffectManager::Finalize()
{
}

void ScreenEffectManager::CreateRenderTexture()
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice();

	//		レンダーテクスチャの作製
	m_renderTexture = std::make_unique<DX::RenderTexture>(
		LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetBackBufferFormat());

	//		デバイスの設定
	m_renderTexture->SetDevice(LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice());

	//		サイズの設定
	RECT rect = { 0,0, LibrarySingleton::GetInstance()->GetScreenSize().x,
		LibrarySingleton::GetInstance()->GetScreenSize().y };

	m_renderTexture->SetWindow(rect);

	//		サンプラーの作製
	D3D11_SAMPLER_DESC sampler_desc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	//		フィルター処理方法
	sampler_desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	//		uテクスチャ解決方法
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	//		vテクスチャ解決方法
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	//		wテクスチャ解決方法
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	//		既存のサンプリングデータとの比較
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_LESS;
	//		サンプリングの作製
	device->CreateSamplerState(&sampler_desc,
		m_sampler.ReleaseAndGetAddressOf());
}

void ScreenEffectManager::ChangeRenderTarget()
{
	auto context = LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetD3DDeviceContext();

	//		レンダーターゲット
	auto rtv = m_renderTexture->GetRenderTargetView();
	//		リソース
	m_shaderResouceView = m_renderTexture->GetShaderResourceView();

	//		深度バッファ
	auto depthStencil = LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetDepthStencilView();

	//		レンダーターゲットを変更
	context->ClearRenderTargetView(rtv, DirectX::Colors::SteelBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->OMSetRenderTargets(1, &rtv, depthStencil);
}

void ScreenEffectManager::FirstRenderTarget()
{
	auto context = LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetD3DDeviceContext();

	//		レンダーターゲット
	auto renderTarget = LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetRenderTargetView();

	//		深度
	auto depthStencil = LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, DirectX::Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	auto viewPoart = LibrarySingleton::GetInstance()->GetDeviceResources()->GetScreenViewport();

	context->RSSetViewports(1, &viewPoart);
}
