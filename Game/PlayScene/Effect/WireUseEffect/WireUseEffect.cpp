/*
* @file		WireUseEffect.cpp
* @brief	ワイヤー使用エフェクト
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
	//		ビルボードエフェクトの生成
	m_billboardEffect = std::make_unique<BillboardEffect>();

	//		テクスチャの読み込み
	m_billboardEffect->LoadTexture(L"Resources/Texture/UI/WireSelect/WireSelect.png");

	//		ビルボードの作製
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
