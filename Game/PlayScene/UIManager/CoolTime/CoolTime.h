/*
* @file		CoolTime.h
* @brief	�N�[���^�C��
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "../CircleShader.h"

class CoolTime
{
public:

	CoolTime();

	~CoolTime();

	void Initialize();

	void Update();

	void Render();

	void Finalize();


private:

	//		�����̕`��
	std::unique_ptr<CircleShader> m_circleShader;

	//		�p�x
	float m_angle;

	//		����
	float m_time;
};
