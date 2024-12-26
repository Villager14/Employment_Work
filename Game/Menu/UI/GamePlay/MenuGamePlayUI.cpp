/*
* @file		MenuGamePlayUI.cpp
* @brief	���j���[�Q�[���v���CUI�̃^�C�g��
* @author	Morita
* @date		2024/12/23
*/

#include "pch.h"

#include "MenuGamePlayUI.h"

MenuGamePlayUI::MenuGamePlayUI(AboveUI* aboveUI,
	MenuSummarizeColliderInformation* summarizeColliderInformation)
	:
	m_aboveUI(aboveUI),
	m_titleMove(0.0f),
	m_summarizeColliderInformation(summarizeColliderInformation),
	m_colliderJudgement(false)
{
	//		�t���[�����[�NUI�̐���
	m_frameWalkUI = std::make_unique<FrameWalkUI>();
}

MenuGamePlayUI::~MenuGamePlayUI()
{
}

void MenuGamePlayUI::Initialize()
{
	m_colliderJudgement = false;

	m_frameWalkUI->Initialize();

	//		�����蔻��̒ǉ�
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::MenuClose].position, UISubType::CloseMenuButton);
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::Exit].position, UISubType::GameExitButton);
}

void MenuGamePlayUI::Update()
{
	m_frameWalkUI->Update(FrameWalkUI::FrameType::EXIT);
	m_frameWalkUI->Update(FrameWalkUI::FrameType::MenuClear);

	if (m_type == MenuUITaype::UIType::GamePlay)
	{
		//		�����蔻��t���O���I�t�ɂ���
		for (auto& e : (*m_frameWalkUI->GetFrameInformation()))
		{
			e.second.boxhitJudgement = false;
		}
	}

	//		�^�C�g�����オ��؂����瓖���蔻����I���ɂ���
	if (m_titleMove >= 1.0f && m_colliderJudgement
		&& m_type == MenuUITaype::UIType::GamePlay)
	{
		//		�����蔻���ǉ�
		m_summarizeColliderInformation->AddCollider(m_colliderInformation);

		//		�t���O���I���ɂ���
		m_colliderJudgement = false;
	}
	//		GamePlay�ȊO�̏ꍇ
	else if (m_type != MenuUITaype::UIType::GamePlay)
	{
		//		�����蔻�肪�I�t�̏ꍇ
		if (!m_colliderJudgement)
		{
			//		�����蔻��̍폜
			m_summarizeColliderInformation->DeleteCollider(m_colliderInformation);

			//		�t���O���I�t�ɂ���
			m_colliderJudgement = true;

			//		�����蔻��t���O���I�t�ɂ���
			for (auto& e : (*m_frameWalkUI->GetFrameInformation()))
			{
				e.second.boxhitJudgement = false;
			}
		}
	}
}

void MenuGamePlayUI::Render()
{
	//		�Q�[���v���C�ȊO�̏ꍇ���������Ȃ�
	if (m_type != MenuUITaype::UIType::GamePlay) {return;}

	//		�^�C�g��
	m_aboveUI->Render(AboveUI::UIType::GamePlayTitle, m_titleMove);

	//		�{�^��
	m_aboveUI->Render(AboveUI::UIType::MenuClose, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::Exit, m_buttonMove);

	m_frameWalkUI->Render(m_buttonMove, FrameWalkUI::FrameType::EXIT);
	m_frameWalkUI->Render(m_buttonMove, FrameWalkUI::FrameType::MenuClear);
}

void MenuGamePlayUI::Finalize()
{
	m_colliderInformation.clear();
}

void MenuGamePlayUI::SetType(MenuUITaype::UIType type)
{
	m_type = type;
}

void MenuGamePlayUI::TitleMoveProcess(float move)
{
	m_titleMove = move;
}

void MenuGamePlayUI::ButtonMoveProcess(float move)
{
	m_buttonMove = move;
}

void MenuGamePlayUI::AddMenuColliderInformation(DirectX::SimpleMath::Vector2* position, UISubType type)
{
	MenuColliderInformation information;

	information.position = position;
	information.subType = type;
	information.type = UIType::Button;

	m_colliderInformation.push_back(information);
}

void MenuGamePlayUI::HitBunnton(UISubType type)
{
	if (type == UISubType::GameExitButton)
	{
		(*m_frameWalkUI->GetFrameInformation())[FrameWalkUI::FrameType::EXIT].boxhitJudgement = true;
	}
	else if (type == UISubType::CloseMenuButton)
	{
		(*m_frameWalkUI->GetFrameInformation())[FrameWalkUI::FrameType::MenuClear].boxhitJudgement = true;
	}
}
