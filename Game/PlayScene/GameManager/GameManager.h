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

	//		����
	float m_time;

	//		���S��
	int m_deathCount;

	//		�Q�[�����J�n���邩
	bool m_gameStartJudgement;

	//		���S���Ă��邩�ǂ������f����
	bool m_deathJudgement;

	//		������Ԃ��ǂ������f����
	bool m_revivalJudgement;

	//		�S�[�����Ă��邩�ǂ���
	bool m_goalJudgement;

	//		�I�����邩�ǂ���
	bool m_endJudgement;

	//		���̃V�[���ɍs����
	bool m_nextSceneJudgement;
public:
	/*
	*	���Ԃ�ݒ肷��
	* 
	*	@param	(time)	����
	*/
	void SetTime(float time) { m_time = time; }

	/*
	*	���Ԃ��󂯎��
	* 
	*	@return ����
	*/
	float GetTime() { return m_time; }
	
	/*
	*	���S�񐔂�ݒ肷��
	* 
	*	@param	(count)	��
	*/
	void SetDeathCount(int count) { m_deathCount = count; }

	/*
	*	���S�񐔂��󂯎��
	* 
	*	@return ��
	*/
	int GetDeathCount() { return m_deathCount; }

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

	/*
	*	�S�[�����Ă��邩�ǂ����ݒ肷��
	*	
	*	@param	(judgement) true : �S�[�����Ă��� false : �S�[�����Ă��Ȃ�
	*/
	void SetGoalJudgement(bool judgement) { m_goalJudgement = judgement; }

	/*
	*	�S�[�����Ă��邩�ǂ����󂯎��
	* 
	*	@return true : �S�[�����Ă��� false : �S�[�����Ă��Ȃ�
	*/
	bool GetGoalJudgement() { return m_goalJudgement; }

	/*
	*	�I�����邩�ǂ����󂯎��
	*	
	*	@return true : �I������ false : �I�����Ȃ�
	*/
	bool GetEndJudgement() { return m_endJudgement; }

	/*
	*	�I�����邩�ݒ肷��
	* 
	*	@param	(judgement)	true : �I������ false : �I�����Ȃ�
	*/
	void SetEndJudgement(bool judgement) { m_endJudgement = judgement; }

	/*
	*	���̃V�[���ɍs�����ǂ����󂯎��
	*
	*	@return true : ���ɃV�[���ɍs�� false : ���̃V�[���ɍs���Ȃ�
	*/
	bool GetNextSceneJudgement() { return m_nextSceneJudgement; }

	/*
	*	���̃V�[���ɍs�����ǂ����ݒ肷��
	*
	*	@param	(judgement)	true : ���ɃV�[���ɍs�� false : ���̃V�[���ɍs���Ȃ�
	*/
	void SetNextSceneJudgement(bool judgement) { m_nextSceneJudgement = judgement; }

};