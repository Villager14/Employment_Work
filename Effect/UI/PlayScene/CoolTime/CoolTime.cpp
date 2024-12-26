/*
* @file		CoolTime.h
* @brief	�N�[���^�C��
* @author	Morita
* @date		2024/05/20
*/
#include "pch.h"

#include "CoolTime.h"

CoolTime::CoolTime(UIManager* uiManager)
	:
	m_angle(MAX_ANGLE),
	m_time(0.0f),
	m_ratio(RATO),
	m_uiManager(uiManager)
{
}

CoolTime::~CoolTime()
{
}

void CoolTime::Initialize()
{
	//		��]�V�F�[�_�[�̐���
	m_coolTImeShader = std::make_unique<UIRenderManager>();

	//		�V�F�[�_�[�`��}�l�[�W���[�̐���
	m_coolTimeNumberShader = std::make_unique<UIRenderManager>();

	//		�N�[���^�C��UI�̍쐻
	m_coolTImeShader->Create(COOL_TIME_TEXTURE_PATH,
		COOL_TIME_VS_PATH, COOL_TIME_GS_PATH,
		COOL_TIME_PS_PATH, buffer,
		COOL_TIME_POSITION, { 0.6f, 0.6f });

	//		�����V�F�[�_�[�̍쐻
	m_coolTimeNumberShader->Create(COOL_TIME_NUMBER_TEXTURE_PATH,
		NUMBER_VS_PATH, NUMBER_GS_PATH,
		NUMBER_PS_PATH, buffer,
		{ 0.0f, 0.0f }, { 0.3f, 0.3f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	circleBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	circleBuffer.rotationMatrix = m_coolTImeShader->GetRotationMatrix();

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	buffer.rotationMatrix = m_coolTimeNumberShader->GetRotationMatrix();
}

void CoolTime::Update(float coolTime)
{
	//		���炷���
	if (coolTime <=  0.5f)
	{
		//		�_�b�V������
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * DASH_SPEED;
	}
	else
	{
		//		�N�[���^�C��
		m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * COOL_TIME_SPEED;
	}

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		�p�x��ݒ肷��
	m_angle = Library::Lerp(MAX_ANGLE, 0.0f, m_time);

	//		������ݒ肷��
	m_ratio = Library::Lerp(RATO, 0.0f, m_time);
}

void CoolTime::Render()
{
	//		�w�i�̕`��
	m_uiManager->GetStandardShader()->Render(UIManager::UIType::CloolTimeBackGround);

	//		��]�ʂ�ݒ肷��
	circleBuffer.rotation = { m_angle, 0.0f, 0.0f, 0.0f };

	//		����̕`��
	m_coolTImeShader->Render(circleBuffer);

	//		�����̕`��
	NumberView();
}

void CoolTime::Finalize()
{
	m_angle = MAX_ANGLE;
	m_time = 0.0f;
	m_ratio = RATO;

	m_coolTImeShader.reset();
	m_coolTimeNumberShader.reset();
}

void CoolTime::NumberView()
{
	//		�����̐ݒ�(�S�̈�)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio / 100)), 0.0f, 0.0f, 0.0f };
	//		�����̍��W�ݒ�(�S�̈�)
	m_coolTimeNumberShader->SetPosition({ NUMBER_CENTER_POSITION - NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		�����̕`��i�S�̈ʁj
	m_coolTimeNumberShader->Render(buffer);

	//		�����̐ݒ�(�\�̈�)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio) % 100 / 10), 0.0f, 0.0f, 0.0f };
	//		�����̍��W�ݒ�(�\�̈�)
	m_coolTimeNumberShader->SetPosition({ NUMBER_CENTER_POSITION, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		�����̕`��i�\�̈ʁj
	m_coolTimeNumberShader->Render(buffer);

	//		�����̐ݒ�(��̈�)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio) % 100 % 10), 0.0f, 0.0f, 0.0f };
	//		�����̍��W�ݒ�(��̈�)
	m_coolTimeNumberShader->SetPosition({ NUMBER_CENTER_POSITION + NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		�����̕`��i��̈ʁj
	m_coolTimeNumberShader->Render(buffer);
}