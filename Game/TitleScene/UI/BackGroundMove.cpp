/*
* @file		BackGroundMove.h
* @brief	�w�i�̈ړ�
* @author	Morita
* @date		2024/05/24
*/

#include "pch.h"

#include "BackGroundMove.h"

BackGroundMove::BackGroundMove()
	:
	m_time(0.0f),
	m_fadeinResetJudgement(true),
	m_fadeoutResetJudgement(false)
{
}

BackGroundMove::~BackGroundMove()
{
}

void BackGroundMove::Initialize()
{
	//		UI�`��̐���
	m_uiRenderManager = std::make_unique<UIRenderManager>();

	//		�V�F�[�_�[�̐���
	m_uiRenderManager->Create(L"Resources/Texture/TitleScene/TitleBack.png",
		L"Resources/Shader/BackGroundMove/BackGroundMoveVS.cso",
		L"Resources/Shader/BackGroundMove/BackGroundMoveGS.cso",
		L"Resources/Shader/BackGroundMove/BackGroundMovePS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		�E�B���h�E�T�C�Y��ݒ肷��
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

void BackGroundMove::Update()
{
	//		�w�i�̈ړ�����
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;
}

void BackGroundMove::Render()
{
	//		�R���X�g�o�b�t�@�̒l��ݒ肷��
	buffer.rotationMatrix = m_uiRenderManager->GetRotationMatrix();
	buffer.time = { m_time, 0.0f, 0.0f, 0.0f };

	//		�w�i�̕`��
	m_uiRenderManager->Render(buffer);
}

void BackGroundMove::Finalize()
{
}
