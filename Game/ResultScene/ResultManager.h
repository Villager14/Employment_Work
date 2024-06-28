/*
* @file		ResultManager.h
* @brief	リザルトマネージャー
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include "IResultManager.h"

#include "Game/TitleScene/UI/BackGroundMove.h"

#include "Game/PlayScene/UIManager/Fade/FadeRender.h"

#include "Game/PlayScene/UIManager/UIRender.h"


#include "Game/ResultScene/UI/AboveNumber.h"

#include "State/ResultStart.h"
#include "State/ResultNumberMove.h"
#include "State/ResultEvaluation.h"
#include "State/ResultStay.h"
#include "State/ResultEnd.h"

#include "Game/PlayScene/ScreenEffect/ScreenEffectManager.h"
#include "Game/PlayScene/Player/Bons/PlayerAnimation.h"

class ResultStart;
class ResultNumberMove;
class ResultEvaluation;
class ResultStay;
class ResultEnd;

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

	/*
	*	状態を変更する
	*
	*	@param	(state)	状態
	*/
	void ChangeState(IResultManager* state);

	//		状態を作成する
	void CreateState();

	/*
	*	数字の描画
	* 
	*	@param	(time)	時間
	*/
	void NumberRender(float time);

	/*
	*	UIを追加する
	*
	*	@param	(path)		テクスチャファイルパス
	*	@param	(position)	座標
	*	@param	(size)		サイズ
	*/
	void AddRenderUI(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size);

	//		アニメーションスキップ
	void AnimationSkip();

private:

	//		状態
	IResultManager* m_state;

	//		リザルトスタート状態
	std::unique_ptr<ResultStart> m_resultStart;

	//		リザルトシーンの番号移動状態
	std::unique_ptr<ResultNumberMove> m_resultNumberMove;

	//		リザルト評価状態
	std::unique_ptr<ResultEvaluation> m_resultEvaluation;

	//		リザルト待機状態
	std::unique_ptr<ResultStay> m_resultStay;

	//		リザルト終了処理
	std::unique_ptr<ResultEnd> m_resultEnd;
public:

	/*
	*	スタート状態を生成する
	* 
	*	@return インスタンスのポインタ
	*/
	ResultStart* GetResultStart() { return m_resultStart.get(); }

	/*
	*	番号移動状態を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	ResultNumberMove* GetNumberMove() { return m_resultNumberMove.get(); }

	/*
	*	評価状態を受け取る
	*
	*	@return インスタンスのポインタ
	*/
	ResultEvaluation* GetEvaluation() { return m_resultEvaluation.get(); }

	/*
	*	待機状態を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	ResultStay* GetResultStay() { return m_resultStay.get(); }

	/*
	*	終了状態を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	ResultEnd* GetResultEnd() { return m_resultEnd.get(); }

private:
	
	//		背景移動の描画
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	//		フェードイン描画
	std::unique_ptr<FadeRender> m_fadeRender;

	//		上に移動する番号
	std::vector<std::unique_ptr<AboveNumber>> m_aboveNumber;

	//		UIの描画
	std::vector<std::unique_ptr<UIRender>> m_uiRender;

	//		スコア
	int m_score;
	//		時間
	int m_time;
	//		死亡カウント
	int m_deathCount;

	//		ポジジョン
	std::vector<DirectX::SimpleMath::Vector2> m_uiPosition;

	//		サイズ
	std::vector<DirectX::SimpleMath::Vector2> m_uiSize;

	//		スクリーンエフェクトマネージャー
	std::unique_ptr<ScreenEffectManager> m_screenEffectManager;

	//		プレイヤーアニメーション
	std::unique_ptr<PlayerAnimation> m_playerAnimation;

	//		回転量
	float m_rotation;

	//		シーンを切り替える
	bool m_changeScene;

public:

	/*
	*	フェードの描画
	* 
	*	@param	(time)	時間
	*/
	void FadeViewProcess(float time) { m_fadeRender->Render(time); }

	/*
	*	UI描画の処理
	* 
	*	@param	(index)	要素数
	*/
	void UIViewProcess(int index) { m_uiRender[index]->Render(); }

	/*
	*	UI描画のスケール
	*
	*	@param	(index)	要素数
	*	@param	(size)	サイズ
	*/
	void UIScare(int index, float size) { m_uiRender[index]->SetSize({size, size}); }

	/*
	*	上がる数字の処理
	* 
	*	@param	(index)	 要素数
	*	@param	(number) 番号
	*	@param	(time)	 時間
	*/
	void AboveNumberView(int index, int number, float time) { m_aboveNumber[index]->Render(number, time); }

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
};