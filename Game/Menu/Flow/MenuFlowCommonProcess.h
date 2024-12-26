/*
* @file		MenuFlowCommonProcess.h
* @brief	���j���[�̗��ꋤ�ʏ���
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "MenuFlow.h"

class MenuFlowCommonProcess
{
public:

	//		�R���X�g���N�^
	MenuFlowCommonProcess(MenuFlow* menuFlow);

	//		�f�X�g���N�^
	~MenuFlowCommonProcess();

	/*
	*	UI�̑J�ڏ���
	*
	*	@param	(transitionTime1)	�J�ڎ��ԂP
	*	@param	(transitionTime2)	�J�ڎ��ԂQ
	*	@param	(transitionTime3)	�J�ڎ��ԂR
	*	@param	(startJudgement)	�X�^�[�g���Ă��邩�ǂ������f����
	*	@param	(endJudgement)		�I��点�邩�ǂ������f����
	*	@param	(moveJudgement)		�J�ڎ��ԂR�𓮂��������f����
	*/
	bool Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3,
		bool* startJudgement, bool endJudgement, bool moveJudgement);

	/*
	*	UI�̑J�ڏ����i�J�n�j
	*
	*	@param	(transitionTime1)	�J�ڎ��ԂP
	*	@param	(transitionTime2)	�J�ڎ��ԂQ
	*	@param	(transitionTime3)	�J�ڎ��ԂR
	*	@param	(startJudgement)	�X�^�[�g���Ă��邩�ǂ������f����
	*	@param	(moveJudgement)		�J�ڎ��ԂR�𓮂��������f����
	*/
	void TransitionStart(float* transitionTime1, float* transitionTime2, float* transitionTime3,
		bool* startJudgement, bool moveJudgement);

	/*
	*	UI�̑J�ڏ����i�I���j
	*
	*	@param	(transitionTime1)	�J�ڎ��ԂP
	*	@param	(transitionTime2)	�J�ڎ��ԂQ
	*	@param	(transitionTime3)	�J�ڎ��ԂR
	*	@param	(moveJudgement)		�J�ڎ��ԂR�𓮂��������f����
	*/
	void TransitionEnd(float* transitionTime1, float* transitionTime2, float* transitionTime3, bool moveJudgement);

private:

	//		�J�ڑ��x
	const float TRANSITION_SPEED = 3.0f;

private:

	MenuFlow* m_menuFlow;
};