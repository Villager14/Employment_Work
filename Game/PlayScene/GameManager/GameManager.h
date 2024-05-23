/*
* @file		GameManager.h
* @brief	�Q�[���}�l�[�W���[
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

	//		�Q�[�����J�n���邩
	bool m_gameStartJudgement;

	//		���S���Ă��邩�ǂ������f����
	bool m_deathJudgement;

	//		������Ԃ��ǂ������f����
	bool m_revivalJudgement;
public:
	/*
	*	�Q�[�����J�n���邩�ǂ����󂯎��
	* 
	*	@return true : �J�n false : �J�n���Ă��Ȃ�
	*/
	bool GetGameStartJudgement() { return m_gameStartJudgement; }

	/*
	*	�Q�[�����J�n���邩�ǂ����ݒ肷��
	* 
	*	@param	(judgement)	true : �J�n false : �J�n���Ă��Ȃ�
	*/
	void SetGameStartJudgement(bool judgement) { m_gameStartJudgement = judgement; }

	/*
	*	���S���Ă��邩�ǂ����󂯎��
	* 
	*	@return true : ���S���Ă��� false : ���S���Ă��Ȃ�
	*/
	bool GetDeathJudgement() { return m_deathJudgement; }

	/*
	*	���S���Ă��邩�ǂ����ݒ肷��
	* 
	*	@param	(judgement)�@true: ���S���Ă��� false : ���S���Ă��Ȃ�
	*/
	void SetDeathJudgement(bool judgement) { m_deathJudgement = judgement; }

	/*
	*	������Ԃ��ǂ����󂯎��
	*
	*	@return true: ������Ԃł͂Ȃ� false : ������Ԃł͂Ȃ�
	*/
	bool GetRevivalJudgement() { return m_revivalJudgement; }

	/*
	*	������Ԃ��ǂ����ݒ肷��
	*
	*	@param	(judgement)�@true: ������Ԃł͂Ȃ� false : ������Ԃł͂Ȃ�
	*/
	void SetRevivalJudgement(bool judgement) { m_revivalJudgement = judgement; }

};