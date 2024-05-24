
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
	//		�T�C�Y
	RECT rect = { 0,0,LibrarySingleton::GetInstance()->GetScreenSize().x,
				  LibrarySingleton::GetInstance()->GetScreenSize().y };

	//		�[�x�X�e���V���̐���
	m_depthStencil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	//		�f�o�C�X��ݒ肷��
	m_depthStencil->SetDevice(LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetD3DDevice());
	//		�}�b�v�̃T�C�Y���󂯎��
	m_depthStencil->SetWindow(rect);
}

void ShadowInformation::CreateRenderTexture()
{
	//		�T�C�Y
	RECT rect = { 0,0,LibrarySingleton::GetInstance()->GetScreenSize().x,
				  LibrarySingleton::GetInstance()->GetScreenSize().y };

	//		�[�x�X�e���V���̐���
	m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	//		�f�o�C�X��ݒ肷��
	m_renderTexture->SetDevice(LibrarySingleton::GetInstance()->
		GetDeviceResources()->GetD3DDevice());
	//		�}�b�v�̃T�C�Y���󂯎��
	m_renderTexture->SetWindow(rect);
}
