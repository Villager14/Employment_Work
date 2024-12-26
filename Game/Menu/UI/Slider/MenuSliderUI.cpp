/*
* @file		MenuSliderUI.cpp
* @brief	���j���[�̃X���C�_�[UI
* @author	Morita
* @date		2024/12/20
*/

#include "pch.h"

#include "MenuSliderUI.h"

MenuSliderUI::MenuSliderUI(AboveUI* abvoceUI)
	:
	m_abvoceUI(abvoceUI),
	m_move(0.0f),
	m_effectElapsedTime(0.0f),
	m_type(MenuUITaype::UIType::Empty)
{
	//		�X���C�_�[�̐���
	m_slider = std::make_unique<Slider>();
}

MenuSliderUI::~MenuSliderUI()
{
}

void MenuSliderUI::Initialize()
{
	//		�X���C�_�[�̏���������
	m_slider->Initialize();
}

void MenuSliderUI::Update()
{
}

void MenuSliderUI::Render()
{
	if (m_type == MenuUITaype::Audio)
	{
		AudioRender();
	}
	else if (m_type == MenuUITaype::GamePlay)
	{
		GamePlayRender();
	}
	else if (m_type == MenuUITaype::Option)
	{
		OptionRender();
	}
}

void MenuSliderUI::Finalize()
{
	
}

void MenuSliderUI::AudioRender()
{
	//		�X���C�_�[�̔w�i
	SliderBackGroundRender(m_slider->MASTER_VOLUM_POSITION);
	SliderBackGroundRender(m_slider->BGM_VOLUM_POSITION);
	SliderBackGroundRender(m_slider->SOUND_EFFECT_POSITION);

	//		�X���C�_�[�̖���
	m_abvoceUI->Render(AboveUI::UIType::MastarVolume, m_move);
	m_abvoceUI->Render(AboveUI::UIType::BGMVolume, m_move);
	m_abvoceUI->Render(AboveUI::UIType::SoundEffectVolume, m_move);

	//		�X���C�_�[�̕`��
	m_slider->Render(Slider::BGMVolum, m_move);
	m_slider->Render(Slider::SoundEffect, m_move);
	m_slider->Render(Slider::MastarVolum, m_move);

	//		�X���C�_�[�̃m�u
	m_abvoceUI->Render(AboveUI::UIType::MasterKnob, m_move);
	m_abvoceUI->Render(AboveUI::UIType::BGMKnob, m_move);
	m_abvoceUI->Render(AboveUI::UIType::SoundEffectKnob, m_move);
}

void MenuSliderUI::GamePlayRender()
{
	//m_abvoceUI->Render(AboveUI::UIType::MenuClose, m_move);
	//m_abvoceUI->Render(AboveUI::UIType::Exit, m_move);
}

void MenuSliderUI::OptionRender()
{
	//		�X���C�_�[�̔w�i
	SliderBackGroundRender(m_slider->MOUSE_POSITION);
	SliderBackGroundRender(m_slider->FOV_POSITION);

	//		�X���C�_�[�̖���
	m_abvoceUI->Render(AboveUI::UIType::Mouse, m_move);
	m_abvoceUI->Render(AboveUI::UIType::FOV, m_move);

	//		�X���C�_�[�̕`��
	m_slider->Render(Slider::FOV, m_move);
	m_slider->Render(Slider::Mouse, m_move);

	//		�X���C�_�[�̃m�u
	m_abvoceUI->Render(AboveUI::UIType::MouseKnob, m_move);
	m_abvoceUI->Render(AboveUI::UIType::FOVKnob, m_move);
}

void MenuSliderUI::SliderBackGroundRender(DirectX::SimpleMath::Vector2 position)
{
	(*m_abvoceUI->GetInformation())[AboveUI::UIType::SliderBack].position = position;
	m_abvoceUI->Render(AboveUI::UIType::SliderBack, m_move);
}

void MenuSliderUI::AddMenuColliderInformation(DirectX::SimpleMath::Vector2 position, UISubType type)
{
	MenuColliderInformation information;

	information.position = &position;
	information.subType = type;
	information.type = UIType::Knob;

	m_colliderInformation.push_back(information);
}

void MenuSliderUI::SliderMove(float move)
{
	m_move = move;
}

void MenuSliderUI::SetSliderType(MenuUITaype::UIType type)
{
	m_type = type;

	m_colliderInformation.clear();

	if (m_type == MenuUITaype::Audio)
	{
		////		�����蔻����̍X�V(���ʉ�)
		//AddMenuColliderInformation((*m_abvoceUI->GetInformation())
		//	[AboveUI::UIType::SoundEffectKnob].position, UISubType::SoundEffectVolKnob);
		////		�����蔻����̍X�V(BGM)
		//AddMenuColliderInformation((*m_abvoceUI->GetInformation())
		//	[AboveUI::UIType::BGMKnob].position, UISubType::BGMVolKnob);
		////		�����蔻����̍X�V(�}�X�^�[�{�����[��)
		//AddMenuColliderInformation((*m_abvoceUI->GetInformation())
		//	[AboveUI::UIType::MasterKnob].position, UISubType::MasterVolKnob);
	}
	else if (m_type == MenuUITaype::Option)
	{

	}
}
