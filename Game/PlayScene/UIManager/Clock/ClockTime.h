/*
* @file		ClockTime.h
* @brief	UI���v�̐���
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

	//		�����̕`��
	std::unique_ptr<NumberShader> m_numberShader;

	//		����
	int m_time;

};
