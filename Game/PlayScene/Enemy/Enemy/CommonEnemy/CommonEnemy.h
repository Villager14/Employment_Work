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

class CommonEnemyStaty;
class CommonEnemyVigilance;
class CommonEnemyCharge;
class CommonEnemyAttack;

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

	/*
	*	状態を切り替える
	*
	*	@param	(nextState)	次の状態
	*/
	void ChangeState(ICommonEnemy* nextState)
	{
		//現在の状態の終了処理
		m_state->Finalize();

		//次の状態を切り替える
		m_state = nextState;

		//次の状態の初期化処理
		m_state->Initialize();
	}

private:

	//		状態
	ICommonEnemy* m_state;

	//		待機状態
	std::unique_ptr<CommonEnemyStay> m_stay;

	//		警戒状態
	std::unique_ptr<CommonEnemyVigilance> m_vigilance;

	//		チャージ状態
	std::unique_ptr<CommonEnemyCharge> m_charge;

	//		攻撃状態
	std::unique_ptr<CommonEnemyAttack> m_attack;
public:

	/*
	*	待機状態を受け取る
	*
	*	@return 待機状態のインスタンスのポインタ
	*/
	CommonEnemyStay* GetStay() { return m_stay.get(); }

	/*
	*	警戒状態を受け取る
	*
	*	@return 待機状態のインスタンスのポインタ
	*/
	CommonEnemyVigilance* GetVigilance() { return m_vigilance.get(); }

	/*
	*	チャージ状態を受け取る
	*
	*	@return チャージ状態のインスタンスのポインタ
	*/
	CommonEnemyCharge* GetCharge() { return m_charge.get(); }

	/*
	*	攻撃状態を受け取る
	*
	*	@return 攻撃状態のインスタンスのポインタ
	*/
	CommonEnemyAttack* GetAttack() { return m_attack.get(); }

private:

	//		モデル
	std::unique_ptr<DirectX::Model> m_model;

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
public:

	/*
	*	モデルを受け取る
	*
	*	@return モデル
	*/
	DirectX::Model* GetModel() { return m_model.get(); }

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