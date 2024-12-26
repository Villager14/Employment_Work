/*
* @file		MenuFlowCommonProcess.cpp
* @brief	メニューの流れ共通処理
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
		//		メニュー開始時のUIの動き
		TransitionStart(transitionTime1, transitionTime2, transitionTime3, startJudgement, moveJudgement);

		return true;
	}

	if (endJudgement)
	{
		//		メニュー終了時のUIの動き
		TransitionEnd(transitionTime1, transitionTime2, transitionTime3, moveJudgement);

		return true;
	}


	return false;
}

void MenuFlowCommonProcess::TransitionStart(float* transitionTime1, float* transitionTime2, float* transitionTime3, bool* startJudgement, bool moveJudgement)
{
	//		開始状態の場合
	if (*startJudgement)
	{
		//		時間1の更新
		*transitionTime1 += LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;

		//		時間1が一定時間以上になったら他の時間も更新する
		if (*transitionTime1 > 0.3f)
		{
			//		時間2の更新
			*transitionTime2 += LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;

			//		時間2が一定時間以上3遷移フラグがオンの場合時間3の更新をする
			if (*transitionTime2 > 0.3f && moveJudgement)
			{
				//		時間3の更新
				*transitionTime3 += LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;
			}
		}

		//		1以上にならないようにする
		*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
		*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
		*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

		//		Iconの移動処理
		m_menuFlow->IconMoveProcess(*transitionTime1);

		//		3の更新をする場合
		if (moveJudgement)
		{
			//		3の更新が終わったら
			if (*transitionTime3 >= 1.0f)
			{
				//		開始状態を終了する
				*startJudgement = false;
			}
		}
		else
		{
			//		2の更新が終わったら
			if (*transitionTime2 >= 1.0f)
			{
				//		開始状態を終了する
				*startJudgement = false;
			}
		}
	}
}

void MenuFlowCommonProcess::TransitionEnd(float* transitionTime1, float* transitionTime2, float* transitionTime3, bool moveJudgement)
{
	//		時間1の更新
	*transitionTime1 -= LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;

	//		時間1が一定時間以下になったら他の時間も更新する
	if (*transitionTime1 < 0.7f)
	{
		//		時間2の更新
		*transitionTime2 -= LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;

		//		時間2が一定時間以下3遷移フラグがオンの場合時間3の更新をする
		if (*transitionTime2 < 0.7f && moveJudgement)
		{
			//		時間3の更新
			*transitionTime3 -= LibrarySingleton::GetInstance()->GetElpsedTime() * TRANSITION_SPEED;
		}
	}

	//		0以下にならないようにする
	*transitionTime1 = Library::Clamp(*transitionTime1, 0.0f, 1.0f);
	*transitionTime2 = Library::Clamp(*transitionTime2, 0.0f, 1.0f);
	*transitionTime3 = Library::Clamp(*transitionTime3, 0.0f, 1.0f);

	//m_menuIconUIObserver->IconMoveProcess(*transitionTime1);
	//		Iconの移動処理
	m_menuFlow->IconMoveProcess(*transitionTime1);

	if (moveJudgement)
	{
		if (*transitionTime3 <= 0.0f)
		{
			//		シーンを切り替える
			m_menuFlow->ChangState(MenuFlow::MenuType::Close);
		}
	}
	else
	{
		if (*transitionTime2 <= 0.0f)
		{
			//		シーンを切り替える
			m_menuFlow->ChangState(m_menuFlow->GetNextType());
		}
	}
}
