/*
* @file		SceneManager.h
* @brief	シーンマネージャー
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include <unordered_map>

#include "Scene/IScene.h"

#include "SceneState/PlayScene.h"
#include "SceneState/TitleScene.h"
#include "SceneState/ResultScene.h"

class PlayScene;
class TitleScene;
class ResultScene;

#include "Game/Menu/MenuManager.h"

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

public:

	enum SceneType
	{
		Title,
		Play,
		Result,
	};

private:

	//		シーン
	IScene* m_scene;

	//		メニューマネージャー
	std::unique_ptr<MenuManager> m_menuManager;

	//        クリアタイム
	int m_clearTime;

	//        死亡カウント
	int m_deathCount;

	std::unique_ptr<bool> m_menuJudgement;

	//		メニューを使えるかどうか判断する
	bool m_menuUseJudgement;

	//		シーンの情報
	std::unordered_map<SceneType, std::unique_ptr<IScene>> m_sceneInformation;

	//		シーンタイプ
	SceneType m_sceneType;

public:

	void ChangeScene(SceneType type);

	/*
	*    クリアタイムを設定する
	*
	*    @param    (time)    時間
	*/
	void SetClearTime(int time) { m_clearTime = time; }

	/*
	*    クリアタイムを受け取る
	*
	*    @return 時間
	*/
	int GetClearTime() { return m_clearTime; }

	/*
	*    死亡回数を設定する
	*
	*    @param    (count)    回数
	*/
	void SetDeathCount(int count) { m_deathCount = count; }

	/*
	*    死亡回数を受け取る
	*
	*    @return 回数
	*/
	int GetDeathCount() { return m_deathCount; }

	/*
	*	メニューを開いているかどうか受け取る
	* 
	*	@return true : 開いている false : 開いていない
	*/
	bool* GetMenuJudgement() 
	{ 
		return m_menuJudgement.get(); }

	/*
	*	メニューを開いているかどうか設定する
	*
	*	@param	(judgement) true : 開いている false : 開いていない
	*/
	//void SetMenuJudgement(bool judgement) { m_menuJudgement = judgement; }

	/*
	*	メニューを使えるかどうか判断する
	* 
	*	@return true : 使える false : 使えない
	*/
	bool GetMenuUseJudgement() { return m_menuUseJudgement; }

	/*
	*	メニューを使えるかどうか設定する
	* 
	*	@param	(judgement)	true : 使える false : 使えない
	*/
	void SetMenuUseJudgement(bool judgement) { m_menuUseJudgement = judgement; }
};
