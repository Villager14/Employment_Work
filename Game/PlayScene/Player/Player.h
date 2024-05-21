/*
* @file		Player.h
* @brief	プレイヤーの処理
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "Game/PlayScene/CollitionManager/CollitionInformation.h"

#include "Game/PlayScene/Player/PlayerInformationCollition.h"

#include "Game/PlayScene/Player/PlayerInformationCamera.h"

#include "PlayerInformation.h"

#include "State/PlayerStay.h"
#include "State/PlayerWalk.h"
#include "State/PlayerCrouching.h"
#include "State/PlayerJump.h"
#include "State/PlayerSliding.h"
#include "State/PlayerDash.h"
#include "State/PlayerSlowTime.h"
#include "State/PlayerWallWalk.h"
#include "State/PlayerWire.h"
#include "State/PlayerWallJump.h"
#include "State/PlayerDeath.h"

#include "State/PlayerAttack.h"


class PlayerStay;
class PlayerWork;
class PlayerCrouching;
class PlayerJump;
class PlayerSliding;
class PlayerDash;
class PlayerSlowTime;
class PlayerWallWalk;
class PlayerWire;
class PlayerWallJump;
class PlayerDeath;

class Player
{
public:

	//		コンストラクタ
	Player();

	//		デストラクタ
	~Player();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		メッシュの更新
	void MeshUpdate();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		死亡したか判断する
	void DeathJudgement();

	/*
	*	状態を変更する
	*
	*	@param	(state)	状態
	*/
	void ChangeState(IPlayer* state);

	/*
	*	移動処理
	*
	*	@param	(keyPressJudgement)	キーを押したかどうか
	*	@return 移動方向
	*/
	DirectX::SimpleMath::Vector3 Direction(bool* keyPressjudgement);

	/*
	*	移動する向き
	*
	*	@param (direction) 移動したい方向
	*	@return 向き
	*/
	DirectX::SimpleMath::Vector3 MoveDirection
	(const DirectX::SimpleMath::Vector3 direction);

	/*
	*	重力処理
	* 
	*	@param	(weekJudgement)	弱い重力にするかどうか
	*/
	void Gravity(bool weekJudgement = false);

	//		床メッシュに当たっているか判断する
	bool FloorMeshHitJudgement();

	//		壁メッシュに当たっているか判断する
	bool WallMeshHitJudgement();

	/*
	*	立つ状態にする
	*
	*	@param	(firstHeight)	最初の高さ
	*	@param	(endHeight)		最終的な高さ
	*	@param	(speed)			速度
	*/
	void PlayerHeightTransition(const float& firstHeight, const float& endHeight, const float& speed);

	/*
	*	ワイヤーアクションをするかどうか
	* 
	*	@returnr するかどうか true : 行う fales : 行わない
	*/
	bool WireActionJudgement();

	//		壁ジャンプ状態になるかどうか
	void WallWalkJudgement();

private:

	//		現在の状態
	IPlayer* m_state;

	//		プレイヤー待機状態
	std::unique_ptr<PlayerStay> m_playerStay;

	//		プレイヤー歩き状態
	std::unique_ptr<PlayerWalk> m_playerWalk;

	//		プレイヤーしゃがみ状態
	std::unique_ptr<PlayerCrouching> m_playerCrouching;

	//		プレイヤーのジャンプ状態
	std::unique_ptr<PlayerJump> m_playerJump;

	//		プレイヤーのスライディング状態
	std::unique_ptr<PlayerSliding> m_playerSliding;

	//		プレイヤーのダッシュ状態
	std::unique_ptr<PlayerDash> m_playerDash;

	//		プレイヤー低速状態
	std::unique_ptr<PlayerSlowTime> m_playerSlowTime;

	//		プレイヤーの壁走り状態
	std::unique_ptr<PlayerWallWalk> m_playerWallWalk;

	//		プレイヤーのワイヤー状態
	std::unique_ptr<PlayerWire> m_playerWire;

	//		プレイヤーの壁ジャンプ状態
	std::unique_ptr<PlayerWallJump> m_playerWallJump;

	//		プレイヤーの死亡状態
	std::unique_ptr<PlayerDeath> m_playerDeath;
public:

	/*
	*	待機状態を受け取る
	*
	*	@return 待機状態のインスタンスのポインタ
	*/
	PlayerStay* GetStayState() { return m_playerStay.get(); }

	/*
	*	歩き状態を受け取る
	*
	*	@return 歩き状態のインスタンスのポインタ
	*/
	PlayerWalk* GetWalkState() { return m_playerWalk.get(); }

	/*
	*	しゃがみ状態を受け取る
	*
	*	@return しゃがみ状態のインスタンスのポインタ
	*/
	PlayerCrouching* GetCrouchingState() { return m_playerCrouching.get(); }

	/*
	*	ジャンプ状態を受け取る
	*
	*	@return ジャンプ状態のインスタンスのポインタ
	*/
	PlayerJump* GetJumpState() { return m_playerJump.get(); }

	/*
	*	プレイヤーのスライディング状態を受け取る
	*
	*	@return スライディング状態のインスタンスのポインタ
	*/
	PlayerSliding* GetSlidingState() { return m_playerSliding.get(); }

	/*
	*	プレイヤーのダッシュ状態を受け取る
	*
	*	@return ダッシュ状態のインスタンスのポインタ
	*/
	PlayerDash* GetDashState() { return m_playerDash.get(); }

	/*
	*	プレイヤーの低速状態を受け取る
	*
	*	@return 低速状態のインスタンスのポインタ
	*/
	PlayerSlowTime* GetSlowTimeState() { return m_playerSlowTime.get(); }

	/*
	*	プレイヤーの壁を歩く状態を受け取る
	* 
	*	@return 壁を歩く状態のインスタンスのポインタ
	*/
	PlayerWallWalk* GetWallWalkState() { return m_playerWallWalk.get(); }

	/*
	*	プレイヤーのワイヤー状態を受け取る
	* 
	*	@return ワイヤー状態のインスタンスを受け取る
	*/
	PlayerWire* GetWireState() { return m_playerWire.get(); }

	/*
	*	プレイヤーの壁ジャンプ状態を受け取る
	* 
	*	@return 壁ジャンプのインスタンスを受け取る
	*/
	PlayerWallJump* GetWallJumpState() { return m_playerWallJump.get(); }

	/*
	*	プレイヤーの死亡状態を受け取る
	* 
	*	@return 死亡状態のインスタンスを受け取る
	*/
	PlayerDeath* GetDeathState() { return m_playerDeath.get(); }

private:
	//		立つ速度
	const float STANDING_SPEED = 3.0f;

	//		歩き速度
	const float WALK_SPEED = 50.0f;

	//		しゃがみ速度 
	const float CROUCHING_SPEED = 30.0f;

	//		プレイヤーの高さ
	const float STANDING_HEIGHT = 7.0f;

	//		減速速度
	const float DECELERATION_SPEED = 80.0f;

	//		壁移動時の最高移動量
	const float HEAD_MOVE_MAX = 4.0f;

	//		頭の移動速度
	const float HEAD_MOVE_SPEED = 30.0f;

private:

	//		当たり判定の情報
	CollitionInformation* m_collitionInformation;

	//		当たり判定用プレイヤーの情報
	std::unique_ptr<PlayerInformationCollition> m_playerInformationCollition;

	//		カメラ用プレイヤー情報
	std::unique_ptr<PlayerInformationCamera> m_playerInformationCamera;

	//		プレイヤーの攻撃
	std::unique_ptr<PlayerAttack> m_playerAttack;

	//		プレイヤーの情報
	std::unique_ptr<PlayerInformation> m_information;

	//		プレイヤーモデル
	std::unique_ptr<DirectX::Model> m_playerObject;

public:

	/*
	*	歩きの速さ
	*
	*	@return 速度
	*/
	float GetWalkSpeed() { return WALK_SPEED; }

	/*
	*	減速の速さ
	*
	*	@return 速度
	*/
	float GetDecelerationSpeed() { return DECELERATION_SPEED; }

	/*
	*	しゃがみの速さ
	*
	*	@return 速度
	*/
	float GetCrouchingSpeed() { return CROUCHING_SPEED; }

	/*
	*	立っているときの高さ
	*
	*	@return 速度
	*/
	float GetStandingHeight() { return STANDING_HEIGHT; }

	/*
	*	頭の最高移動量を受け取る
	*
	*	@reutrn 移動量
	*/
	inline constexpr float GetHeadMoveMAX() const noexcept { return HEAD_MOVE_MAX; }

	/*
	*	頭の移動速度を受け取る
	*
	*	@return 移動速度
	*/
	inline constexpr float GetHeadMoveSpeed() const noexcept { return HEAD_MOVE_SPEED; }

public:

	/*
	*	当たり判定の情報を受け取る
	* 
	*	@param	(collitionInformation)	インスタンスのポインタ
	*/
	void SetCollitionInformation(CollitionInformation* collitionInformation)
							{ m_collitionInformation = collitionInformation; }

	/*
	*	当たり判定の情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	CollitionInformation* GetCollitionInformation() { return m_collitionInformation; }

	/*
	*	当たり判定用情報を設定する
	* 
	*	@return インスタンスのポインタ
	*/
	PlayerInformationCollition* GetPlayerInformationCollition() { return m_playerInformationCollition.get(); }

	/*
	*	カメラ用プレイヤー情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	PlayerInformationCamera* GetPlayerInformationCamera() { return m_playerInformationCamera.get(); }

	/*
	*	プレイヤーの情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	PlayerInformation* GetInformation() { return m_information.get(); }
 }; 
