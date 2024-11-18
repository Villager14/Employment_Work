/*
* @file		Bler.cpp
* @brief	�u���[�̏���
* @author	Morita
* @date		2024/10/02
*/

#include "pch.h"

#include "Bler.h"

Bler::Bler(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
	//		���[�x�X�e���V���̍쐻�i�V���h�E�}�b�v�j
	m_sideDepthStancil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);

	//		�c�[�x�X�e���V���̍쐻�i�V���h�E�}�b�v�j
	m_warpDepthStancil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
}

Bler::~Bler()
{
}

void Bler::Initialize()
{
	//		�T�C�h�u���[�𐶐�����
	m_sideBler = std::make_unique<UIRenderManager>();
	m_warpBler = std::make_unique<UIRenderManager>();
	m_expansionBler = std::make_unique<UIRenderManager>();


	CreateRenderTexture();

	//		�V�F�[�_�[�̍쐻
	CreateShader();

	//		�[�x�X�e���V���̍쐻
	RECT rect = { 0,0,
	  static_cast<long>(LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f),
	  static_cast<long>(LibrarySingleton::GetInstance()->GetScreenSize().y) };
	m_sideDepthStancil->SetDevice(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice());
	m_sideDepthStancil->SetWindow(rect);

	rect = { 0,0,
		  static_cast<long>(LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f),
		  static_cast<long>(LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f) };
	m_warpDepthStancil->SetDevice(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice());
	m_warpDepthStancil->SetWindow(rect);

	//		�E�B���h�E�T�C�Y��ݒ肷��
	m_sideConstBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	m_sideConstBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	m_sideConstBuffer.blerValue = { 1.0f, 0.0f, 0.0f, 0.0f };
}

ID3D11ShaderResourceView* Bler::Render(ID3D11ShaderResourceView* texture)
{
	//		���e�N�X�`��
	m_sideTexture = m_postEffectManager->ChangeRenderTarget(m_sideRenderTexture.get(),
		m_sideDepthStancil->GetDepthStencilView());
	
	//		�e�N�X�`����ݒ肷��
	m_sideBler->SetTexture(texture);

	m_sideBler->Render(m_sideConstBuffer);

	//		�c�e�N�X�`��
	m_warpTexture = m_postEffectManager->ChangeRenderTarget(m_warpRenderTexture.get(),
		m_warpDepthStancil->GetDepthStencilView());

	//		�e�N�X�`����ݒ肷��
	m_warpBler->SetTexture(m_sideTexture);

	//		�e�N�X�`���T�C�Y��ݒ肷��
	m_warpBler->SetTextureSize(static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	m_warpBler->Render(m_sideConstBuffer);

	//		�g��e�N�X�`��
	m_expansionTexture = m_postEffectManager->ChangeRenderTarget(m_expansionRenderTexture.get(),
		LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetDepthStencilView());

	//		�e�N�X�`����ݒ肷��
	m_expansionBler->SetTexture(m_warpTexture);

	//		�e�N�X�`���T�C�Y��ݒ肷��
	m_expansionBler->SetTextureSize(static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	m_expansionBler->Render(m_sideConstBuffer);

	return m_expansionTexture;
}

void Bler::CreateShader()
{
	//		���ڂ����V�F�[�_�[���쐬����
	m_sideBler->Create(TEST_TEXTURE_PATH,
		SLIDER_BLER_VS_PATH, SLIDER_BLER_GS_PATH,
		SLIDER_BLER_PS_PATH, m_sideConstBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		�c�ڂ����V�F�[�_�[�𐧍삷��
	m_warpBler->Create(TEST_TEXTURE_PATH,
		WARP_BLER_VS_PATH, WARP_BLER_GS_PATH,
		WARP_BLER_PS_PATH, m_sideConstBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		�����V�F�[�_�[�𐧍삷��
	m_expansionBler->Create(TEST_TEXTURE_PATH,
		EXPANSION_BLER_VS_PATH, EXPANSION_BLER_GS_PATH,
		EXPANSION_BLER_PS_PATH, m_sideConstBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);
}

void Bler::Finalize()
{
	m_sideBler.reset();
	m_warpBler.reset();
	m_expansionBler.reset();

	m_sideRenderTexture.reset();
	m_warpRenderTexture.reset();
	m_expansionRenderTexture.reset();
}

void Bler::CreateRenderTexture()
{
	//		�������_�[�e�N�X�`���̐���
	m_sideRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture(DirectX::SimpleMath::Vector2
	(LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f,
		LibrarySingleton::GetInstance()->GetScreenSize().y));

	//		�c�����_�[�e�N�X�`���̐���
	m_warpRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture(DirectX::SimpleMath::Vector2
	(LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f,
		LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f));

	//		���������_�[�e�N�X�`��
	m_expansionRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture(DirectX::SimpleMath::Vector2
	(LibrarySingleton::GetInstance()->GetScreenSize().x,
		LibrarySingleton::GetInstance()->GetScreenSize().y));
}
