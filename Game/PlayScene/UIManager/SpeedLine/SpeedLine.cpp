

#include "pch.h"

#include "SpeedLine.h"

SpeedLine::SpeedLine(UIManager* uiManager)
	:
	m_uiManager(uiManager),
	m_time(1.0f),
	m_frontTime(1.0f),
	frontFlag(false)
{
	m_shader = std::make_unique<UIRenderManager>();
}

SpeedLine::~SpeedLine()
{
}

void SpeedLine::Initialize()
{
	//		��]�V�F�[�_�[�̍쐻
	m_shader->Create(L"Resources/Texture/UI/Speed/UISpeed.png",
		L"Resources/Shader/SpeedLine/SpeedLineVS.cso",
		L"Resources/Shader/SpeedLine/SpeedLineGS.cso",
		L"Resources/Shader/SpeedLine/SpeedLinePS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		��]�ʂ�ݒ肷��
	buffer.rotationMatrix = m_shader->GetRotationMatrix();

	m_frontTime = 1.0f;
	m_time = 1.0f + LINE_LENGTH;
}

void SpeedLine::Update()
{
	//		�_�b�V�������Ă��邩�ǂ���
	if (!m_uiManager->GetGameManager()->
		FlagJudgement(GameManager::DashJudgement))
	{
		if (m_frontTime < 1.0f)
		{
			m_frontTime = 1.0f;
			m_time = 1.0f + LINE_LENGTH;
		}

		return;
	}

	//		�o�ߎ���
	m_time -= LibrarySingleton::GetInstance()->GetElpsedTime() * SPEED;

	if (m_time <= 1.0f - LINE_LENGTH && frontFlag)
	{
		frontFlag = false;

		m_frontTime = 1.0f - LINE_LENGTH;
		m_time = 1.0f;
	}


	m_frontTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * SPEED;

	if (m_frontTime <= 0.0f)
	{
		m_frontTime = LINE_LENGTH;

		m_time = 1.0f;

		frontFlag = true;
	}


	//		�R���X�g�o�b�t�@�̎��Ԃ̍X�V
	buffer.time = { m_time, m_frontTime,
		static_cast<float>(frontFlag), 0.0f};
}

void SpeedLine::Render()
{
	//		�_�b�V�������Ă��邩�ǂ���
	if (!m_uiManager->GetGameManager()->
		FlagJudgement(GameManager::DashJudgement))
	{
		return;
	}

	//		UI�̕`��
	m_shader->Render(buffer);
}

void SpeedLine::Finalize()
{
}
