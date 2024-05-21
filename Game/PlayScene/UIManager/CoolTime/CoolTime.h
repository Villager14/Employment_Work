/*
* @file		CoolTime.h
* @brief	クールタイム
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

	//		数字の描画
	std::unique_ptr<CircleShader> m_circleShader;

	//		角度
	float m_angle;

	//		時間
	float m_time;
};
