/*
* @file		ClockTime.h
* @brief	UIŒv‚Ì”š
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "../NumberShader.h"

class ClockTime
{
public:

	ClockTime();

	~ClockTime();

	void Initialize();

	void Update(float elapsedTime);

	void Render();

	void Finalize();


private:

	//		”š‚Ì•`‰æ
	std::unique_ptr<NumberShader> m_numberShader;

	//		ŠÔ
	int m_time;

};
