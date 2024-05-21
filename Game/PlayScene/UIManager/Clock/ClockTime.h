/*
* @file		ClockTime.h
* @brief	UI時計の数字
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

	//		数字の描画
	std::unique_ptr<NumberShader> m_numberShader;

	//		時間
	int m_time;

};
