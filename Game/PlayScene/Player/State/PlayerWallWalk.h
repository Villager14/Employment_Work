/*
* @file		PlayerWallWalk.cpp
* @brief	プレイヤーの壁歩き状態
* @author	Morita
* @date		2024/04/30
*/
#pragma once

#include "../IPlayer.h"

class Player;

class PlayerWallWalk : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerWallWalk(Player* player);

	//		デストラクタ
	~PlayerWallWalk();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		移動処理
	void Move() override;

	//		アニメーションの処理
	void Animation() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	//		移動処理
	void MoveProcessing();

	//		状態遷移判断
	void ChangeStateJudgement();

	//		頭の動き
	void HeadMove();

private:

	//		加速の速さ
	const float WORK_ACCERARATION_SPEED = 0.8f;

	//		壁移動時の頭の高さ
	const float HEAD_WALLWALK_HEIGHT = 2.5f;


private:
	//		状態管理クラスのポインタ
	Player* m_player;

	//		ベロシティ
	DirectX::SimpleMath::Vector3 m_velocity;

	DirectX::SimpleMath::Vector2 m_moveAngle;


	float m_heightMove;

};
