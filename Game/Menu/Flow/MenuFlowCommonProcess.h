/*
* @file		MenuFlowCommonProcess.h
* @brief	メニューの流れ共通処理
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "MenuFlow.h"

class MenuFlowCommonProcess
{
public:

	//		コンストラクタ
	MenuFlowCommonProcess(MenuFlow* menuFlow);

	//		デストラクタ
	~MenuFlowCommonProcess();

	/*
	*	UIの遷移処理
	*
	*	@param	(transitionTime1)	遷移時間１
	*	@param	(transitionTime2)	遷移時間２
	*	@param	(transitionTime3)	遷移時間３
	*	@param	(startJudgement)	スタートしているかどうか判断する
	*	@param	(endJudgement)		終わらせるかどうか判断する
	*	@param	(moveJudgement)		遷移時間３を動かすか判断する
	*/
	bool Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3,
		bool* startJudgement, bool endJudgement, bool moveJudgement);

	/*
	*	UIの遷移処理（開始）
	*
	*	@param	(transitionTime1)	遷移時間１
	*	@param	(transitionTime2)	遷移時間２
	*	@param	(transitionTime3)	遷移時間３
	*	@param	(startJudgement)	スタートしているかどうか判断する
	*	@param	(moveJudgement)		遷移時間３を動かすか判断する
	*/
	void TransitionStart(float* transitionTime1, float* transitionTime2, float* transitionTime3,
		bool* startJudgement, bool moveJudgement);

	/*
	*	UIの遷移処理（終了）
	*
	*	@param	(transitionTime1)	遷移時間１
	*	@param	(transitionTime2)	遷移時間２
	*	@param	(transitionTime3)	遷移時間３
	*	@param	(moveJudgement)		遷移時間３を動かすか判断する
	*/
	void TransitionEnd(float* transitionTime1, float* transitionTime2, float* transitionTime3, bool moveJudgement);

private:

	//		遷移速度
	const float TRANSITION_SPEED = 3.0f;

private:

	MenuFlow* m_menuFlow;
};