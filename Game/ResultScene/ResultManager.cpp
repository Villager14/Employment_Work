/*
* @file		ResultManager.cpp
* @brief	���U���g�}�l�[�W���[
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultManager.h"

#include "State/ResultStart.h"
#include "State/ResultNumberMove.h"
#include "State/ResultEvaluation.h"
#include "State/ResultStay.h"
#include "State/ResultEnd.h"

ResultManager::ResultManager()
	:
	m_score(0),
	m_time(0),
	m_deathCount(0),
	m_iState(),
	m_rotation(0.0f),
	m_changeScene(false),
	m_state{}
{
}

ResultManager::~ResultManager()
{
}

void ResultManager::Initialize(int score, int time, int deathCount)
{
	m_score = score;
	m_time = time;
	m_deathCount = deathCount;

	//		�w�i�̐���
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		�w�i�̏�����
	m_backGroundMove->Initialize();

	//		�����㏸�V�F�[�_�[�̐���
	m_riseNumber = std::make_unique<RiseNumberShader>();

	//		�����㏸�V�F�[�_�[�̏�����
	m_riseNumber->Initialize(m_deathCount, m_time, m_score);
	
	//		UI�`��̐���
	m_fadeRender = std::make_unique<FadeRender>();

	//		UI�`��̍쐻
	m_fadeRender->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		�X�^���_�[�h�V�F�[�_�[�̍쐻
	CreateStandardShader();

	//		��Ԃ��쐬����
	CreateState();

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[�̍쐻
	m_screenEffectManager = std::make_unique<ScreenEffectManager>(nullptr);

	//		�X�N���[���G�t�F�N�g�̏�����
	m_screenEffectManager->Initialize(ScreenEffectManager::ResultScene);

	//		�v���C���[�̃A�j���[�V�����̍쐻
	m_playerAnimation = std::make_unique<PlayerAnimation>();

	//		�v���C���[�̃A�j���[�V����������
	m_playerAnimation->Initialize(true);

	//		�������
	m_playerAnimation->ChangeState(m_playerAnimation->Upright);
}

void ResultManager::Update()
{
	//		��Ԃ̍X�V
	m_iState->Update();

	//		�w�i�̍X�V
	m_backGroundMove->Update();

	//		�v���C���[�̉�]
	m_rotation += LibrarySingleton::GetInstance()->GetElpsedTime() * PLAYER_ROTATION_SPEED;

	//		�v���C���[�̃A�j���[�V����
	m_playerAnimation->Execute(0.0f, PLAYER_POSITION, { m_rotation, 0.0f }, PLAYER_HEIGHT);
}

void ResultManager::Render()
{
	//		�����_�[�^�[�Q�b�g�̕ύX
	m_screenEffectManager->ChangeRenderTarget();

	//		�v���C���[�̕`��(���C���[)
	m_playerAnimation->Render(true);

	//		�����_�[�^�[�Q�b�g��߂�
	m_screenEffectManager->FirstRenderTarget();

	//		�ړ��w�i�̕`��
	m_backGroundMove->Render();

	//		�w�i�̕`��(UI)
	m_shader->Render(ResultUIType::Back);

	//		�����_�[�^�[�Q�b�g�̕`��
	m_screenEffectManager->Render();

	//		��Ԃ̕`��
	m_iState->Render();
}

void ResultManager::Finalize()
{
}


void ResultManager::CreateState()
{
	//		��Ԃ𐶐�����
	m_stateInformation.insert({State::Start, std::make_unique<ResultStart>(this)});
	m_stateInformation.insert({ State::NumberMove, std::make_unique<ResultNumberMove>(this) });
	m_stateInformation.insert({ State::Evaluation, std::make_unique<ResultEvaluation>(this) });
	m_stateInformation.insert({ State::Stay, std::make_unique<ResultStay>(this) });
	m_stateInformation.insert({ State::End, std::make_unique<ResultEnd>(this) });

	//		������Ԃ�������
	m_state = State::Start;

	//		������Ԃ�ݒ肷��
	m_iState = m_stateInformation[m_state].get();

	//		��Ԃ�����������
	m_iState->Initialize();
}

void ResultManager::AnimationSkip()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�}�E�X�̎擾
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Space�܂��͍��N���b�N���������ꍇ��������
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		��Ԃ�؂�ւ���(�ҋ@���)
		m_iState = m_stateInformation[State::Stay].get();
	}
}

void ResultManager::CreateStandardShader()
{
	//		���U���gUI�}�l�[�W���[�̐���
	m_shader = std::make_unique<StandardShader<ResultManager::ResultUIType>>();

	//		����������
	m_shader->Initialize();

	//		�w�i�摜
	m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ResultBack.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f },
		ResultManager::ResultUIType::Back);

	//		�X�R�A�ɂ���ĕ]����ς���
	if (2000.0f > m_score)
	{
		//		A�]���̐���
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreA.png",
			{ 350.0f, 150.0f }, { 0.0f, 0.0f },
			ResultManager::ResultUIType::EvaluationUI);
	}
	else if (1000.0f > m_score)
	{
		//		B�]���̐���
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreB.png",
			{ 350.0f, 150.0f }, { 0.0f, 0.0f },
			ResultManager::ResultUIType::EvaluationUI);
	}
	else
	{
		//		C�]���̐���
		m_shader->CreateUIInformation(L"Resources/Texture/ResultScene/ScoreC.png",
			{ 350.0f, 150.0f }, { 0.0f, 0.0f },
			ResultManager::ResultUIType::EvaluationUI);
	}

	//		���̃V�[���U���̐���
	m_shader->CreateUIInformation(L"Resources/Texture/UI/GameOver/button.png",
		{ 0.0f, 280.0f }, { 1.0f, 1.0f },
		ResultManager::ResultUIType::Button);
}

void ResultManager::ChangeState(State state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I������������
	m_iState->Finalize();

	m_state = state;

	//		��Ԃ�؂�ւ���
	m_iState = m_stateInformation[state].get();

	//		�V������Ԃ̏���������������
	m_iState->Initialize();
}
