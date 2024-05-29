/*
* @file		GameManager.cpp
* @brief	�Q�[���}�l�[�W���[
* @author	Morita
* @date		2024/05/22
*/

#include "pch.h"

#include "GameManager.h"

GameManager::GameManager()
	:
	m_gameStartJudgement(false),
	m_deathJudgement(false),
	m_revivalJudgement(false),
	m_goalJudgement(false),
	m_endJudgement(false),
	m_nextSceneJudgement(false),
	m_time(0.0f),
	m_deathCount(0)
{
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{

	if (!m_deathJudgement) return;

	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�}�E�X�̎擾
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Space�܂��͍��N���b�N���������ꍇ��������
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		m_revivalJudgement = true;
	}
}
