/*
* @file		UIManager.cpp
* @brief	UI�}�l�[�W���[
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "UIManager.h"

UIManager::UIManager(Player* player)
	:
	m_player(player)
{
}

UIManager::~UIManager()
{
}

void UIManager::Initialize()
{
	//		���v�̔w�i�̐���
	m_clockManager = std::make_unique<ClockManager>();

	//		���v�̔w�i�̏�����
	m_clockManager->Initialize();

	//		�N�[���^�C���̐���
	m_coolTime = std::make_unique<CoolTime>();

	//		�N�[���^�C���̏�����
	m_coolTime->Initialize();
}

void UIManager::Update()
{
	m_clockManager->Update();

	m_coolTime->Update();
}

void UIManager::Render()
{
	m_clockManager->Render();

	m_coolTime->Render();
}
