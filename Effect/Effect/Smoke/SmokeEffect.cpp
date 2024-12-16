#include "pch.h"

#include "SmokeEffect.h"

SmokeEffect::SmokeEffect(EffectManager* effectManager)
	:
	m_effectManager(effectManager)
{
	//		エフェクトの生成
	m_effect = std::make_unique<EffectShaderManager<ConstBuffer>>();

	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();

	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

SmokeEffect::~SmokeEffect()
{
}

void SmokeEffect::Initialzie()
{
	//		エフェクトの生成
	m_effect->Create(
		L"Resources/Texture/Effect/Smoke/Smoke.png",
		L"Resources/Shader/Effect/SmokeEffect/SmokeEffectVS.cso",
		L"Resources/Shader/Effect/SmokeEffect/SmokeEffectGS.cso",
		L"Resources/Shader/Effect/SmokeEffect/SmokeEffectPS.cso",
		m_constBuffer,
		{ 0.0f, 5.0f, 0.0f },
		{ 1.0f, 1.0f }
	);
}

void SmokeEffect::Update()
{
}

void SmokeEffect::Render(PostEffectFlag::Flag flag)
{
	m_effect->RenderProcedure();

	m_constBuffer = m_effect->GetConstBuffer();

	//		スケール
	m_effect->SetScale({ 10.0f, 10.0f });

	m_effect->SetPosition({0.0f, 5.0f, 0.0f});

	if ((PostEffectFlag::Alpha & flag) != 0)
	{
		//半透明描画指定
		ID3D11BlendState* blendstate = LibrarySingleton::GetInstance()->GetCommonState()->Additive();

		// 透明判定処理
		LibrarySingleton::GetInstance()->GetDeviceResources()->
			GetD3DDeviceContext()->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

		// 深度バッファに書き込み参照する
		LibrarySingleton::GetInstance()->GetDeviceResources()->
			GetD3DDeviceContext()->OMSetDepthStencilState
			(LibrarySingleton::GetInstance()->GetCommonState()->DepthNone(), 0);
	}

	if ((PostEffectFlag::AlphaDepth & flag) != 0)
	{
		//半透明描画指定(不透明)
		ID3D11BlendState* blendstate =
			LibrarySingleton::GetInstance()->GetCommonState()->Opaque();

		// 透明判定処理
		LibrarySingleton::GetInstance()->GetDeviceResources()->
			GetD3DDeviceContext()->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

		// 深度バッファに書き込み参照する
		LibrarySingleton::GetInstance()->GetDeviceResources()->
			GetD3DDeviceContext()->OMSetDepthStencilState
			(LibrarySingleton::GetInstance()->GetCommonState()->DepthDefault(), 0);
	}

	m_constBuffer.matWorld = m_effect->GetBillbord().Transpose();

	m_effect->Render(m_constBuffer);
}

void SmokeEffect::Finalize()
{
	m_effect.release();
}