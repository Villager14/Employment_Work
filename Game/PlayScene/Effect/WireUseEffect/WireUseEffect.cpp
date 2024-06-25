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
}

WireUseEffect::~WireUseEffect()
{
}

void WireUseEffect::Initialize()
{
	//		�r���{�[�h�G�t�F�N�g�̐���
	m_billboardEffect = std::make_unique<BillboardEffect>();

	//		�e�N�X�`���̓ǂݍ���
	m_billboardEffect->LoadTexture(L"Resources/Texture/UI/WireSelect/WireSelect.png");

	//		�r���{�[�h�̍쐻
	m_billboardEffect->Create();

}

void WireUseEffect::Update(PlayerCameraInformation* cameraInformation)
{
	if (m_playerInformation->GetWireJudgement())
	{
		m_billboardEffect->CreateBillboard(
			cameraInformation->GetTarget(),
			cameraInformation->GetEye(),
			cameraInformation->GetUP());
	}
}

void WireUseEffect::Render(const std::vector<DirectX::SimpleMath::Vector3>& position)
{
	if (m_playerInformation->GetWireJudgement())
	{
		m_billboardEffect->Render(position);
	}
}

void WireUseEffect::Finalize()
{
}
