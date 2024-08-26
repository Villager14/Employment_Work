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
	m_angle(360.0f),
	m_time(0.0f),
	m_coolTimeJudgement(false),
	m_ratio(100.0f),
	m_state(),
	m_uiManager(uiManager)
{
	//		��]�V�F�[�_�[�̐���
	m_rotataionShader = std::make_unique<UIRenderManager>();

	//		��]�V�F�[�_�[�̍쐻
	m_rotataionShader->Create(L"Resources/Texture/UI/CoolTime/CoolTime.png",
		L"Resources/Shader/CoolTime/CoolTimeVS.cso",
		L"Resources/Shader/CoolTime/CoolTimeGS.cso",
		L"Resources/Shader/CoolTime/CoolTimePS.cso",
		buffer,
		{ 270.0f, 0.0f }, { 0.6f, 0.6f });

	//		�V�F�[�_�[�`��}�l�[�W���[�̐���
	m_shader = std::make_unique<UIRenderManager>();

	//		�����V�F�[�_�[�̍쐻
	m_shader->Create(L"Resources/Texture/UI/CoolTime/cooltimeNumber.png",
		L"Resources/Shader/Number/NumberVS.cso",
		L"Resources/Shader/Number/NumberGS.cso",
		L"Resources/Shader/Number/NumberPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 0.3f, 0.3f });
}

CoolTime::~CoolTime()
{
}

void CoolTime::Initialize()
{
	//		�E�B���h�E�T�C�Y��ݒ肷��
	circleBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	circleBuffer.rotationMatrix = m_rotataionShader->GetRotationMatrix();

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	buffer.rotationMatrix = m_shader->GetRotationMatrix();

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
	m_uiManager->GetStandardShader()->Render(UIManager::UIType::CloolTimeBackGround);

	//		��]�ʂ�ݒ肷��
	circleBuffer.rotation = { m_angle, 0.0f, 0.0f, 0.0f };

	//		����̕`��
	m_rotataionShader->Render(circleBuffer);

	//		�����̕`��
	NumberView();
}

void CoolTime::Finalize()
{
}

void CoolTime::NumberView()
{
	//		�����̐ݒ�(�S�̈�)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio / 100)), 0.0f, 0.0f, 0.0f };
	//		�����̍��W�ݒ�(�S�̈�)
	m_shader->SetPosition({ NUMBER_CENTER_POSITION - NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		�����̕`��i�S�̈ʁj
	m_shader->Render(buffer);

	//		�����̐ݒ�(�\�̈�)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio) % 100 / 10), 0.0f, 0.0f, 0.0f };
	//		�����̍��W�ݒ�(�\�̈�)
	m_shader->SetPosition({ NUMBER_CENTER_POSITION, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		�����̕`��i�\�̈ʁj
	m_shader->Render(buffer);

	//		�����̐ݒ�(��̈�)
	buffer.number = { static_cast<float>(static_cast<int>(m_ratio) % 100 % 10), 0.0f, 0.0f, 0.0f };
	//		�����̍��W�ݒ�(��̈�)
	m_shader->SetPosition({ NUMBER_CENTER_POSITION + NUMBER_INTERVAL, LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f });
	//		�����̕`��i��̈ʁj
	m_shader->Render(buffer);
}
