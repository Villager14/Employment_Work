/*
* @file		EndSetting.cpp
* @brief	�I���ݒ�̐ݒ�
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "EndSetting.h"

#include "Scene/SceneManager.h"

#include "../MenuFlowCommonProcess.h"

EndSetting::EndSetting(MenuFlow* menuFlow)
	:
	m_menuFlow(menuFlow),
	m_transitionTitleTime(0.0f),
	m_transitionSettingUITime(0.0f),
	m_startJudgement(true),
	m_endJudgement(false),
	m_transitionRoughTime(1.0f),
	m_menuCloseJudgement(false)
{
}

EndSetting::~EndSetting()
{
}

void EndSetting::Initialize()
{
	m_transitionTitleTime = 0.0f;
	m_transitionSettingUITime = 0.0f;
	m_startJudgement = true;
	m_endJudgement = false;
	m_transitionRoughTime = 1.0f;
	m_menuCloseJudgement = false;

	//		�I�[�f�B�I��I������
	m_menuFlow->GetSelectTypeObserver()->SelectType(MenuUITaype::GamePlay);
}

void EndSetting::Update()
{
	//		���j���[�̑J�ڏ���
	if (m_menuFlow->GetMenuFlowCommonProcess()->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, m_endJudgement, m_menuCloseJudgement))
	{
		//		�^�C�g���I�u�W�F�N�g�̈ړ�����
		m_menuFlow->GetTitleUIUObserver()->TitleMoveProcess(m_transitionSettingUITime);

		//		Tab�I�u�W�F�N�g�̈ړ�����
		m_menuFlow->GetMenuTabUIObserver()->TabMove(m_transitionRoughTime);

		return;
	}

	//		TabUI��I�������Ƃ��̏���
	if (m_menuFlow->TabProcess(MenuFlow::GamePlay))
	{
		m_endJudgement = true;
	}

	//		���j���[����邩�ǂ���
	if (m_menuFlow->FlagJudgement(MenuFlow::K_MenuClose))
	{
		//		���j���[������Ԃɂ���
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}

	//		Exit�{�^�����������ꍇ
	if (m_menuFlow->ButtonHitJudgement(UISubType::GameExitButton))
	{
		//		�Q�[�������
		//PostQuitMessage(0);
		//m_menuManager->GetSceneManager()->GetInformation()->SetEndJudgement(true);
	}

	//		MenuClose�{�^�����������ꍇ
	if (m_menuFlow->ButtonHitJudgement(UISubType::CloseMenuButton))
	{
		//		���j���[������Ԃɂ���
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}
	/*
	//		���j���[�̑J�ڏ���
	if (m_menuManager->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, m_endJudgement, m_menuCloseJudgement)) return;

	//		��܂��ȃ��j���[�{�^���̏���
	if (m_menuManager->GetCommonProcess()->ButtonCollider(MenuInformation::MenuType::GamePlay))
	{
		m_endJudgement = true;
	}

	//		ESC�Ń��j���[���Ƃ��鏈��
	if (m_menuManager->GetCommonProcess()->MenuEscCloseProcess())
	{
		//		���j���[������Ԃɂ���
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}

	//		�{�^���̏���
	ButtonProcess();
	*/
}

void EndSetting::Render()
{
	/*
	m_menuManager->MenuBackRneder();

	//		Option�̃^�C�g���`��
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::GamePlayTitle, m_menuManager->EasingIcon(m_transitionTitleTime));

	//		��܂��ȃ��j���[�̕`��
	m_menuManager->RoughMenuViwe(m_menuManager->EasingIcon(m_transitionRoughTime));

	//		���j���[�I�𒆂̕`��
	if (!m_menuCloseJudgement) m_menuManager->MenuSelectView();

	//		���j���[�����
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MenuClose, m_menuManager->EasingIcon(m_transitionSettingUITime));

	//		���j���[�����̘g
	m_menuManager->GetInformation()->GetFramWalkUI()->Render(m_menuManager->EasingIcon(m_transitionSettingUITime), FrameWalkUI::MenuClear);

	//		Exit
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::Exit, m_menuManager->EasingIcon(m_transitionSettingUITime));

	//		EXIT�̘g
	m_menuManager->GetInformation()->GetFramWalkUI()->Render(m_menuManager->EasingIcon(m_transitionSettingUITime), FrameWalkUI::EXIT);

	//		�}�E�X�|�C���^�̕`��
	m_menuManager->GetCommonProcess()->MousePointa();
	*/
}

void EndSetting::Finalize()
{
}

void EndSetting::ButtonProcess()
{
	/*
	//		���j���[����邩�ǂ���
	if (m_menuManager->GetCommonProcess()->BoxCollider({ 640, 200.0f }, { 1039.0f, 317.0f }))
	{
		//		���N���b�N
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().PRESSED)
		{
			m_endJudgement = true;
			m_menuCloseJudgement = true;

			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);
		}

		//		�������Ă���
		(*m_menuManager->GetInformation()->GetFramWalkUI()->GetFrameInformation())
			[FrameWalkUI::FrameType::MenuClear].boxhitJudgement = true;

	}
	else
	{
		//		�������Ă���
		(*m_menuManager->GetInformation()->GetFramWalkUI()->GetFrameInformation())
			[FrameWalkUI::FrameType::MenuClear].boxhitJudgement = false;
	}

	//		�Q�[������邩�ǂ���
	if (m_menuManager->GetCommonProcess()->BoxCollider({ 640.0f, 351.0f }, { 1039.0f, 470.0f }))
	{
		//		���N���b�N
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().PRESSED)
		{
			//		�Q�[�������
			//PostQuitMessage(0);
			m_menuManager->GetSceneManager()->GetInformation()->SetEndJudgement(true);
		}

		//		�������Ă���
		(*m_menuManager->GetInformation()->GetFramWalkUI()->GetFrameInformation())
			[FrameWalkUI::FrameType::EXIT].boxhitJudgement = true;
	}
	else
	{
		//		�������Ă���
		(*m_menuManager->GetInformation()->GetFramWalkUI()->GetFrameInformation())
			[FrameWalkUI::FrameType::EXIT].boxhitJudgement = false;
	}
	*/
}
