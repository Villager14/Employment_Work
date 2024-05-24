/*
* @file		ClockBackGround.h
* @brief	UI時計の背景
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "../UIRender.h"

class ClockBackGround
{
public:
	//		コンストラクタ
	ClockBackGround();

	//		デストラクタ
	~ClockBackGround();

	//		初期処理
	void Initialize();

	/*
	*	更新処理
	* 
	*	@param	(elapsedTime)	経過時間
	*/
	void Update(float elapsedTime);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:

	const float ROTATION_RADIAN = 60.0f;

private:

	//		UIの描画
	std::unique_ptr<UIRender> m_uiRender;

	//		コロンの描画
	std::unique_ptr<UIRender> m_colonRender;

	//		最小時間
	float m_rotationMin;

	//		最大時間
	float m_rotationMax;

	//		過去の時間
	float m_pastTime;
};
