/*
* @file		MenuFlowCommonProcess.cpp
* @brief	���j���[�̗��ꋤ�ʏ���
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuFlowCommonProcess.h"

#include "../UI/MenuUITabEnums.h"

MenuFlowCommonProcess::MenuFlowCommonProcess(MenuFlow* menuFlow)
	:
	m_menuFlow(menuFlow)
{
}

MenuFlowCommonProcess::~MenuFlowCommonProcess()
{
}

bool MenuFlowCommonProcess::Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3, bool* startJudgement, bool endJudgement, bool moveJudgement)
{
	if (*startJudgement)
	{
		//		���j���[�J�n����UI�̓���
		TransitionStart(transitionTime1, transitionTime2, transitionTime3, startJudgement, moveJudgement);

		return true;
	}

	if (endJudgement)
	{
		//		���j���[�I������UI�̓���
		TransitionEnd(transitionTime1, transitionTime2, transitionTime3, moveJudgement);

		return true;
	}


	return false;
}

void MenuFlowCommonProcess::TransitionStart(float* transitionTime1, float* transitionTime2, float* transitionTime3, bool* startJudgement, bool moveJudgement)
{
	//		�J�n��Ԃ̏ꍇ
	if (*startJudgement)
	{
		//		����1�̍X�V
		*transitionTime1 += LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;

		//		����1����莞�Ԉȏ�ɂȂ����瑼�̎��Ԃ��X�V����
		if (*transitionTime1 > 0.3f)
		{
			//		����2�̍X�V
			*transitionTime2 += LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;

			//		����2����莞�Ԉȏ�3�J�ڃt���O���I���̏ꍇ����3�̍X�V������
			if (*transitionTime2 > 0.3f && moveJudgement)
			{
				//		����3�̍X�V
				*transitionTime3 += LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;
			}
		}

		//		1�ȏ�ɂȂ�Ȃ��悤�ɂ���
		*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
		*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
		*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

		//		Icon�̈ړ�����
		m_menuFlow->IconMoveProcess(*transitionTime1);

		//		3�̍X�V������ꍇ
		if (moveJudgement)
		{
			//		3�̍X�V���I�������
			if (*transitionTime3 >= 1.0f)
			{
				//		�J�n��Ԃ��I������
				*startJudgement = false;
			}
		}
		else
		{
			//		2�̍X�V���I�������
			if (*transitionTime2 >= 1.0f)
			{
				//		�J�n��Ԃ��I������
				*startJudgement = false;
			}
		}
	}
}

void MenuFlowCommonProcess::TransitionEnd(float* transitionTime1, float* transitionTime2, float* transitionTime3, bool moveJudgement)
{
	//		����1�̍X�V
	*transitionTime1 -= LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;

	//		����1����莞�Ԉȉ��ɂȂ����瑼�̎��Ԃ��X�V����
	if (*transitionTime1 < 0.7f)
	{
		//		����2�̍X�V
		*transitionTime2 -= LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;

		//		����2����莞�Ԉȉ�3�J�ڃt���O���I���̏ꍇ����3�̍X�V������
		if (*transitionTime2 < 0.7f && moveJudgement)
		{
			//		����3�̍X�V
			*transitionTime3 -= LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;
		}
	}

	//		0�ȉ��ɂȂ�Ȃ��悤�ɂ���
	*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
	*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
	*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

	//m_menuIconUIObserver->IconMoveProcess(*transitionTime1);
	//		Icon�̈ړ�����
	m_menuFlow->IconMoveProcess(*transitionTime1);

	if (moveJudgement)
	{
		if (*transitionTime3 <= 0.0f)
		{
			//		�V�[����؂�ւ���
			m_menuFlow->ChangState(MenuFlow::MenuType::Close);
		}
	}
	else
	{
		if (*transitionTime2 <= 0.0f)
		{
			//		�V�[����؂�ւ���
			m_menuFlow->ChangState(m_menuFlow->GetNextType());
		}
	}
}
