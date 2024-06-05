/*
* @file		CoolTime.h
* @brief	�N�[���^�C��
* @author	Morita
* @date		2024/05/20
*/
#include "pch.h"

#include "CoolTime.h"

CoolTime::CoolTime()
	:
	m_angle(360.0f),
	m_time(0.0f),
	m_coolTimeJudgement(false),
	m_ratio(100.0f),
	m_state()
{
}

CoolTime::~CoolTime()
{
}

void CoolTime::Initialize()
{
	//		�����V�F�[�_�[�̐���
	m_circleShader = std::make_unique<CircleShader>();

	float scale = 0.6f;

	//		�N�[���^�C���V�F�[�_�[�̍쐻
	m_circleShader->Create(L"Resources/Texture/UI/CoolTime/CoolTime.png",
		{270.0f, 0.0f}, { scale, scale });
		
	//		�w�i�V�F�[�_�[�̐���
	m_backRender = std::make_unique<UIRender>();

	//		�w�i�V�F�[�_�[�̍쐻
	m_backRender->Create(L"Resources/Texture/UI/CoolTime/CoolTimeBack.png",
		{ 539.0f, 0.0f }, { scale, scale });

	//		�����V�F�[�_�[�̐���
	m_numberShader = std::make_unique<NumberShader>();

	//		�����V�F�[�_�[�̍쐻
	m_numberShader->Create(L"Resources/Texture/UI/CoolTime/cooltimeNumber.png",
		{ 1200.0f, 360.0f }, { 0.3f, 0.3f });

	//		�����Ȃ����
	m_state = State::None;
}

void CoolTime::Update(PlayerInformation* playerInformation)
{
	//		�N�[���^�C�����������Ă��Ȃ��ꍇ�������s��
	if (!m_coolTimeJudgement)
	{
		//		�_�b�V���N�[���^�C���ɓ�������
		if (playerInformation->GetDashCoolTime() > 0.0f)
		{
			//		�N�[���^�C����Ԃɂ���
			m_coolTimeJudgement = true;

			//		�p�x���ő�ɂ���
			m_angle = 360.0f;

			//		�������ő�ɂ���
			m_ratio = 100.0f;

			//		���炷���
			m_state = State::Reduce;
		}
	}

	//		��Ԃ��������Ȃ��ꍇ���������Ȃ�
	if (m_state == State::None) return;

	//		���炷���
	if (m_state == State::Reduce)
	{
		//		�_�b�V������
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 3.0f;

		if (m_time >= 1.0f)
		{
			//		���₷��Ԃɂ���
			m_state = State::Increase;

			m_time = 1.0f;
		}
	}
	//		���₷���
	else if (m_state == State::Increase)
	{
		//		�N�[���^�C��
		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * 0.6f;

		if (m_time <= 0.0f)
		{
			//		�������Ȃ���Ԃɂ���
			m_state = State::None;

			m_time = 0.0f;

			m_coolTimeJudgement = false;
		}
	}

	//		�p�x��ݒ肷��
	m_angle = Library::Lerp(360.0f, 0.0f, m_time);

	//		������ݒ肷��
	m_ratio = Library::Lerp(100.0f, 0.0f, m_time);

}

void CoolTime::Render()
{
	//		�w�i�̕`��
	m_backRender->Render();


	//		�~�̕`��
	m_circleShader->Render(static_cast<int>(m_angle));

	

	//		�����V�F�[�_�[�̍��W��ݒ肷��i�S�̈ʁj
	m_numberShader->SetPosition({ NUMBER_CENTER_POSITION - NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		�����̕`��i�S�̈ʁj
	m_numberShader->Render(static_cast<int>(m_ratio / 100));
	//		�����V�F�[�_�[�̍��W��ݒ肷��i�\�̈ʁj
	m_numberShader->SetPosition({ NUMBER_CENTER_POSITION, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		�����̕`��i�\�̈ʁj
	m_numberShader->Render(static_cast<int>(m_ratio) % 100 / 10);
	//		�����V�F�[�_�[�̍��W��ݒ肷��i��̈ʁj
	m_numberShader->SetPosition({ NUMBER_CENTER_POSITION + NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		�����̕`��i��̈ʁj
	m_numberShader->Render(static_cast<int>(m_ratio) % 100 % 10);
}

void CoolTime::Finalize()
{
}
