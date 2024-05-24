
#include "pch.h"

#include "ShadowInformation.h"

ShadowInformation::ShadowInformation()
{
}

ShadowInformation::~ShadowInformation()
{
}

void ShadowInformation::CreateDepthStencil()
{
	//		サイズ
	RECT rect = { 0,0,LibrarySingleton::GetInstance()->GetScreenSize().x,
				  LibrarySingleton::GetInstance()->GetScreenSize().y };

	//		深度ステンシルの生成
	m_depthStencil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	//		デバイスを設定する
	m_depthStencil->SetDevice(LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetD3DDevice());
	//		マップのサイズを受け取る
	m_depthStencil->SetWindow(rect);
}

void ShadowInformation::CreateRenderTexture()
{
	//		サイズ
	RECT rect = { 0,0,LibrarySingleton::GetInstance()->GetScreenSize().x,
				  LibrarySingleton::GetInstance()->GetScreenSize().y };

	//		深度ステンシルの生成
	m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	//		デバイスを設定する
	m_renderTexture->SetDevice(LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetD3DDevice());
	//		マップのサイズを受け取る
	m_renderTexture->SetWindow(rect);
}
