/*
* @file		EffectManager.cpp
* @brief	エフェクトマネージャー
* @author	Morita
* @date		2024/06/10
*/

#include "pch.h"

#include "EffectManager.h"

EffectManager::EffectManager(PlayerInformation* playerInformation)
	:
	m_playerInformation(playerInformation)
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize()
{
	//		ワイヤー使用時のエフェクトの生成
	m_wireUseEffect = std::make_unique<WireUseEffect>(m_playerInformation);

	//		ワイヤー使用時のエフェクトの初期化
	m_wireUseEffect->Initialize();
}

void EffectManager::Update(PlayerCameraInformation* cameraInformation)
{
	//		ワイヤー使用時のエフェクトの更新処理
	m_wireUseEffect->Update(cameraInformation);
}

void EffectManager::Render()
{
	for (int i = 0, max = static_cast<int>(m_wireInformation.size()); i < max; ++i)
	{
		if (!(*m_wireInformation[i]).m_usedJudgement) continue;

		//		ワイヤー使用時のエフェクトの描画
		m_wireUseEffect->Render((*m_wireInformation[i]).position);
	}
}

void EffectManager::Finalize()
{
}
