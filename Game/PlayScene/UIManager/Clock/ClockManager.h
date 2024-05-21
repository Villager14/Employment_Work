/*
* @file		ClockManager.h
* @brief	UI���v�̃}�l�[�W���[
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

	//		���v�̔w�i
	std::unique_ptr<ClockBackGround> m_clockBackGround;

	//		���v�̐���
	std::unique_ptr<ClockTime> m_clockTime;

	//		�o�ߎ���
	float m_elapsedTime;
};