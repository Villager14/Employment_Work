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

#include "Game/Observer/Menu/MenuOpenJudgementObserver/IMenuOpenJudgementObserver.h"

#include "Game/Observer/Menu/MenuUsedObserver/MenuUsedObserver.h"

class SceneManager;

class ResultScene : public IScene,
					public IMenuOpenJudgementObserver
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

	//		プロジェクション行列を作成
	void CreateProj();

	//		ビュー行列の作製
	void CreateView();

	//		メニューを開いている
	void MenuOpen() override;

	//		メニューを閉じている
	void MenuClose() override;

private:
	//		シーンマネージャーのインスタンスのポインタ
	SceneManager* m_sceneManager;

	//		リザルトマネージャー
	std::unique_ptr<ResultManager> m_resultManager;

	float m_score;

	//		メニューが開いているか
	bool m_menuOpenJugement;

	//		メニューを使うか判断するオブザーバー
	std::unique_ptr<MenuUsedObserver> m_menuUsedObserver;

public:

	/*
	*	メニューを使用できるか判断するオブザーバー
	*
	*	@return インスタンスのポインタ
	*/
	MenuUsedObserver* GetMenuUsedObserver() { return m_menuUsedObserver.get(); }
};