/*
* @file		ResultStay.cpp
* @brief	���U���g�ҋ@����
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "ResultStay.h"

ResultStay::ResultStay(ResultManager* resultManager)
	:
	m_resultManager(resultManager),
	m_time(0.0f)
{
}

ResultStay::~ResultStay()
{
}

void ResultStay::Initialize()
{
}

void ResultStay::Update()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�}�E�X�̎擾
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Space�܂��͍��N���b�N���������ꍇ��������
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		��Ԃ�؂�ւ���(�����ړ����)
		m_resultManager->ChangeState(m_resultManager->GetResultEnd());
	}
}

void ResultStay::Render()
{
	//		UI�w�i�̕`��
	m_resultManager->UIViewProcess(1);

	//		�{�^��
	m_resultManager->UIViewProcess(2);

	//		�����̕`��
	m_resultManager->NumberRender(4.0f);
}

void ResultStay::Finalize()
{
}
