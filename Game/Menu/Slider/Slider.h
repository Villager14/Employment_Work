/*
* @file		Slider.h
* @brief	スライダーの処理
* @author	Morita
* @date		2024/07/03
*/
#pragma once

//#include "FadeRender.h"

#include "Game/PlayScene/GameManager/GameManager.h"

class Slider
{
public:

	Slider();

	~Slider();

	void Initialize();

	void Update(GameManager* gameManager);

	void Render();

	void Finalize();


private:

	//		フェードの描画
	//std::unique_ptr<FadeRender> m_fadeRender;

	//		時間
	float m_time;

	//		待機時間
	float m_stayTime;

	//		フェードインをするかどうか判断する
	bool m_fadeinResetJudgement;

	//		フェードアウトをするかどうか判断する
	bool m_fadeoutResetJudgement;

	//		初めのフェードインかどうか
	bool m_firstJudgement;
};
