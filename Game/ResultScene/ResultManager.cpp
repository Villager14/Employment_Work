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
	m_deathCount(0)
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

	//		��Ԃ��쐬����
	CreateState();
}

void ResultManager::Update()
{
	//		��Ԃ̍X�V
	m_state->Update();

	//		�w�i�̍X�V
	m_backGroundMove->Update();
}

void ResultManager::Render()
{
	//		�w�i�̕`��
	m_backGroundMove->Render();

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
	//		���U���g�X�^�[�g�𐶐�����
	m_resultStart = std::make_unique<ResultStart>(this);
	//		�ԍ��ړ��𐶐�����
	m_resultNumberMove = std::make_unique<ResultNumberMove>(this);

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
	AboveNumberView(3, m_time / 60 / 10, Library::Clamp(time, 0.9f, 1.9f) - 0.9);
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
