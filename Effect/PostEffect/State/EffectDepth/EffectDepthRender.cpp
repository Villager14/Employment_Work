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
}

EffectDepthRender::~EffectDepthRender()
{
}

void EffectDepthRender::Initialize()
{
	CreateRenderTarget();

	//		�I�u�W�F�N�g�ɑ΂���V�F�[�_�[���Z�b�g
	m_objectShader = LibrarySingleton::GetInstance()->CreatePSShader
	(TRANSPARENCY_OBJECT_PATH);
}

void EffectDepthRender::Update()
{
}

void EffectDepthRender::ObjectRender()
{
	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|����
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(true);

	//		�I�u�W�F�N�g�ɃV�F�[�_�[���|����
	m_postEffectManager->GetPostObjectShader()->SetPixselShader(m_objectShader.Get());

	//		�w�i�F
	m_postEffectManager->SetBackRenderColor(DirectX::Colors::White);

	//		�I�u�W�F�N�g�ɑ΂��ăV�F�[�_�[���|���Ȃ��悤�ɂ���
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		�����_�[�^�[�Q�b�g��؂�ւ���
	m_texture = m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());
}

void EffectDepthRender::PostEffectRender()
{
}

void EffectDepthRender::Filanize()
{
	m_renderTexture.reset();
}

void EffectDepthRender::CreateRenderTarget()
{
	//		�����_�[�e�N�X�`���̍쐻
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
