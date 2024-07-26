/*
* @file		FrameWalk.cpp
* @brief	�g�̏���
* @author	Morita
* @date		2024/07/18
*/

#include "pch.h"

#include "FrameWalkUI.h"

FrameWalkUI::FrameWalkUI()
	:
	m_time(0.0f),
	m_move(0.0f)
{
}

FrameWalkUI::~FrameWalkUI()
{
}

void FrameWalkUI::Initialize()
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(L"Resources/Texture/Menu/GamePlay/MenuFramework.png",
		L"Resources/Shader/FrameWalk/FrameWalkVS.cso",
		L"Resources/Shader/FrameWalk/FrameWalkGS.cso",
		L"Resources/Shader/FrameWalk/FrameWalkPS.cso",
		m_constBuffer,
		{ 200.0f, -100.0f }, { 1.0f,1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		��]�s��𑗂�
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		�E�B���h�E�T�C�Y�𑗂�
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	CreateFrameInformtion(FrameType::MenuClear, { 200.0f, -100.0f });
	CreateFrameInformtion(FrameType::EXIT, { 200.0f, 50.0f });

}

void FrameWalkUI::Render(float time, FrameType type)
{
	//		�{�b�N�X�ɓ������Ă��邩
	if (m_frameInformation[type].boxhitJudgement)
	{
		//		�������Ă���ꍇ�g���L����
		m_frameInformation[type].move += LibrarySingleton::GetInstance()->GetElpsedTime() * 5.0f;
	}
	else
	{
		//		�������Ă��Ȃ��ꍇ�g�����߂�
		m_frameInformation[type].move -= LibrarySingleton::GetInstance()->GetElpsedTime() * 5.0f;
	}

	//		���Ԃ�1�ȏ�O�ȉ��ɂȂ�Ȃ��悤�ɂ���
	m_frameInformation[type].move = Library::Clamp(m_frameInformation[type].move, 0.0f, 1.0f);

	//		�C�[�W���O�֐�
	m_frameInformation[type].time = 1.0f - pow(1.0f - m_frameInformation[type].move, 4.0f);

	//		�R���X�g�o�b�t�@�Ɏ��Ԃ̒l��n��
	m_constBuffer.time = { time, m_frameInformation[type].time, 0.0f, 0.0f};
	
	//		�V�F�[�_�[�̍��W��ݒ肷��
	m_shader->SetPosition(m_frameInformation[type].position);

	//		�`��
	m_shader->Render(m_constBuffer);
}

void FrameWalkUI::CreateFrameInformtion(FrameType type, DirectX::SimpleMath::Vector2 position)
{
	UIInformation infor;
	infor.position = position;

	m_frameInformation.insert({ type, infor });
}

void FrameWalkUI::Reset()
{
	for (auto e : m_frameInformation)
	{
		e.second.boxhitJudgement = false;
		e.second.time = 0.0f;
		e.second.move = 0.0f;
	}
}