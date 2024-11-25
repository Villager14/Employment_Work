/*
* @file		WireUseEffect.cpp
* @brief	���C���[�g�p�G�t�F�N�g
* @author	Morita
* @date		2024/06/10
*/

#include "pch.h"
#include "WireUseEffect.h"

WireUseEffect::WireUseEffect(PlayerInformation* playerInformation)
	:
	m_playerInformation(playerInformation)
{
	//		�G�t�F�N�g�̐���
	m_effect = std::make_unique<EffectShaderManager<ConstBuffer>>();

	//		�|�X�g�G�t�F�N�g�t���O�𐶐�����
	m_postEffectFlag = std::make_unique<PostEffectFlag>();

	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

WireUseEffect::~WireUseEffect()
{
}

void WireUseEffect::Initialize(int size)
{
	//		�G�t�F�N�g�̐���
	m_effect->Create(
		L"Resources/Texture/UI/WireSelect/WireSelect.png",
		L"Resources/Shader/EffectBillboard/EffectBillboardVS.cso",
		L"Resources/Shader/EffectBillboard/EffectBillboardGS.cso",
		L"Resources/Shader/EffectBillboard/EffectBillboardPS.cso",
		m_constBuffer,
		{ 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f }
	);

	WireStatas wireState;

	for (int i = 0; i < size; ++i)
	{
		m_wireStatas.push_back(wireState);
	}
}

void WireUseEffect::Update(DirectX::SimpleMath::Vector3 position, int index)
{
	//		���߂čX�V�����ꍇ
	if (m_wireStatas[index].sclaeChangeJudgement)
	{
		if (m_wireStatas[index].firstJudgement)
		{
			//		�g�p�ς݂Ȃ̂ŕʂ̕������������ۂɃ��Z�b�g����悤�ɂ���
			m_wireStatas[index].resetFlag = true;

			float length = (m_playerInformation->GetPosition() - position).Length();

			length /= 127.0f;

			m_wireStatas[index].maxScale = Library::Lerp(15.0f, 40.0f, Library::Clamp(length, 0.0f, 1.0f));

			m_wireStatas[index].firstJudgement = false;
		}


		m_wireStatas[index].time += LibrarySingleton::GetInstance()->GetElpsedTime() * 1.5f;

		m_wireStatas[index].time = Library::Clamp(m_wireStatas[index].time, 0.0f, 1.0f);

		m_wireStatas[index].scale = Library::Lerp(m_wireStatas[index].maxScale, 10.0f, 1.0f - pow(1.0f - m_wireStatas[index].time, 5.0f));

		if (m_wireStatas[index].time >= 1.0f)
		{
			m_wireStatas[index].sclaeChangeJudgement = false;
		}
	}
}

void WireUseEffect::BillbordUpdate(PlayerCameraInformation* cameraInformation)
{
	if (m_playerInformation->GetWireJudgement())
	{
		m_effect->CreateBillboard(
				cameraInformation->GetTarget(),
				cameraInformation->GetEye(),
		cameraInformation->GetUP());
	}
}

void WireUseEffect::Render(DirectX::SimpleMath::Vector3 position, int index,
	PostEffectFlag::Flag flag)
{
	UNREFERENCED_PARAMETER(flag);

	m_effect->RenderProcedure();

	m_constBuffer = m_effect->GetConstBuffer();

	//		�X�P�[��
	m_effect->SetScale({ m_wireStatas[index].scale, m_wireStatas[index].scale });

	m_effect->SetPosition(position);

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

void WireUseEffect::Finalize()
{
	m_wireStatas.clear();
}

void WireUseEffect::ResetProcess(int index)
{
	if (!m_wireStatas[index].resetFlag) return;

	m_wireStatas[index].time = 0.0f;
	m_wireStatas[index].firstJudgement = true;
	m_wireStatas[index].sclaeChangeJudgement = true;
	m_wireStatas[index].resetFlag = false;
	m_wireStatas[index].scale = 20.0f;
}
