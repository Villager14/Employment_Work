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
	*	メニューマネージャーを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	MenuManager* GetMenuManager() { return m_menuManager.get(); }
};
