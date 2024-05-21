/*
* @file		PlayerWire.h
* @brief	プレイヤーのワイヤー状態
* @author	Morita
* @date		2024/05/13
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerWire : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerWire(Player* player);

	//		デストラクタ
	~PlayerWire();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		移動処理
	void Move() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	//		移動処理
	void MoveProcessing();

	//		状態遷移判断
	void ChangeStateJudgement();

	//		引き寄せる時の処理
	void AttractProcess();

	//		落下時の処理
	void FallProcess();

	//		落下状態にするかどうか
	void FallJudgement();

private:
	
	//		減速
	const float DECELERATION_SPEED = 8.0f;

private:
	//		状態管理クラスのポインタ
	Player* m_player;

	//		経過時間
	float m_time;

	//		初期の高さ
	float m_firstHeight;

	//		距離
	float m_length;


	//		移動方向
	DirectX::SimpleMath::Vector3 m_direction;

	DirectX::SimpleMath::Vector3 m_acceleation;

	//		速度を受け取る
	float m_speed;

	float m_firstSpeed;

	//		落下判断
	bool m_fallJudgement;

	//		何かに当たった場合
	bool m_floorHitJudgement;

	//		壁に当たったか？
	bool m_wallHitJudgement;
};
