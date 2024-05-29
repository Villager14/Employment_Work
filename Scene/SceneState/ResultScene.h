/*
* @file		ResultScene.h
* @brief	リザルトシーン
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include "Scene/IScene.h"

#include "../SceneManager.h"

#include "Game/ResultScene/ResultManager.h"

class SceneManager;

class ResultScene : public IScene
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(sceneManager)	インスタンスのポインタ	
	*/
	ResultScene(SceneManager* sceneManager);

	//		デストラクタ
	~ResultScene();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	/*
	*	スコア計算を行う
	* 
	*	@param	(count)	死亡回数
	*	@score	(score)	現在のスコア
	*	@return 計算後のスコア
	*/
	float ScoreCalculation(int count, float score);

private:
	//		シーンマネージャーのインスタンスのポインタ
	SceneManager* m_sceneManager;

	//		リザルトマネージャー
	std::unique_ptr<ResultManager> m_resultManager;

	//		スコアを設定する
	int m_score;
};