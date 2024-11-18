/*
* @file		OptionSetting.cpp
* @brief	�I�v�V�����̐ݒ�
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "OptionSetting.h"

OptionSetting::OptionSetting(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
	m_transitionTitleTime(0.0f),
	m_transitionSettingUITime(0.0f),
	m_startJudgement(true),
	m_endJudgement(false),
	m_menuCloseJudgement(false),
	m_transitionRoughTime(1.0f)
{
}

OptionSetting::~OptionSetting()
{
}

void OptionSetting::Initialize()
{
}

void OptionSetting::Update()
{
	//		���j���[�̑J�ڏ���
	if (m_menuManager->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, m_endJudgement, m_menuCloseJudgement)) return;

	//		ESC�Ń��j���[���Ƃ��鏈��
	if (m_menuManager->GetCommonProcess()->MenuEscCloseProcess())
	{
		//		���j���[������Ԃɂ���
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}

	//		��܂��ȃ��j���[�{�^���̏���
	if (m_menuManager->GetCommonProcess()->ButtonCollider(MenuInformation::MenuType::Option))
	{
		m_endJudgement = true;
	}

	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::FOVKnob);
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::MouseKnob);

	//		����p�̍X�V
	m_menuManager->GetInformation()->SetViewAngle(Library::Lerp(FOV_MIN_VAL, FOV_MAX_VAL,
		m_menuManager->GetCommonProcess()->SliderVal(AboveUI::UIType::FOVKnob, Slider::UIType::FOV)));

	//		�}�E�X���x�̍X�V
	m_menuManager->GetInformation()->SetCameraSpeed(Library::Lerp(MOUSE_SENSITIVITY_MIN, MOUSE_SENSITIVITY_MAX,
		m_menuManager->GetCommonProcess()->SliderVal(AboveUI::UIType::MouseKnob, Slider::UIType::Mouse)));
}

void OptionSetting::Render()
{
	//		���j���[�̔w�i�̕`��
	m_menuManager->MenuBackRneder();

	//		Option�̃^�C�g���`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::OptionTitle, m_menuManager->EasingIcon(m_transitionTitleTime));

	//		���j���[�I�𒆂̕`��
	if (!m_menuCloseJudgement) m_menuManager->MenuSelectView();

	//		��܂��ȃ��j���[�̕`��
	m_menuManager->RoughMenuViwe(m_menuManager->EasingIcon(m_transitionRoughTime));

	float transitionTime = m_menuManager->EasingIcon(m_transitionSettingUITime);

	//		�X���C�_�[�̔w�i���W�P
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = SLIDER_POSITION1;

	//		�X���C�_�[�w�i�`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	//		FOV�̃e�L�X�g�`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::FOV, transitionTime);
	//		FOV�̃X���C�_�[�`��
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::FOV, transitionTime);
	//		�X���C�_�[�̃m�u�`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::FOVKnob, transitionTime);

	//		�X���C�_�[�̔w�i���W�Q
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = SLIDER_POSITION2;
	//		�X���C�_�[�w�i�`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	//		�}�E�X���x�e�L�X�g�`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::Mouse, transitionTime);
	//		�}�E�X���x�̃X���C�_�[�`��
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::Mouse, transitionTime);
	//		�X���C�_�[�̃m�u�`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MouseKnob, transitionTime);

	//		�}�E�X�|�C���^�̕`��
	m_menuManager->GetCommonProcess()->MousePointa();
}

void OptionSetting::Finalize()
{
	m_transitionTitleTime = 0.0f;
	m_transitionSettingUITime = 0.0f;
	m_startJudgement = true;
	m_endJudgement = false;
	m_menuCloseJudgement = false;
	m_transitionRoughTime = 1.0f;
}
