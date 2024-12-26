/*
* @file		MenuFlowCommonProcess.h
* @brief	ƒƒjƒ…[‚Ì—¬‚ê‹¤’Êˆ—
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "MenuFlow.h"

class MenuFlowCommonProcess
{
public:

	//		ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	MenuFlowCommonProcess(MenuFlow* menuFlow);

	//		ƒfƒXƒgƒ‰ƒNƒ^
	~MenuFlowCommonProcess();

	/*
	*	UI‚Ì‘JˆÚˆ—
	*
	*	@param	(transitionTime1)	‘JˆÚŠÔ‚P
	*	@param	(transitionTime2)	‘JˆÚŠÔ‚Q
	*	@param	(transitionTime3)	‘JˆÚŠÔ‚R
	*	@param	(startJudgement)	ƒXƒ^[ƒg‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©”»’f‚·‚é
	*	@param	(endJudgement)		I‚í‚ç‚¹‚é‚©‚Ç‚¤‚©”»’f‚·‚é
	*	@param	(moveJudgement)		‘JˆÚŠÔ‚R‚ğ“®‚©‚·‚©”»’f‚·‚é
	*/
	bool Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3,
		bool* startJudgement, bool endJudgement, bool moveJudgement);

	/*
	*	UI‚Ì‘JˆÚˆ—iŠJnj
	*
	*	@param	(transitionTime1)	‘JˆÚŠÔ‚P
	*	@param	(transitionTime2)	‘JˆÚŠÔ‚Q
	*	@param	(transitionTime3)	‘JˆÚŠÔ‚R
	*	@param	(startJudgement)	ƒXƒ^[ƒg‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©”»’f‚·‚é
	*	@param	(moveJudgement)		‘JˆÚŠÔ‚R‚ğ“®‚©‚·‚©”»’f‚·‚é
	*/
	void TransitionStart(float* transitionTime1, float* transitionTime2, float* transitionTime3,
		bool* startJudgement, bool moveJudgement);

	/*
	*	UI‚Ì‘JˆÚˆ—iI—¹j
	*
	*	@param	(transitionTime1)	‘JˆÚŠÔ‚P
	*	@param	(transitionTime2)	‘JˆÚŠÔ‚Q
	*	@param	(transitionTime3)	‘JˆÚŠÔ‚R
	*	@param	(moveJudgement)		‘JˆÚŠÔ‚R‚ğ“®‚©‚·‚©”»’f‚·‚é
	*/
	void TransitionEnd(float* transitionTime1, float* transitionTime2, float* transitionTime3, bool moveJudgement);

private:

	//		‘JˆÚ‘¬“x
	const float TRANSITION_SPEED = 3.0f;

private:

	MenuFlow* m_menuFlow;
};