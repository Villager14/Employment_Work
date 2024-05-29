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


class ResultStart;
class ResultNumberMove;

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

private:

	//		状態
	IResultManager* m_state;

	//		リザルトスタート状態
	std::unique_ptr<ResultStart> m_resultStart;

	//		リザルトシーンの番号移動処理
	std::unique_ptr<ResultNumberMove> m_resultNumberMove;
public:

	/*
	*	スタート状態を生成する
	* 
	*	@return インスタンスのポインタ
	*/
	ResultStart* GetResultStart() { return m_resultStart.get(); }

	/*
	*	番号移動状態
	* 
	*	@return インスタンスのポインタ
	*/
	ResultNumberMove* GetNumberMove() { return m_resultNumberMove.get(); }

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
	*	上がる数字の処理
	* 
	*	@param	(index)	 要素数
	*	@param	(number) 番号
	*	@param	(time)	 時間
	*/
	void AboveNumberView(int index, int number, float time) { m_aboveNumber[index]->Render(number, time); }
};