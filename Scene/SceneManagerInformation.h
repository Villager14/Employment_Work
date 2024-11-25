/*
* @file		SceneManagerInformation.h
* @brief	シーンマネージャーの情報
* @author	Morita
* @date		2024/11/08
*/

#pragma once

#include "pch.h"

#include "Effect/PostEffect/PostEffectManager.h"

#include "Game/Menu/MenuManager.h"

class SceneManagerInformation
{
public:

	//		コンストラクタ
	SceneManagerInformation()
		:
		m_clearTime(0),
		m_deathCount(0),
		m_maxTime(0),
		m_endJudgement(false),
		m_postEffectManager{nullptr},
		m_menuManager{nullptr}
	{}

	//		デストラクタ
	~SceneManagerInformation() {};

	/*
	*	初期化処理
	* 
	*	@param	(postEffectManager)	ポストエフェクトマネージャのポインタ
	*/
	void Initialize(PostEffectManager* postEffectManager, MenuManager* menuManager)
	{
		m_postEffectManager = postEffectManager;
		m_menuManager = menuManager;
	}

private:

	//		ポストエフェクトマネージャーのポインタ
	PostEffectManager* m_postEffectManager;

	//		メニューマネージャーのポインタ
	MenuManager* m_menuManager;

	//        クリアタイム
	int m_clearTime;

	//        死亡カウント
	int m_deathCount;

	//		最大タイム
	int m_maxTime;

	//		ゲームを終了するか
	bool m_endJudgement;

public:

	/*
	*	ポストエフェクトを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	PostEffectManager* GetPostEffectManager() { return m_postEffectManager; }

	/*
	*	メニューマネージャーを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	MenuManager* GetMenuManager() { return m_menuManager; }

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
	*	最大時間を設定する
	*	
	*	@param	(time)	時間
	*/
	void SetMaxTime(int time) { m_maxTime = time; }

	/*
	*	最大時間を受け取る
	* 
	*	@return 時間
	*/
	int GetMaxTime() { return m_maxTime; }

	/*
	*	ゲームを終了するか設定する
	* 
	*	@param	(judgement)	true : 終了する false : 終了しない
	*/
	void SetEndJudgement(bool judgement) { m_endJudgement = judgement; }

	/*
	*	ゲームを終了するか受け取る
	* 
	*	@return true : 終了する false : 終了しない
	*/
	bool GetEndJudgement() { return m_endJudgement; }
};