/*
* @file		UIManager.cpp
* @brief	UI�}�l�[�W���[
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "UIManager.h"

UIManager::UIManager(PlayerInformation* playerInformation,
					 GameManager* gameManager)
	:
	m_playerInformation(playerInformation),
	m_gameManager(gameManager)
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

	//		�t�F�[�h�C���̐���
	m_fadeIn = std::make_unique<FadeIn>();

	//		�t�F�[�h�C���̏�����
	m_fadeIn->Initialize();

	//		�Q�[���[�I�[�o�[�̐���
	m_gameOver = std::make_unique<GameOverManager>(m_gameManager);

	//		�Q�[���I�[�o�[�̏�����
	m_gameOver->Initialize();

	//		�X�N���[���̗�̐���
	m_screenRay = std::make_unique<ScreenRay>(m_gameManager);

	//		�X�N���[���̏�����
	m_screenRay->Initialize();
}

void UIManager::Update()
{
	m_clockManager->Update(m_gameManager);

	m_coolTime->Update();

	m_fadeIn->Update(m_gameManager);

	m_gameOver->Update();

	m_screenRay->Update();
}

void UIManager::FrontRender()
{
	m_clockManager->Render();

	m_coolTime->Render();

	m_screenRay->Render();
}

void UIManager::BackRender()
{
	m_gameOver->Render();

	m_fadeIn->Render();
}
