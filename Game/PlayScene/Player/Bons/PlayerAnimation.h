/*
* @file		PlayerAnimation.h
* @brief	プレイヤーのアニメーション
* @author	Morita
* @date		2024/06/20
*/

#pragma once

#include "IPlayerAnimationState.h"

#include "PlayerBons.h"

#include "AnimationState/WalkAnimationState.h"
#include "AnimationState/StayAnimationState.h"
#include "AnimationState/CrouchingStayAnimationState.h"
#include "AnimationState/CrouchingWalkAnimationState.h"
#include "AnimationState/DashAnimationState.h"
#include "AnimationState/JumpAnimationState.h"
#include "AnimationState/SlidingAnimationState.h"
#include "AnimationState/StartAnimationState.h"
#include "AnimationState/WireJumpAnimationState.h"
#include "AnimationState/WallJumpAnimationState.h"
#include "AnimationState/WallWalkAnimationState.h"

class WalkAnimationState;
class StayAnimationState;
class CrouchingStayAnimationState;
class CrouchingWalkAnimationState;
class DashAnimationState;
class JumpAnimationState;
class SlidingAnimationState;
class StartAnimationState;
class WireJumpAnimationState;
class WallJumpAnimationState;
class WallWalkAnimationState;

class PlayerAnimation
{
public:

	//		コンストラクタ
	PlayerAnimation();

	//		デストラクタ
	~PlayerAnimation();

	//		初期化処理
	void Initialize();

	//		実行処理
	void Execute(
		float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle,
		float height);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		モデルの作製
	void CreateModel();

	/*
	*	モデルの読み込み
	*
	*	@param	(path)		ファイルパス
	*	@param	(effect)	エフェクトファクトリーのポインタ
	*	@param	(modelType)	モデルの種類
	*/
	void LoadModel(const wchar_t* path,
		DirectX::EffectFactory* effect);


	/*
	//		アニメーションの値のリセット
	void AnimationValuReset();

	//		ゲームスタート時のアニメーション
	void Start(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		歩き処理
	void Walk(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		停止
	void Stop(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		ジャンプ
	void Jump(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		ダッシュ
	void Dash(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		しゃがみ停止
	void CrouchingStop(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		しゃがみ歩き
	void CrouchingWalk(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		しゃがみ歩き
	void Sliding(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		壁歩き
	void WallWalk(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		壁ジャンプ
	void WallJump(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);

	//		ワイヤージャンプ
	void WireJump(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height);
	*/

	void AnimationMovement(BonsType type,
		std::vector<PlayerBonsInformation>* m_bonesInformation,
		DirectX::SimpleMath::Quaternion firstVal,
		DirectX::SimpleMath::Quaternion endVal,
		float transrationSpeed);

	//		下半身の値を初期の値にする
	void AnimationLegInitialValue(std::vector<PlayerBonsInformation>* m_bonesInformation, float transrationSpeed);

	/*
	*	アニメーションの切り替え
	*
	*	@param	(IState)
	*/
	void ChangeState(IPlayerAnimationState* IState);

private:

	//		歩きアニメーション
	std::unique_ptr<WalkAnimationState> m_walk;

	//		待機アニメーション
	std::unique_ptr<StayAnimationState> m_stay;

	//		しゃがみ待機アニメーション
	std::unique_ptr<CrouchingStayAnimationState> m_crouchingStay;

	//		しゃがみ歩きアニメーション
	std::unique_ptr<CrouchingWalkAnimationState> m_crouchingWalk;

	//		ダッシュアニメーション
	std::unique_ptr<DashAnimationState> m_dash;

	//		ジャンプアニメーション
	std::unique_ptr<JumpAnimationState> m_jump;

	//		スライディングアニメーション
	std::unique_ptr<SlidingAnimationState> m_sliding;

	//		スタートアニメーション
	std::unique_ptr<StartAnimationState> m_start;

	//		ワイヤージャンプアニメーション
	std::unique_ptr<WireJumpAnimationState> m_wireJump;

	//		壁ジャンプアニメーション
	std::unique_ptr<WallJumpAnimationState> m_wallJump;

	//		壁歩きアニメーション
	std::unique_ptr<WallWalkAnimationState> m_wallWalk;
public:

	/*
	*	歩きアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	WalkAnimationState* GetWalkState() { return m_walk.get(); }

	/*
	*	歩きアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	StayAnimationState* GetStayState() { return m_stay.get(); }

	/*
	*	しゃがみ待機アニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	CrouchingStayAnimationState* GetCrouchingStay() { return m_crouchingStay.get(); }

	/*
	*	しゃがみ歩きアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	CrouchingWalkAnimationState* GetCrouchingWalk() { return m_crouchingWalk.get(); }

	/*
	*	ダッシュアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	DashAnimationState* GetDash() { return m_dash.get(); }

	/*
	*	ジャンプアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	JumpAnimationState* GetJump() { return m_jump.get(); }

	/*
	*	スライディングアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	SlidingAnimationState* GetSliding() { return m_sliding.get(); }

	/*
	*	スタートアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	StartAnimationState* GetStart() { return m_start.get(); }

	/*
	*	ワイヤージャンプアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	WireJumpAnimationState* GetWireJump() { return m_wireJump.get(); }

	/*
	*	壁ジャンプアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	WallJumpAnimationState* GetWallJump() { return m_wallJump.get(); }

	/*
	*	壁歩きアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	WallWalkAnimationState* GetWallWalk() { return m_wallWalk.get(); }
private:

	//		モデル
	std::vector<std::unique_ptr<DirectX::Model>> m_playerModel;

	//		プレイヤーのボーン
	std::unique_ptr<PlayerBons> m_playerBons;

	//		アニメーションの状態
	IPlayerAnimationState* m_IState;


};

