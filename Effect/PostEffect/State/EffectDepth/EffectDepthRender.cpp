/*
* @file		TransparencyDepth.h
* @brief	透明処理の深度処理
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

	//		オブジェクトに対するシェーダーをセット
	m_objectShader = LibrarySingleton::GetInstance()->CreatePSShader
	(TRANSPARENCY_OBJECT_PATH);
}

void EffectDepthRender::Update()
{
}

void EffectDepthRender::ObjectRender()
{
	//		オブジェクトに対してシェーダーを掛ける
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(true);

	//		オブジェクトにシェーダーを掛ける
	m_postEffectManager->GetPostObjectShader()->SetPixselShader(m_objectShader.Get());

	//		背景色
	m_postEffectManager->SetBackRenderColor(DirectX::Colors::White);

	//		オブジェクトに対してシェーダーを掛けないようにする
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		レンダーターゲットを切り替える
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
	//		レンダーテクスチャの作製
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
