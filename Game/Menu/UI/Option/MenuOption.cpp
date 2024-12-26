/*
* @file		MenuOption.cpp
* @brief	���j���[�I�v�V����UI�̃^�C�g��
* @author	Morita
* @date		2024/12/25
*/

#include "pch.h"

#include "MenuOption.h"

MenuOption::MenuOption(AboveUI* aboveUI,
	Slider* slider,
	MenuSummarizeColliderInformation* summarizeColliderInformation)
	:
	m_aboveUI(aboveUI),
	m_slider(slider),
	m_titleMove(0.0f),
	m_buttonMove(0.0f),
	m_colliderJudgement(false),
	m_type(MenuUITaype::UIType::Empty),
	m_summarizeColliderInformation(summarizeColliderInformation)
{
}

MenuOption::~MenuOption()
{
}

void MenuOption::Initialize()
{
	//		�����蔻��̒ǉ�
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::MouseKnob].position, UISubType::MouseSpeedKnob);
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::FOVKnob].position, UISubType::FovKnob);

	m_colliderJudgement = true;
}

void MenuOption::Update()
{
	//		�^�C�g�����オ��؂����瓖���蔻����I���ɂ���
	if (m_titleMove >= 1.0f && m_colliderJudgement
		&& m_type == MenuUITaype::UIType::Option)
	{
		//		�����蔻���ǉ�
		m_summarizeColliderInformation->AddCollider(m_colliderInformation);

		//		�t���O���I���ɂ���
		m_colliderJudgement = false;
	}
	//		Option�ȊO�̏ꍇ
	else if (m_type != MenuUITaype::UIType::Option)
	{
		//		�����蔻�肪�I�t�̏ꍇ
		if (!m_colliderJudgement)
		{
			//		�����蔻��̍폜
			m_summarizeColliderInformation->DeleteCollider(m_colliderInformation);

			//		�t���O���I�t�ɂ���
			m_colliderJudgement = true;
		}
	}
}

void MenuOption::Render()
{
	//		�Q�[���v���C�ȊO�̏ꍇ���������Ȃ�
	if (m_type != MenuUITaype::UIType::Option) {return;}

	//		�^�C�g��
	m_aboveUI->Render(AboveUI::UIType::OptionTitle, m_titleMove);

	//		�X���C�_�[�̔w�i
	SliderBackGroundRender(m_slider->FOV_POSITION);
	SliderBackGroundRender(m_slider->MOUSE_POSITION);

	//		�X���C�_�[�̖���
	m_aboveUI->Render(AboveUI::UIType::FOV, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::Mouse, m_buttonMove);

	//		�X���C�_�[�̕`��
	m_slider->Render(Slider::Mouse, m_buttonMove);
	m_slider->Render(Slider::FOV, m_buttonMove);

	//		�X���C�_�[�̃m�u
	m_aboveUI->Render(AboveUI::UIType::FOVKnob, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::MouseKnob, m_buttonMove);
}

void MenuOption::Finalize()
{
	m_colliderInformation.clear();
}

void MenuOption::SetType(MenuUITaype::UIType type)
{
	m_type = type;
}

void MenuOption::SliderBackGroundRender(DirectX::SimpleMath::Vector2 position)
{
	(*m_aboveUI->GetInformation())[AboveUI::UIType::SliderBack].position = position;
	m_aboveUI->Render(AboveUI::UIType::SliderBack, m_buttonMove);
}

void MenuOption::TitleMoveProcess(float move)
{
	m_titleMove = move;
}

void MenuOption::ButtonMoveProcess(float move)
{
	m_buttonMove = move;
}

void MenuOption::AddMenuColliderInformation(DirectX::SimpleMath::Vector2* position, UISubType type)
{
	MenuColliderInformation information;

	information.position = position;
	information.subType = type;
	information.type = UIType::Knob;

	m_colliderInformation.push_back(information);
}
