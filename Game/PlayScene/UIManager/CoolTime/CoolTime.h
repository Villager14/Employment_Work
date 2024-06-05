/*
* @file		CoolTime.h
* @brief	クールタイム
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "../CircleShader.h"

#include "../UIRender.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "../NumberShader.h"

class CoolTime
{
public:

	//		コンストラクタ
	CoolTime();

	//		デストラクタ
	~CoolTime();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	*	
	*	プレイヤーの情報を受けとる
	*/
	void Update(PlayerInformation* playerInformation);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:

	enum State
	{
		None,		//		何もない状態
		Reduce,		//		減らす状態
		Increase	//		増やす状態
	};

private:

	//		数字の中心の座標
	const float NUMBER_CENTER_POSITION = 1179.0f;

	//		数字の間隔
	const float NUMBER_INTERVAL = 30.0f;

private:

	//		数字の描画
	std::unique_ptr<CircleShader> m_circleShader;

	//		背景の描画
	std::unique_ptr<UIRender> m_backRender;;

	//		角度
	float m_angle;

	//		時間
	float m_time;

	//		パーセント
	float m_ratio;

	//		クールタイムに入ったかどうか判断する
	bool m_coolTimeJudgement;

	//		状態
	State m_state;

	//		数字の描画
	std::unique_ptr<NumberShader> m_numberShader;

};
