/*
* @file		ResultManager.cpp
* @brief	���U���g�}�l�[�W���[
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultManager.h"

ResultManager::ResultManager()
	:
	m_score(0),
	m_time(0),
	m_deathCount(0),
	m_state(),
	m_rotation(0.0f),
	m_changeScene(false)
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

	//		���S��
	for (int i = 0; i < 3; ++i)
	{
		//		��ړ������̐���
		m_aboveNumber.push_back(std::make_unique<AboveNumber>());

		//		�㐔���̍쐻
		m_aboveNumber[i]->Create(L"Resources/Texture/ResultScene/nomber.png", {970.0f + 60.0f * i, 140.0f}, {1.0f, 1.0f});
	}
	
	//		����
	for (int i = 0; i < 4; ++i)
	{
		//		��ړ������̐���
		m_aboveNumber.push_back(std::make_unique<AboveNumber>());

		//		�㐔���̍쐻
		m_aboveNumber[i + 3]->Create(L"Resources/Texture/ResultScene/nomber.png", { 910.0f + 60.0f * i, 250.0f }, { 1.0f, 1.0f });
	}

	//		����
	for (int i = 0; i < 4; ++i)
	{
		//		��ړ������̐���
		m_aboveNumber.push_back(std::make_unique<AboveNumber>());

		//		�㐔���̍쐻
		m_aboveNumber[i + 7]->Create(L"Resources/Texture/ResultScene/nomber.png", { 910.0f + 60.0f * i, 360.0f }, { 1.0f, 1.0f });
	}

	//		UI�`��̐���
	m_fadeRender = std::make_unique<FadeRender>();

	//		UI�`��̍쐻
	m_fadeRender->Create(L"Resources/Texture/UI/Fade/BlackTexture.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });
	
	//		�w�iUI�̍쐻
	AddRenderUI(L"Resources/Texture/ResultScene/ResultBack.png", { 0.0f, 0.0f }, { 1.0f, 1.0f });

	if (m_score >= 2000.0f)
	{
		//		�w�iUI�̍쐻
		AddRenderUI(L"Resources/Texture/ResultScene/ScoreA.png", { 350.0f, 150.0f }, { 0.0f, 0.0f });
	}
	else if (m_score >= 1000.0f)
	{
		//		�w�iUI�̍쐻
		AddRenderUI(L"Resources/Texture/ResultScene/ScoreB.png", { 350.0f, 150.0f }, { 0.0f, 0.0f });
	}
	else
	{
		//		�w�iUI�̍쐻
		AddRenderUI(L"Resources/Texture/ResultScene/ScoreC.png", { 350.0f, 150.0f }, { 0.0f, 0.0f });
	}

	//		UI�`��̍쐻(Continue)
	AddRenderUI(L"Resources/Texture/UI/GameOver/button.png",
		{ 0.0f, 280.0f }, { 1.0f, 1.0f });

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
	m_state->Update();

	//		�w�i�̍X�V
	m_backGroundMove->Update();

	m_rotation += LibrarySingleton::GetInstance()->GetElpsedTime() * 30.0f;

	m_playerAnimation->Execute(0.0f, { 0.0f, 0.0f, 8.0f }, { m_rotation, 0.0f }, 2.5f);
}

void ResultManager::Render()
{
	//		�����_�[�^�[�Q�b�g�̕ύX
	m_screenEffectManager->ChangeRenderTarget();

	m_playerAnimation->Render(true);

	//		�����_�[�^�[�Q�b�g��߂�
	m_screenEffectManager->FirstRenderTarget();


	//		�w�i�̕`��
	m_backGroundMove->Render();

	//		UI�w�i�̕`��
	m_uiRender[0]->Render();

	//		�����_�[�^�[�Q�b�g�̕`��
	m_screenEffectManager->Render();

	//		��Ԃ̕`��
	m_state->Render();
}

void ResultManager::Finalize()
{
}

void ResultManager::ChangeState(IResultManager* state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I������������
	m_state->Finalize();

	//		��Ԃ�؂�ւ���
	m_state = state;

	//		�V������Ԃ̏���������������
	m_state->Initialize();
}

void ResultManager::CreateState()
{
	//		�X�^�[�g��Ԃ𐶐�����
	m_resultStart = std::make_unique<ResultStart>(this);
	//		�ԍ��ړ���Ԃ𐶐�����
	m_resultNumberMove = std::make_unique<ResultNumberMove>(this);
	//		�]����Ԃ𐶐�����
	m_resultEvaluation = std::make_unique<ResultEvaluation>(this);
	//		�ҋ@��Ԃ𐶐�����
	m_resultStay = std::make_unique<ResultStay>(this);
	//		�I����Ԃ𐶐�����
	m_resultEnd = std::make_unique<ResultEnd>(this);
	//		������Ԃ�ݒ肷��
	m_state = m_resultStart.get();

	//		��Ԃ�����������
	m_state->Initialize();
}

void ResultManager::NumberRender(float time)
{
	//		���S�񐔕\��
	AboveNumberView(0, (m_deathCount / 100) % 10,	Library::Clamp(time, 0.0f, 1.0f));
	AboveNumberView(1, (m_deathCount / 10) % 10,	Library::Clamp(time, 0.3f, 1.3f) - 0.3f);
	AboveNumberView(2,  m_deathCount % 10,			Library::Clamp(time, 0.6f, 1.6f) - 0.6f);

	//		�N���A����
	AboveNumberView(3, m_time / 60 / 10, Library::Clamp(time, 0.9f, 1.9f) - 0.9f);
	AboveNumberView(4, m_time / 60 % 10, Library::Clamp(time, 1.2f, 2.2f) - 1.2f);
	AboveNumberView(5, m_time % 60 / 10, Library::Clamp(time, 1.5f, 2.5f) - 1.5f);
	AboveNumberView(6, m_time % 60 % 10, Library::Clamp(time, 1.8f, 2.8f) - 1.8f);

	//		�X�R�A�\��
	AboveNumberView(7,  m_score / 1000,			Library::Clamp(time, 2.1f, 3.1f) - 2.1f);
	AboveNumberView(8, (m_score / 100) % 10,	Library::Clamp(time, 2.4f, 3.4f) - 2.4f);
	AboveNumberView(9, (m_score / 10) % 10,		Library::Clamp(time, 2.7f, 3.7f) - 2.7f);
	AboveNumberView(10, m_score % 10,			Library::Clamp(time, 3.0f, 4.0f) - 3.0f);
}

void ResultManager::AddRenderUI(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 size)
{
	//		UI�����_�[�̐���
	std::unique_ptr<UIRender> uiRender = std::make_unique<UIRender>();

	//		UI�̍쐻
	uiRender->Create(path, position, size);

	m_uiPosition.push_back(position);

	m_uiSize.push_back(size);

	//		UI�̒ǉ�
	m_uiRender.push_back(std::move(uiRender));
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
		m_state = m_resultStay.get();
	}
}
