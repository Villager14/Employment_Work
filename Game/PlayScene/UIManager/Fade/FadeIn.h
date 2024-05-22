/*
* @file		FadeIn.h
* @brief	�t�F�[�h�̏���
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "FadeRender.h"

class FadeIn
{
public:

	FadeIn();

	~FadeIn();

	void Initialize();

	void Update();

	void Render();

	void Finalize();


private:

	//		�t�F�[�h�̕`��
	std::unique_ptr<FadeRender> m_fadeRender;

	//		����
	float m_time;
};
