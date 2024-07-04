/*
* @file		EffectManager.cpp
* @brief	�G�t�F�N�g�}�l�[�W���[
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
	//		���C���[�g�p���̃G�t�F�N�g�̐���
	m_wireUseEffect = std::make_unique<WireUseEffect>(m_playerInformation);

	//		���C���[�g�p���̃G�t�F�N�g�̏�����
	m_wireUseEffect->Initialize();
}

void EffectManager::Update(PlayerCameraInformation* cameraInformation)
{
	//		���C���[�g�p���̃G�t�F�N�g�̍X�V����
	m_wireUseEffect->Update(cameraInformation);
}

void EffectManager::Render()
{
	for (int i = 0, max = static_cast<int>(m_wireInformation.size()); i < max; ++i)
	{
		if (!(*m_wireInformation[i]).m_usedJudgement) continue;

		//		���C���[�g�p���̃G�t�F�N�g�̕`��
		m_wireUseEffect->Render((*m_wireInformation[i]).position);
	}
}

void EffectManager::Finalize()
{
}
