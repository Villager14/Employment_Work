/*
* @file		CommonEnemy.h
* @brief	一般的な敵
* @author	Morita
* @date		2024/05/01
*/

#pragma once

#include "State/CommonEnemyStay.h"
#include "State/CommonEnemyVigilance.h"
#include "State/CommonEnemyCharge.h"
#include "State/CommonEnemyAttack.h"

#include "Library/Animation/AnimationManager.h"

class CommonEnemy
{
public:

	//		コンストラクタ
	CommonEnemy();

	//		デストラクタ
	~CommonEnemy();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	* 
	*	@param	(playerPosition)	プレイヤーの座標
	*	@param	(timeSpeed)			時間の速度
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition,
				float timeSpeed);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();


public:

	enum State
	{
		Stay,
		Vigilance,
		Charge,
		Attack,
	};

private:

	//		状態
	ICommonEnemy* m_istate;

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		座標
	DirectX::SimpleMath::Vector3 m_position;

	//		角度
	float m_rotation;

	//		攻撃するかどうか
	bool m_attackJudgement;

	//		時間の速度
	float m_timeSpeed;

	//		攻撃する方向
	DirectX::SimpleMath::Vector3 m_attakDirection;

	//		状態の情報
	std::unordered_map<State, std::unique_ptr<ICommonEnemy>> m_stateintarface;

	State m_state;

	//		プレイヤーアニメーション
	std::unique_ptr<AnimationManager> m_playerAnimation;

public:

	/*
	*	状態を切り替える
	*
	*	@param	(nextState)	次の状態
	*/
	void ChangeState(State nextState)
	{
		//		同じ状態の場合処理をしない
		if (m_state == nextState) return;

		//現在の状態の終了処理
		m_istate->Finalize();

		//次の状態を切り替える
		m_state = nextState;

		//次の状態を切り替える
		m_istate = m_stateintarface[m_state].get();

		//次の状態の初期化処理
		m_istate->Initialize();
	}

	/*
	*	プレイヤーアニメーション
	* 
	*	@return プレイヤーアニメーション
	*/
	AnimationManager* GetPlayerAnimation() { return m_playerAnimation.get(); }

	/*
	*	プレイヤーの座標を受け取る
	* 
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerPosition() { return m_playerPosition; }

	/*
	*	座標を受け取る
	*
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

	/*
	*	座標を設定する
	* 
	*/
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	/*
	*	攻撃座標を受け取る
	* 
	*	@return 座標
	*/
	DirectX::SimpleMath::Vector3 GetAttackPosition() 
	{
		DirectX::SimpleMath::Vector3 attackPosition = m_position;

		attackPosition.y += 5.0f;

		return attackPosition;
	}

	/*
	*	角度を設定する
	* 
	*	@param	(rotation)	角度
	*/
	void SetRotation(float rotation) { m_rotation = rotation; }

	/*
	*	角度を受け取る
	* 
	*	@return 角度
	*/
	float GetRotation() { return m_rotation; }

	/*
	*	攻撃するかどうかを受け取る
	* 
	*	@return true : 攻撃する false : 攻撃しない
	*/
	bool GetAttackJudgement() { return m_attackJudgement; }

	/*
	*	攻撃するかどうか設定する
	* 
	*	@param	(judgement)	true : 攻撃する false : 攻撃しない
	*/
	void SetAttackJudgement(bool judgement) { m_attackJudgement = judgement; }

	/*
	*	攻撃する方向を設定する
	* 
	*	@param	(direction)	方向
	*/
	void SetAttackDirection(const DirectX::SimpleMath::Vector3& direction) { m_attakDirection = direction; }

	/*
	*	攻撃する方向を受け取る
	* 
	*	@return 方向
	*/
	const DirectX::SimpleMath::Vector3& GetAttackDirection() { return m_attakDirection; }

	/*
	*	時間の速度を受け取る
	* 
	*	@return 速度
	*/
	float GetTimeSpeed() { return m_timeSpeed; }
};