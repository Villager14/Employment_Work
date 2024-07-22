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
#include "AnimationState/UprightAnimationState.h"
#include "AnimationState/FallAnimationState.h"

#include <unordered_map>

class PlayerAnimation
{
public:

	//		コンストラクタ
	PlayerAnimation();

	//		デストラクタ
	~PlayerAnimation();

	//		初期化処理
	void Initialize(bool createHead = false);

	//		実行処理
	void Execute(
		float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle,
		float height);

	//		描画処理
	void Render(bool wireJudgement = false);

	//		終了処理
	void Finalize();

	//		モデルの作製
	void CreateModel(bool createHead);

	/*
	*	モデルの読み込み
	*
	*	@param	(path)		ファイルパス
	*	@param	(effect)	エフェクトファクトリーのポインタ
	*	@param	(modelType)	モデルの種類
	*/
	void LoadModel(const wchar_t* path,
		DirectX::EffectFactory* effect);

	void AnimationMovement(BonsType type,
		std::vector<PlayerBonsInformation>* m_bonesInformation,
		DirectX::SimpleMath::Quaternion firstVal,
		DirectX::SimpleMath::Quaternion endVal,
		float transrationSpeed);

	//		下半身の値を初期の値にする
	void AnimationLegInitialValue(std::vector<PlayerBonsInformation>* m_bonesInformation, float transrationSpeed);

	//		着地処理
	void Landing(float height);

public:

	enum AnimationState
	{
		Stay,
		Walk,
		CrouchingStay,
		CrouchingWalk,
		Jump,
		Sliding,
		Dash,
		WallWalk,
		WallJump,
		Wire,
		Start,
		Upright,
		Fall,
	};

public:

	/*
	*	アニメーションの切り替え
	*
	*	@param	(IState)
	*/
	void ChangeState(AnimationState State);

private:

	//		アニメーションの情報
	std::unordered_map<AnimationState, std::unique_ptr<IPlayerAnimationState>> m_animationStateInformation;

	AnimationState m_animationState;

private:

	//		モデル
	std::vector<std::unique_ptr<DirectX::Model>> m_playerModel;

	//		プレイヤーのボーン
	std::unique_ptr<PlayerBons> m_playerBons;

	//		アニメーションの状態
	IPlayerAnimationState* m_IState;

	//		ワールド座標
	std::vector<DirectX::SimpleMath::Matrix> m_world;

	//		落下していたかどうか
	bool m_fallJudgement;

	//		着地時間
	float m_landingTime;

public:

	bool GetFallJudgement() { return m_fallJudgement; }

	void SetFallJudgement(bool judgement) { m_fallJudgement = judgement; }
};

