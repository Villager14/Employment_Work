/*
* @file		ClockManager.h
* @brief	UI時計のマネージャー
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "ClockBackGround.h"

#include "ClockTime.h"

class ClockManager
{
public:

	ClockManager();

	~ClockManager();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

private:

	//		時計の背景
	std::unique_ptr<ClockBackGround> m_clockBackGround;

	//		時計の数字
	std::unique_ptr<ClockTime> m_clockTime;

	//		経過時間
	float m_elapsedTime;
};