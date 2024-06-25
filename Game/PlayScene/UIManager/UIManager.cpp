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

	//		�W�����̐���
	m_concentrationLine = std::make_unique<ConcentrationLineManager>();

	//		�W�����̏�����
	m_concentrationLine->Initialize();
}

void UIManager::Update()
{
	//		���Ԃ̍X�V
	m_clockManager->Update(m_gameManager);

	//		�_�b�V���N�[���^�C���̍X�V
	m_coolTime->Update(m_playerInformation);

	//		�t�F�[�h�̍X�V
	m_fadeIn->Update(m_gameManager);

	//		�Q�[���I�[�o�[�̍X�V
	m_gameOver->Update();

	//		�X�N���[���̐��̍X�V
	m_screenRay->Update();

	//		�W�����̍X�V
	m_concentrationLine->Update();
}

void UIManager::FrontRender()
{
	//		�W�����̕`��
	m_concentrationLine->Render();

	//		���v�̕`��
	m_clockManager->Render();

	//		�_�b�V���N�[���^�C���̕`��
	m_coolTime->Render();

	//		�X�N���[���̐��̕`��
	m_screenRay->Render();
}

void UIManager::BackRender()
{
	//		�Q�[���[�o�[�̕`��
	m_gameOver->Render();

	//		�t�F�[�h�C���̕`��
	m_fadeIn->Render();
}
