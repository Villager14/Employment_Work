#include "pch.h"

#include "SmokeEffect.h"

SmokeEffect::SmokeEffect(EffectManager* effectManager)
	:
	m_effectManager(effectManager)
{
	//		�G�t�F�N�g�̐���
	m_effect = std::make_unique<EffectShaderManager<ConstBuffer>>();

	//		�|�X�g�G�t�F�N�g�t���O�𐶐�����
	m_postEffectFlag = std::make_unique<PostEffectFlag>();

	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

SmokeEffect::~SmokeEffect()
{
}

void SmokeEffect::Initialzie()
{
	//		�G�t�F�N�g�̐���
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

	//		�X�P�[��
	m_effect->SetScale({ 10.0f, 10.0f });

	m_effect->SetPosition({0.0f, 5.0f, 0.0f});

	if ((PostEffectFlag::Alpha & flag) != 0)
	{
		//�������`��w��
		ID3D11BlendState* blendstate = LibrarySingleton::GetInstance()->GetCommonState()->Additive();

		// �������菈��
		LibrarySingleton::GetInstance()->GetDeviceResources()->
			GetD3DDeviceContext()->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

		// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
		LibrarySingleton::GetInstance()->GetDeviceResources()->
			GetD3DDeviceContext()->OMSetDepthStencilState
			(LibrarySingleton::GetInstance()->GetCommonState()->DepthNone(), 0);
	}

	if ((PostEffectFlag::AlphaDepth & flag) != 0)
	{
		//�������`��w��(�s����)
		ID3D11BlendState* blendstate =
			LibrarySingleton::GetInstance()->GetCommonState()->Opaque();

		// �������菈��
		LibrarySingleton::GetInstance()->GetDeviceResources()->
			GetD3DDeviceContext()->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

		// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
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