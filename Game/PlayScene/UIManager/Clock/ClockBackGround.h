/*
* @file		ClockBackGround.h
* @brief	UIŒv‚Ì”wŒi
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "../UIRender.h"

class ClockBackGround
{
public:

	ClockBackGround();

	~ClockBackGround();

	void Initialize();

	void Update(float elapsedTime);

	void Render();

	void Finalize();


private:

	//		UI‚Ì•`‰æ
	std::unique_ptr<UIRender> m_uiRender;

	//		ƒRƒƒ“‚Ì•`‰æ
	std::unique_ptr<UIRender> m_colonRender;

	float m_rotationMin;

	float m_rotationMax;

	bool m_rotationUpdateJudgement;

	float m_pastTime;
};
