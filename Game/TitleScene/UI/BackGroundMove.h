/*
* @file		BackGroundMove.h
* @brief	背景の移動
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "BackGroundMoveRender.h"

class BackGroundMove
{
public:

	BackGroundMove();

	~BackGroundMove();

	void Initialize();

	void Update();

	void Render();

	void Finalize();


private:

	//		背景移動の描画
	std::unique_ptr<BackGroundMoveRender> m_backGroundMoveRender;

	//		時間
	float m_time;

	//		フェードインをするかどうか判断する
	bool m_fadeinResetJudgement;

	//		フェードアウトをするかどうか判断する
	bool m_fadeoutResetJudgement;
};
