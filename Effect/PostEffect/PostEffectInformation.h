/*
* @file		PostEffectInformation.h
* @brief	�|�X�g�G�t�F�N�g�̏��
* @author	Morita
* @date		2024/11/08
*/

#pragma once

#include "pch.h"

class PostEffectInformation
{
public:

	PostEffectInformation() 
		:
		m_flag(Flag::None)
	{
	};

	~PostEffectInformation() {};

	void Initialize()
	{
		m_flag = Flag::None;
	}

public:

	enum Flag
	{
		None				= 0b00000000,
		FadeJudgement		= 1 << 0,		//		�t�F�[�h�����邩�ǂ���
		SceneEndFade		= 1 << 1,		//		�V�[���̏I���t�F�[�h
		SceneEnd			= 1 << 2,		//		�V�[���̏I��
		TimeLimitJudgement	= 1 << 3,		//		�^�C�����~�b�g��
		FadeEnd				= 1 << 4,		//		�t�F�[�h�̏I��
		RedScreen			= 1 << 5,		//		��ʂ𖾂邭���邩
		FadeInEnd			= 1 << 6,		//		�t�F�[�h�C�����I���������H
	};

public:

	/*
	*	�t���O�������Ă��邩
	*
	*	@param	(flag)	�m�F�������t���O
	*	@return true : yes false : no
	*/
	bool FlagJudgement(Flag flag)
	{
		//		�����̃r�b�g���P�̏ꍇ
		if (m_flag & flag) return true;

		return false;
	}

	/*
	*	�t���O��On�ɂ���
	*
	*	@param	(flag)	�I���ɂ������t���O
	*/
	void TrueFlag(Flag flag)
	{
		m_flag |= flag;
	}


	/*
	*	�t���O��of�ɂ���
	*
	*	@param	(flag)	�I�t�ɂ������t���O
	*/
	void FalseFlag(Flag flag)
	{
		//		�t���O���I���̎��̓I�t�ɂ���
		m_flag &= ~flag;
	}

private:

	//		�t���O
	int m_flag;




};