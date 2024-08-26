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

	void Initialize();

	void Update();

	void Finalize();
public:

	enum Flag
	{
		None = 0b0000000,
		GameStart			= 1 << 0,		//		�Q�[�����J�n���邩
		DeathJudgement		= 1 << 1,		//		���S���Ă��邩���f����
		RevivalJudgement	= 1 << 2,		//		�������Ă��邩���f����
		GoalJudgement		= 1 << 3,		//		�S�[�����Ă��邩���f����
		EndJudgement		= 1 << 4,		//		�I�����Ă��邩���f����
		NextScene			= 1 << 5,		//		���̃V�[���ɍs�������f����
		DamageObjectHit		= 1 << 6,		//		�_���[�W�I�u�W�F�N�g�ɓ������Ă��邩�ǂ���
		FallDead			= 1 << 7,		//		���������Ă��邩�ǂ���
	};

private:

	//		����
	float m_time;

	//		���S��
	int m_deathCount;

	//		�Q�[���̑��x
	float m_gameSpeed;

	//		�t���O
	int m_flag;

public:

	/*
	*	�t���O�������Ă��邩
	* 
	*	@param	(flag)	�m�F�������t���O
	*	@return true : yes false : no
	*/
	 bool FlagJudgement(Flag flag);

	/*
	*	�t���O��On�ɂ���
	* 
	*	@param	(flag)	�I���ɂ������t���O
	*/
	 void TrueFlag(Flag flag);

	/*	
	*	�t���O��of�ɂ���
	* 
	*	@param	(flag)	�I�t�ɂ������t���O
	*/
	 void FalseFlag(Flag flag);

	/*
	*	���Ԃ�ݒ肷��
	* 
	*	@param	(time)	����
	*/
	inline void SetTime(float time) { m_time = time; }

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
	*	�Q�[���̑��x��ݒ肷��
	* 
	*	@return ���x
	*/
	float GetGameSpeed() { return m_gameSpeed; }

	/*
	*	�Q�[���̑��x��ݒ肷��
	* 
	*	@param	(speed) ���x
	*/
	void SetGameSpeed(float speed) { m_gameSpeed = speed; }
};