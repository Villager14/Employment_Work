/*
* @file		MenuAudioUI.cpp
* @brief	���j���[�I�[�f�B�IUI�̃^�C�g��
* @author	Morita
* @date		2024/12/25
*/

#include "pch.h"

#include "MenuAudioUI.h"

MenuAudioUI::MenuAudioUI(AboveUI* aboveUI,
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

MenuAudioUI::~MenuAudioUI()
{
}

void MenuAudioUI::Initialize()
{
	//		�����蔻��̒ǉ�
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::BGMKnob].position, UISubType::BGMKnob);
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::SoundEffectKnob].position, UISubType::SoundEffectKnob);
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::MasterKnob].position, UISubType::MastarVolumKnob);

	m_colliderJudgement = true;
}

void MenuAudioUI::Update()
{
	//		�^�C�g�����オ��؂����瓖���蔻����I���ɂ���
	if (m_titleMove >= 1.0f && m_colliderJudgement
		&& m_type == MenuUITaype::UIType::Audio)
	{
		//		�����蔻���ǉ�
		m_summarizeColliderInformation->AddCollider(m_colliderInformation);

		//		�t���O���I���ɂ���
		m_colliderJudgement = false;
	}
	//		Audio�ȊO�̏ꍇ
	else if (m_type != MenuUITaype::UIType::Audio)
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

void MenuAudioUI::Render()
{
	//		�Q�[���v���C�ȊO�̏ꍇ���������Ȃ�
	if (m_type != MenuUITaype::UIType::Audio) {return;}

	//		�^�C�g��
	m_aboveUI->Render(AboveUI::UIType::AudioTitle, m_titleMove);

	//		�X���C�_�[�̔w�i
	SliderBackGroundRender(m_slider->MASTER_VOLUM_POSITION);
	SliderBackGroundRender(m_slider->BGM_VOLUM_POSITION);
	SliderBackGroundRender(m_slider->SOUND_EFFECT_POSITION);

	//		�X���C�_�[�̖���
	m_aboveUI->Render(AboveUI::UIType::MastarVolume, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::BGMVolume, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::SoundEffectVolume, m_buttonMove);

	//		�X���C�_�[�̕`��
	m_slider->Render(Slider::BGMVolum, m_buttonMove);
	m_slider->Render(Slider::SoundEffect, m_buttonMove);
	m_slider->Render(Slider::MastarVolum, m_buttonMove);

	//		�X���C�_�[�̃m�u
	m_aboveUI->Render(AboveUI::UIType::MasterKnob, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::BGMKnob, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::SoundEffectKnob, m_buttonMove);
}

void MenuAudioUI::Finalize()
{
	m_colliderInformation.clear();
}

void MenuAudioUI::SetType(MenuUITaype::UIType type)
{
	m_type = type;
}

void MenuAudioUI::SliderBackGroundRender(DirectX::SimpleMath::Vector2 position)
{
	(*m_aboveUI->GetInformation())[AboveUI::UIType::SliderBack].position = position;
	m_aboveUI->Render(AboveUI::UIType::SliderBack, m_buttonMove);
}

void MenuAudioUI::TitleMoveProcess(float move)
{
	m_titleMove = move;
}

void MenuAudioUI::ButtonMoveProcess(float move)
{
	m_buttonMove = move;
}

void MenuAudioUI::AddMenuColliderInformation(DirectX::SimpleMath::Vector2* position, UISubType type)
{
	MenuColliderInformation information;

	information.position = position;
	information.subType = type;
	information.type = UIType::Knob;

	m_colliderInformation.push_back(information);
}
