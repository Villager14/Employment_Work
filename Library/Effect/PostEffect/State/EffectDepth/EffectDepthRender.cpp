/*
* @file		TransparencyDepth.h
* @brief	���������̐[�x����
* @author	Morita
* @date		2024/10/18
*/

#include "pch.h"

#include "EffectDepthRender.h"

EffectDepthRender::EffectDepthRender(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
	//		�����_�[�e�N�X�`���̍쐻
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_depthRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();

	m_depthShaderView = std::make_unique<UIRenderManager>();

}

EffectDepthRender::~EffectDepthRender()
{
}

void EffectDepthRender::Initialize()
{
	CreateDepth();

	//		�����p
	m_depthShaderView->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/Transparency/Depth/TransparencyDepthVS.cso",
		L"Resources/Shader/PostEffect/Transparency/Depth/TransparencyDepthGS.cso",
		L"Resources/Shader/PostEffect/Transparency/Depth/TransparencyDepthPS.cso",
		m_constBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		�萔�o�b�t�@�̒l
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_constBuffer.backColor = m_postEffectManager->GetBackColor();
	m_constBuffer.drawingDistance = { 0.1f, 20.0f, 0.0f, 0.0f };

}

void EffectDepthRender::Update()
{
}

void EffectDepthRender::ObjectRender()
{
	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|���Ȃ��悤�ɂ���
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		�����_�[�^�[�Q�b�g��؂�ւ���
	m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(), m_depthStencilView.Get());
}

void EffectDepthRender::PostEffectRender()
{
	m_texture = m_postEffectManager->ChangeRenderTarget(m_depthRenderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());

	m_depthShaderView->SetTextureSize(static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	m_depthShaderView->SetTexture(m_depthSRV);

	//		�`�揈��
	m_depthShaderView->Render(m_constBuffer);
}

void EffectDepthRender::Filanize()
{
}

void EffectDepthRender::CreateDepth()
{
	//		�T�C�Y
	RECT rect = { 0,0, static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().x),
				  static_cast<LONG>(LibrarySingleton::GetInstance()->GetScreenSize().y) };

	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	auto const width = size_t(std::max<LONG>(rect.right - rect.left, 1));
	auto const height = size_t(std::max<LONG>(rect.bottom - rect.top, 1));

	// �[�x�e�N�X�`���̐ݒ�
	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = width; // �e�N�X�`���̕�
	depthTextureDesc.Height = height; // �e�N�X�`���̍���
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.Format = DXGI_FORMAT_R32_TYPELESS; // �[�x�t�H�[�}�b�g
	depthTextureDesc.SampleDesc.Count = 1; // �}���`�T���v�����O�̃J�E���g
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	// �e�N�X�`�����쐬
	HRESULT hr = device->CreateTexture2D(&depthTextureDesc, nullptr, &m_depthTexture);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		exit;
	}

	// �[�x�X�e���V���r���[�̍쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = device->CreateDepthStencilView(m_depthTexture.Get(), &dsvDesc, &m_depthStencilView);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		exit;
	}

	// �V�F�[�_�[���\�[�X�r���[�̍쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView(m_depthTexture.Get(), &srvDesc, &m_depthSRV);
	if (FAILED(hr))
	{
		// �G���[�n���h�����O
		exit;
	}
}