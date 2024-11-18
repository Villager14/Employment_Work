#include "ScreenObjectView.h"
/*
* @file		ScreenObjectView.h
* @brief	�X�N���[���ɃI�u�W�F�N�g��`�悷��̏���
* @author	Morita
* @date		2024/11/11
*/

#include "pch.h"

#include "ScreenObjectView.h"

ScreenObjectView::ScreenObjectView(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
}

ScreenObjectView::~ScreenObjectView()
{
}

void ScreenObjectView::Initialize()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()
					  ->CreateRenderTexture();

	m_objectrenderTexture = m_postEffectManager->GetCommonProcess()
		->CreateRenderTexture();

	//		�[�x�V�F�[�_�[�`��
	m_screenObjectShader = std::make_unique<UIRenderManager>();

	//		�����p
	m_screenObjectShader->Create(CLOCK_BACK_GROUND_TEXTURE_PATH,
		SCREEN_OBJECT_VIEW_VS_PATH,
		SCREEN_OBJECT_VIEW_GS_PATH,
		SCREEN_OBJECT_VIEW_PS_PATH,
		m_constBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		�萔�o�b�t�@�̒l
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
}

void ScreenObjectView::Update()
{
}

void ScreenObjectView::ObjectRender()
{
	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|�Ȃ�
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	m_postEffectManager->SetBackRenderColor(DirectX::Colors::White);

	//		�����_�[�^�[�Q�b�g�̕ύX(�I�u�W�F�N�g�̕`��)
	m_texture = m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());
}

void ScreenObjectView::PostEffectRender()
{
	//		�����_�[�^�[�Q�b�g�̕ύX(�I�u�W�F�N�g�̕`��)
	m_objectTexture = m_postEffectManager->ChangeRenderTarget(m_objectrenderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());


	m_screenObjectShader->SetTextureSize(static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
										 static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	m_screenObjectShader->SetTexture(m_texture);
	m_screenObjectShader->SetTexture(m_postEffectManager->GetShaderTexture(), 1);

	m_screenObjectShader->Render(m_constBuffer);

	m_postEffectManager->SetShaderTexture(m_objectTexture);
}

void ScreenObjectView::Filanize()
{
}
