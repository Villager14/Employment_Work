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
#include "Effect/UI/PlayScene/GameOver/GameOverManager.h"
#include "Effect/UI/PlayScene/GameClear/GameClearManager.h"
#include "Effect/UI/PlayScene/SpeedLine/SpeedLine.h"
#include "Effect/UI/PlayScene/GameStart/GameStart.h"
#include "Effect/UI/PlayScene/CountDown/CountDown.h"

UIManager::UIManager(GameManager* gameManager)
	:
	m_gameManager(gameManager)
{
	Generation();
}

UIManager::~UIManager()
{
}

void UIManager::Initialize()
{
	//		�X�^���_�[�h�V�F�[�_�[�̍쐻
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	//		�X�^���_�[�h�V�F�[�_�[�̏�����
	m_standardShader->Initialize();

	//		UI�e�N�X�`���̍쐻
	CreateStandardUITexture();

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

	//		�J�E���g�_�E���̏���������
	m_countDonw->Initialize();
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

	//		�J�E���g�_�E���̐���
	m_countDonw = std::make_unique<CountDown>();
}

void UIManager::Update()
{
	//		���Ԃ̍X�V
	m_clockManager->Update(m_gameManager);

	//		�Q�[���I�[�o�[�̍X�V
	m_gameOver->Update();

	//		�Q�[���N���A�}�l�[�W���[�̍X�V
	m_clearManager->Update();

	//		�Q�[���X�^�[�g�}�l�[�W���[�̍X�V
	m_gameStart->Update();

	//		�J�E���g�_�E���̍X�V����
	m_countDonw->Update(m_gameManager->GetLimitTime() - m_clockManager->GetElapsedTime());
}

void UIManager::Finalize()
{
	m_standardShader.reset();

	m_clockManager->Finalize();

	m_coolTime->Finalize();

	m_gameOver->Finalize();

	m_speedLine->Finalize();

	m_clearManager->Finalize();

	m_gameStart->Finalize();

	m_countDonw->Finalize();
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
	//		�J�E���g�_�E��
	m_countDonw->Render();

	//		�Q�[���[�o�[�̕`��
	m_gameOver->Render();

	//		�Q�[���X�^�[�g�̕`��
	m_gameStart->Render();
}

void UIManager::CreateStandardUITexture()
{
	m_standardShader->CreateUIInformation(CLOCK_BACK_GROUND_PAHT, CLOCK_BACK_GROUND_POSITION, { 0.8f, 0.8f }, UIType::ClockBackGround);
	m_standardShader->CreateUIInformation(CLOCK_COLON_TEXTURE_PATH, CLOCK_BACK_GROUND_POSITION, { 0.8f, 0.8f }, UIType::ClockColon);
	m_standardShader->CreateUIInformation(COOL_TIME_BACK_TEXTURE_PATH, CLOCK_BACK_TIME_GROUND_POSITION, { 0.6f, 0.6f }, UIType::CloolTimeBackGround);
	m_standardShader->CreateUIInformation(GAME_OVER_TEXTURE_PATH, { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameOver);
	m_standardShader->CreateUIInformation(CONTINUE_TEXTURE_PATH, { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameOverContinue);
	m_standardShader->CreateUIInformation(BUTTON_TEXTURE_PATH, NEXT_INDCCTION, { 0.6f, 0.6f }, UIType::NextInduction);
	m_standardShader->CreateUIInformation(SCREEN_RAY_TEXTURE_PATH, { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::ScreenRay);
	m_standardShader->CreateUIInformation(MESSAGE_BAR_TEXTURE_PATH, MESSAGE_BER_UP, { 0.0f, 1.0f }, UIType::GameClearBarUp);
	m_standardShader->CreateUIInformation(MESSAGE_BAR_TEXTURE_PATH, MESSAGE_BER_DOWN, { 0.0f, 1.0f }, UIType::GameClearBarUnder);
	m_standardShader->CreateUIInformation(MESSAGE_BACK_FILE_PATH, { 0.0f, 0.0f }, { 1.0f, 0.0f }, UIType::GameClearBackGround);
	m_standardShader->CreateUIInformation(TIME_LIMIT_TEXTURE_PATH, { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameStartTimeLimit);
	m_standardShader->CreateUIInformation(TEN_TEXTURE_PATH, { 0.0f, 0.0f }, { 1.0f, 1.0f }, UIType::GameStartTimeTen);
}

void UIManager::DashCoolTime(float coolTime)
{
	m_coolTime->Update(coolTime);
}

void UIManager::NowSpeed(float speed)
{
	m_speedLine->Update(speed);
}