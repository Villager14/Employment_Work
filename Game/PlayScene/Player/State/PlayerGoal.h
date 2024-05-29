/*
* @file		PlayerGoal.h
* @brief	プレイヤーゴール状態
* @author	Morita
* @date		2024/05/27
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerGoal : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerGoal(Player* player);

	//		デストラクタ
	~PlayerGoal();

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
	
private:

	//		状態管理クラスのポインタ
	Player* m_player;
};
