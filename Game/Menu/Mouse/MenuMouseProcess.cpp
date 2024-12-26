/*
* @file		MenuMouseProcess.h
* @brief	���j���[�̃}�E�X����
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuMouseProcess.h"

MenuMouseProcess::MenuMouseProcess()
{
	m_menuMouseObserver = std::make_unique<MenuMouseObserver>();
}

MenuMouseProcess::~MenuMouseProcess()
{
}

void MenuMouseProcess::Initialize()
{
	//		�}�E�X�𑊑Έʒu�ɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_ABSOLUTE);
}

void MenuMouseProcess::Update()
{
	//		�}�E�X�̍��W
	int mousePositionX = 0;
	int mousePositionY = 0;

	//		�}�E�X�̌��ݍ��W���󂯎��
	mousePositionX = LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x;
	mousePositionY = LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y;

	//		�}�E�X�̍��W���X�V�����ꍇ
	if (mousePositionX != m_mousePositionX)
	{
		//		�}�E�X�̍��W�̍X�V
		m_mousePositionX = mousePositionX;

		//		�}�E�X�̃I�u�U�[�o�[X���W�̍X�V
		m_menuMouseObserver->MousePositionX(m_mousePositionX);
	}

	if (mousePositionY != m_mousePositionY)
	{
		//		�}�E�X�̍��W�̍X�V
		m_mousePositionY = mousePositionY;
		
		//		�}�E�X�̃I�u�U�[�o�[Y���W�̍X�V
		m_menuMouseObserver->MousePositionY(m_mousePositionY);
	}
}

void MenuMouseProcess::Finalize()
{
	//		�}�E�X���΃��[�h
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_mousePositionX = 0;

	m_mousePositionY = 0;
}
