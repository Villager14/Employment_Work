/*
* @file		ResultManager.h
* @brief	リザルトマネージャー
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include <unordered_map>

#include "IResultManager.h"

#include "Game/TitleScene/UI/BackGroundMove.h"

#include "Library/Shader/UIRenderManager.h"

#include "Game/PlayScene/ScreenEffect/ScreenEffectManager.h"

#include "Game/PlayScene/Player/Bons/PlayerAnimation.h"

#include "Library/Shader/StandardShader.h"

#include "UI/RiseNumberShader.h"

class ResultManager
{
public:

	//		リザルトマネージャー
	ResultManager();

	//		リザルトマネージャー
	~ResultManager();

	//		初期化処理
	/*
	*	初期化処理
	* 
	*	@param	(score)			スコア
	*	@param	(time)			タイム
	*	@param	(deathCount)	死亡カウント
	*/
	void Initialize(int score, int time, int deathCount);

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		状態を作成する
	void CreateState();

	//		アニメーションスキップ
	void AnimationSkip();

	//		シェーダーの作製
	void CreateStandardShader();

	//		背景の更新
	void BackGroundUpdate();

public:

	//		状態
	enum State
	{
		Start,			//		スタート
		NumberMove,		//		番号
		Evaluation,		//		評価
		Stay,			//		待機
		End,			//		終了
	};

	//		リザルトのUIの種類
	enum ResultUIType
	{
		Back,			//		UI背景
		Button,			//		ボタンヒント
		EvaluationUI	//		評価
	};

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

private:

	//		プレイヤーの回転速度
	const float PLAYER_ROTATION_SPEED = 30.0f;

	//		プレイヤーの高さ
	const float PLAYER_HEIGHT = 2.5f;

	//		プレイヤーの座標
	const DirectX::SimpleMath::Vector3 PLAYER_POSITION = { 0.0f, 0.0f, 8.0f };

private:

	//		状態
	IResultManager* m_iState;

	//		状態の情報
	std::unordered_map<State, std::unique_ptr<IResultManager>> m_stateInformation;

	//		状態
	State m_state;
	
	//		シェーダー
	std::unique_ptr<StandardShader<ResultManager::ResultUIType>> m_shader;

	//		背景移動の描画
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	ConstBuffer buffer;

	//		フェード描画
	std::unique_ptr<UIRenderManager> m_fade;

	//		スコア
	int m_score;
	//		時間
	int m_time;
	//		死亡カウント
	int m_deathCount;

	//		スクリーンエフェクトマネージャー
	std::unique_ptr<ScreenEffectManager> m_screenEffectManager;

	//		プレイヤーアニメーション
	std::unique_ptr<PlayerAnimation> m_playerAnimation;

	//		回転量
	float m_rotation;

	//		シーンを切り替える
	bool m_changeScene;

	//		数字の上昇シェーダー
	std::unique_ptr<RiseNumberShader> m_riseNumber;

	//		メニューを使えるかどうか
	bool m_menuUseJudgement;

public:

	/*
	*	状態を変更する
	*
	*	@param	(state)	状態
	*/
	void ChangeState(State state);

	/*
	*	フェードの描画
	* 
	*	@param	(time)	時間
	*/
	void FadeViewProcess(float time) { 
		buffer.time = { time, 0.0f, 0.0f, 0.0f };
		m_fade->Render(buffer); }

	/*
	*	シーンを切り替えるか設定する
	* 
	*	@param	(judgement)	true : 切り替える false : 切り替えない
	*/
	void SetChangeSceneJudgement(bool judgement) { m_changeScene = judgement; }

	/*
	*	シーンを切り替えるか受け取る
	*	
	*	@return true : 切り替える false : 切り替えない
	*/
	bool GetChangeSceneJudgement() { return m_changeScene; }

	/*
	*	リザルトUIマネジャーのインスタンスのポインタを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	StandardShader<ResultUIType>* GetStandardShader() { return m_shader.get(); }

	/*
	*	上昇数字のインスタンスのポインタを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	RiseNumberShader* GetRiseNumberShader() { return m_riseNumber.get(); }

	/*
	*	メニューを使えるかどうか受け取る
	* 
	*	@return true : 使える false : 使えない
	*/
	bool GetMenuUseJugement() { return m_menuUseJudgement; }

	/*
	*	メニューを使えるかどうか設定する
	*
	*	@param	(judgement) true : 使える false : 使えない
	*/
	void SetMenuUseJugement(bool judgement) { m_menuUseJudgement = judgement; }
};