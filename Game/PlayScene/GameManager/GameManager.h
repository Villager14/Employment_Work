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

	//		ゲームを開始するか
	bool m_gameStartJudgement;

	//		死亡しているかどうか判断する
	bool m_deathJudgement;

	//		復活状態かどうか判断する
	bool m_revivalJudgement;
public:
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

};