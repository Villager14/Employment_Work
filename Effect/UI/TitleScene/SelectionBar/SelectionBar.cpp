/*
* @file		SelectionBar.cpp
* @brief	�I���o�[
* @author	Morita
* @date		2024/12/12
*/
#include "pch.h"

#include "SelectionBar.h"

SelectionBar::SelectionBar()
{
	//		�I���o�[�ړ������̐���
	m_selectionBarMoveProcess = std::make_unique<SelectionBarMoveProcess>(this);
}

SelectionBar::~SelectionBar()
{
}

void SelectionBar::Initialize()
{
	//		���SUI��Play�ɂ���
	m_centerType = UIType::Play;

	//		UI�̐���
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	//		�X�^���_�[�h�V�F�[�_�[�̏���������
	m_standardShader->Initialize();

	//		Play�̐���
	m_standardShader->CreateUIInformation(TITLE_PLAY_TEXTURE_PATH,
		CENTER_POINT, { MAX_SCALE, MAX_SCALE },
		UIType::Play);

	//		End�̐���
	m_standardShader->CreateUIInformation(TITLE_END_TEXTURE_PATH,
		UP_POINT, { MIN_SCALE, MIN_SCALE },
		UIType::End);

	//		Setting�̐���
	m_standardShader->CreateUIInformation(TITLE_SETTING_TEXTURE_PATH,
		UNDER_POINT, { MIN_SCALE, MIN_SCALE },
		UIType::Setting);
}

void SelectionBar::Render()
{
	//		UI�̕`��
	for (int i = 0; i < m_standardShader->GetUIInformation()->size(); ++i)
	{
		m_standardShader->Render(UIType(i));
	}
}

void SelectionBar::Finalize()
{
	m_standardShader.reset();
}

void SelectionBar::UpSelect(float processingTime)
{
	int centerToTop = 0;
	int centerToBottom = 0;
	int fromTopToBottom = 0;

	if (m_centerType == UIType::Play)
	{
		centerToTop = UIType::Play;
		centerToBottom = UIType::Setting;
		fromTopToBottom = UIType::End;
	}
	else if (m_centerType == UIType::End)
	{
		centerToTop = UIType::End;
		centerToBottom = UIType::Play;
		fromTopToBottom = UIType::Setting;
	}
	else if (m_centerType == UIType::Setting)
	{
		centerToTop = UIType::Setting;
		centerToBottom = UIType::End;
		fromTopToBottom = UIType::Play;
	}

	//		��ƒ��S�̈ړ�����
	m_selectionBarMoveProcess->CenterToTopProcess(true, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(centerToTop)].position,
		&(*m_standardShader->GetUIInformation())[UIType(centerToTop)].scale);

	//		���ƒ��S�̈ړ�����
	m_selectionBarMoveProcess->CenterToBottom(true, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(centerToBottom)].position,
		&(*m_standardShader->GetUIInformation())[UIType(centerToBottom)].scale);

	//		��Ɖ��̈ړ�����
	m_selectionBarMoveProcess->FromTopToBottom(true, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(fromTopToBottom)].position,
		&(*m_standardShader->GetUIInformation())[UIType(fromTopToBottom)].scale);

	//		���Ԃ��o�߂�����
	if (processingTime >= 1.0f)
	{
		//		���SUI��ς���
		m_centerType = UIType(centerToBottom);
	}
}

void SelectionBar::DownSelect(float processingTime)
{
	int centerToTop = 0;
	int centerToBottom = 0;
	int fromTopToBottom = 0;

	if (m_centerType == UIType::Play)
	{
		centerToTop = UIType::End;
		centerToBottom = UIType::Play;
		fromTopToBottom = UIType::Setting;
	}
	else if (m_centerType == UIType::End)
	{
		centerToTop = UIType::Setting;
		centerToBottom = UIType::End;
		fromTopToBottom = UIType::Play;
	}
	else if (m_centerType == UIType::Setting)
	{
		centerToTop = UIType::Play;
		centerToBottom = UIType::Setting;
		fromTopToBottom = UIType::End;
	}

	//		��ƒ��S�̈ړ�����
	m_selectionBarMoveProcess->CenterToTopProcess(false, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(centerToTop)].position,
		&(*m_standardShader->GetUIInformation())[UIType(centerToTop)].scale);

	//		���ƒ��S�̈ړ�����
	m_selectionBarMoveProcess->CenterToBottom(false, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(centerToBottom)].position,
		&(*m_standardShader->GetUIInformation())[UIType(centerToBottom)].scale);

	//		��Ɖ��̈ړ�����
	m_selectionBarMoveProcess->FromTopToBottom(false, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(fromTopToBottom)].position,
		&(*m_standardShader->GetUIInformation())[UIType(fromTopToBottom)].scale);

	//		���Ԃ��o�߂�����
	if (processingTime >= 1.0f)
	{
		//		���SUI��ς���
		m_centerType = UIType(centerToTop);
	}
}
