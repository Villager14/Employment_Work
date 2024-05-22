/*
* @file		FadeIn.h
* @brief	フェードの処理
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

	//		フェードの描画
	std::unique_ptr<FadeRender> m_fadeRender;

	//		時間
	float m_time;
};
