/*
* @file		UIManager.cpp
* @brief	UI�}�l�[�W���[
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "UIManager.h"

#include "Clock/ClockManager.h"
#include "CoolTime/CoolTime.h"
#include "Game/PlayScene/UIManager/GameOver/GameOverManager.h"
#include "Game/PlayScene/UIManager/GameClear/GameClearManager.h"
#include "Game/PlayScene/UIManager/SpeedLine/SpeedLine.h"
#include "Game/PlayScene/UIManager/GameStart/GameStart.h"

UIManager::UIManager(PlayerInformation* playerInformation,
					 GameManager* gameManager)
	:
	m_playerInformation(playerInformation),
	m_gameManager(gameManager)
{
	Generation();
}

UIManager::~UIManager()
{
}

void UIManager::Initialize()
{
	//		���v�̔w�i�̏�����
	m_clockManager->Initialize();

	//		�N�[���^�C���̏�����
	m_coolTime->Initialize();

	//		�Q�[���I�[�o�[�̏�����
	m_gameOver->Initialize();

	//		����������
	m_speedLine->Initialize();

	//		�Q�[���N���A�}�l�[�W���[�̏�����
	m_clearManager->Initialize();

	//		�Q�[���X�^�[�g�̏�����
	m_gameStart->Initialize();
}

void UIManager::Generation()
{
	//		�N�[���^�C���̐���
	m_coolTime = std::make_unique<CoolTime>(this);

	//		���v�̔w�i�̐���
	m_clockManager = std::make_unique<ClockManager>(this);

	//		�Q�[���[�I�[�o�[�̐���
	m_gameOver = std::make_unique<GameOverManager>(m_gameManager, this);

	//		�Q�[���N���A�}�l�[�W���[�̐���
	m_clearManager = std::make_unique<GameClearManager>(m_gameManager, this);

	//		�Q�[���X�^�[�g�̐���
	m_gameStart = std::make_unique<GameStart>(m_gameManager, this);

	//		�X�s�[�h���C���̐���
	m_speedLine = std::make_unique<SpeedLine>(this);

	//		�X�^���_�[�h�V�F�[�_�[�̍쐻
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	//		�X�^���_�[�h�V�F�[�_�[�̏�����
	m_standardShader->Initialize();

	//		UI�e�N�X�`���̍쐻
	CreateStandardUITexture();
}

void UIManager::Update()
{
	//		���x�̍X�V����
	m_speedLine->Update();

	//		���Ԃ̍X�V
	m_clockManager->Update(m_gameManager);

	//		�_�b�V���N�[���^�C���̍X�V
	m_coolTime->Update(m_playerInformation);

	//		�Q�[���I�[�o�[�̍X�V
	m_gameOver->Update();

	//		�Q�[���N���A�}�l�[�W���[�̍X�V
	m_clearManager->Update();

	//		�Q�[���X�^�[�g�}�l�[�W���[�̍X�V
	m_gameStart->Update();
}

void UIManager::Finalize()
{
	m_coolTime->Finalize();

	m_clearManager->Finalize();
}

void UIManager::FrontRender()
{
	//		�X�s�[�h���C���̕`��
	m_speedLine->Render();

	//		���v�̕`��
	m_clockManager->Render();

	//		�_�b�V���N�[���^�C���̕`��
	m_coolTime->Render();

	//		�X�N���[���̐��̕`��
	m_standardShader->Render(UIType::ScreenRay);

	//		�Q�[���N���A�}�l�[�W���[�̕`��
	m_clearManager->Render();
}

void UIManager::BackRender()
{
	//		�Q�[���[�o�[�̕`��
	m_gameOver->Render();

	//		�Q�[���X�^�[�g�̕`��
	m_gameStart->Render();
}

void UIManager::CreateStandardUITexture()
{
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/Clock/ClockBackGround.png", { 480.0f, 200.0f }, { 0.8f, 0.8f }, UIType::ClockBackGround);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/Clock/ClockColon.png", { 480.0f, 200.0f }, { 0.8f, 0.8f }, UIType::ClockColon);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/CoolTime/CoolTimeBack.png", { 539.0f, 0.0f }, { 0.6f, 0.6f }, UIType::CloolTimeBackGround);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameOver/GameOver.png", { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameOver);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameOver/Continue.png", { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameOverContinue);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameOver/button.png", { 0.0f, 200.0f }, { 0.6f, 0.6f }, UIType::NextInduction);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/ScreenRay/ScreenRay.png", { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::ScreenRay);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png", { 0.0f, 13.0f }, { 0.0f, 1.0f }, UIType::GameClearBarUp);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png", { 0.0f, -13.0f }, { 0.0f, 1.0f }, UIType::GameClearBarUnder);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBack.png", { 0.0f, 0.0f }, { 1.0f, 0.0f }, UIType::GameClearBackGround);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameStart/TimeLimit.png", { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameStartTimeLimit);
	m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameStart/Ten.png", { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameStartTimeTen);
}
