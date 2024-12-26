/*
* @file		MenuBackGround.h
* @brief	���j���[�̔w�i
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuBackGround.h"

MenuBackGround::MenuBackGround()
{
}

MenuBackGround::~MenuBackGround()
{
}

void MenuBackGround::Initialize()
{
	//		�X�^���_�[�h�V�F�[�_�[�̐���
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	//		�X�^���_�[�h�V�F�[�_�[�̏���������
	m_standardShader->Initialize();

	m_standardShader->CreateUIInformation(MESSAGE_BACK_FILE_PATH,
		{ 0.0f, 0.0f }, { 0.0f, 1.0f }, UIType::BackGround);
	m_standardShader->CreateUIInformation(MESSAGE_BAR_FILE_PATH,
		MESSAGE_BAR1_CLOSE_POSITION, { 0.0f, 1.0f }, UIType::Bar1);
	m_standardShader->CreateUIInformation(MESSAGE_BAR_FILE_PATH,
		MESSAGE_BAR2_CLOSE_POSITION, { 0.0f, 1.0f }, UIType::Bar2);
}

void MenuBackGround::Update()
{
}

void MenuBackGround::Render()
{
	//		�S�Ă�UI�`�揈��
	for (int i = 0; i < static_cast<int>
		(m_standardShader->GetUIInformation()->size()); ++i)
	{
		m_standardShader->Render(UIType(i));
	}
}

void MenuBackGround::Finalize()
{
}

void MenuBackGround::BarScale(float scale)
{
	//		�o�[1�̃X�P�[���̕ύX
	(*m_standardShader->GetUIInformation())[UIType::Bar1].scale = { scale, 1.0f };
	//		�o�[2�̃X�P�[���̕ύX
	(*m_standardShader->GetUIInformation())[UIType::Bar2].scale = { scale, 1.0f };
}

void MenuBackGround::MenuMoveProcess(float move)
{
	//		�o�[�P�̈ړ�
	(*m_standardShader->GetUIInformation())[UIType::Bar1].position =
		DirectX::SimpleMath::Vector2::Lerp
		(MESSAGE_BAR1_CLOSE_POSITION, MESSAGE_BAR1_OPEN_POSITION, move);

	//		�o�[�Q�̈ړ�
	(*m_standardShader->GetUIInformation())[UIType::Bar2].position =
		DirectX::SimpleMath::Vector2::Lerp
		(MESSAGE_BAR2_CLOSE_POSITION, MESSAGE_BAR2_OPEN_POSITION, move);

	//		�w�i�̃X�P�[���ύX
	(*m_standardShader->GetUIInformation())[UIType::BackGround].scale =
	{ 1.0f, Library::Lerp(0.0f, 1.0f, move) };
		
}
