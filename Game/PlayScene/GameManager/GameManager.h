/*
* @file		GameManager.h
* @brief	ゲームマネージャー
* @author	Morita
* @date		2024/05/22
*/

#pragma once

class GameManager
{
public:

	GameManager();

	~GameManager();

	void Update();

private:

	//		時間
	float m_time;

	//		死亡回数
	int m_deathCount;

	//		ゲームを開始するか
	bool m_gameStartJudgement;

	//		死亡しているかどうか判断する
	bool m_deathJudgement;

	//		復活状態かどうか判断する
	bool m_revivalJudgement;

	//		ゴールしているかどうか
	bool m_goalJudgement;

	//		終了するかどうか
	bool m_endJudgement;

	//		次のシーンに行くか
	bool m_nextSceneJudgement;
public:
	/*
	*	時間を設定する
	* 
	*	@param	(time)	時間
	*/
	void SetTime(float time) { m_time = time; }

	/*
	*	時間を受け取る
	* 
	*	@return 時間
	*/
	float GetTime() { return m_time; }
	
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

	/*
	*	ゲームを開始するかどうか受け取る
	* 
	*	@return true : 開始 false : 開始していない
	*/
	bool GetGameStartJudgement() { return m_gameStartJudgement; }

	/*
	*	ゲームを開始するかどうか設定する
	* 
	*	@param	(judgement)	true : 開始 false : 開始していない
	*/
	void SetGameStartJudgement(bool judgement) { m_gameStartJudgement = judgement; }

	/*
	*	死亡しているかどうか受け取る
	* 
	*	@return true : 死亡している false : 死亡していない
	*/
	bool GetDeathJudgement() { return m_deathJudgement; }

	/*
	*	死亡しているかどうか設定する
	* 
	*	@param	(judgement)　true: 死亡している false : 死亡していない
	*/
	void SetDeathJudgement(bool judgement) { m_deathJudgement = judgement; }

	/*
	*	復活状態かどうか受け取る
	*
	*	@return true: 復活状態ではない false : 復活状態ではない
	*/
	bool GetRevivalJudgement() { return m_revivalJudgement; }

	/*
	*	復活状態かどうか設定する
	*
	*	@param	(judgement)　true: 復活状態ではない false : 復活状態ではない
	*/
	void SetRevivalJudgement(bool judgement) { m_revivalJudgement = judgement; }

	/*
	*	ゴールしているかどうか設定する
	*	
	*	@param	(judgement) true : ゴールしている false : ゴールしていない
	*/
	void SetGoalJudgement(bool judgement) { m_goalJudgement = judgement; }

	/*
	*	ゴールしているかどうか受け取る
	* 
	*	@return true : ゴールしている false : ゴールしていない
	*/
	bool GetGoalJudgement() { return m_goalJudgement; }

	/*
	*	終了するかどうか受け取る
	*	
	*	@return true : 終了する false : 終了しない
	*/
	bool GetEndJudgement() { return m_endJudgement; }

	/*
	*	終了するか設定する
	* 
	*	@param	(judgement)	true : 終了する false : 終了しない
	*/
	void SetEndJudgement(bool judgement) { m_endJudgement = judgement; }

	/*
	*	次のシーンに行くかどうか受け取る
	*
	*	@return true : 次にシーンに行く false : 次のシーンに行かない
	*/
	bool GetNextSceneJudgement() { return m_nextSceneJudgement; }

	/*
	*	次のシーンに行くかどうか設定する
	*
	*	@param	(judgement)	true : 次にシーンに行く false : 次のシーンに行かない
	*/
	void SetNextSceneJudgement(bool judgement) { m_nextSceneJudgement = judgement; }

};