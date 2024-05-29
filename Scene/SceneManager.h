/*
* @file		SceneManager.h
* @brief	シーンマネージャー
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "IScene.h"

#include "SceneState/PlayScene.h"

#include "SceneState/TitleScene.h"

#include "SceneState/ResultScene.h"

class PlayScene;

class TitleScene;

class ResultScene;

class SceneManager
{
public:
	//		コンストラクタ
	SceneManager();

	//		デストラクタ
	~SceneManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		状態を切り替える
	void ChangeState(IScene* scene);

private:
	//		シーン
	IScene* m_scene;

	//		プレイシーン
	std::unique_ptr<PlayScene> m_playScene;

	//		タイトルシーン
	std::unique_ptr<TitleScene> m_titleScene;

	//		リザルトシーン
	std::unique_ptr<ResultScene> m_resultScene;

public:

	/*
	*	プレイシーンを受け取る
	*
	*	@return プレイシーンのインスタンスのポインタ
	*/
	PlayScene* GetPlayScene() { return m_playScene.get(); }

	/*
	*	タイトルシーンを受け取る
	* 
	*	@return タイトルシーンのインスタンスのポインタ
	*/
	TitleScene* GetTitleScene() { return m_titleScene.get(); }

	/*
	*	リザルトシーンを受け取る
	* 
	*	@return リザルトシーンのインスタンスのポインタ
	*/
	ResultScene* GetResultScene() { return m_resultScene.get(); }

private:

	//		クリアタイム
	int m_clearTime;

	//		死亡回数
	int m_deathCount;

public:

	/*
	*	クリアタイムを設定する
	* 
	*	@param	(time)	時間
	*/
	void SetClearTime(int time) { m_clearTime = time; }

	/*
	*	クリアタイムを受け取る
	* 
	*	@return 時間
	*/
	int GetClearTime() { return m_clearTime; }

	/*
	*	死亡回数を設定する
	* 
	*	@param	(count)	回数
	*/
	void SetDeathCount(int count) { m_deathCount = count; }

	/*
	*	死亡回数を受け取る
	* 
	*	@return 回数
	*/
	int GetDeathCount() { return m_deathCount; }
};
