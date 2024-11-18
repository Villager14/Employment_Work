/*
* @file		PostEffectFlag.h
* @brief	�|�X�g�G�t�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/10/01
*/

#pragma once

#include "pch.h"

class PostEffectFlag
{
public:

	enum Flag
	{
		None =			0,
		Normal =		1 << 0,		//		�ʏ�`��
		BloomDepth =	1 << 1,		//		�u���[���[�x
		Bloom =			1 << 2,		//		�u���[��
		Fog =			1 << 3,		//		�t�H�O�̏���
		AlphaDepth =	1 << 4,		//		�A���t�@�[�x����
		Alpha =			1 << 5,		//		�A���t�@�̏���
		UI =			1 << 6,		//		UI�̕`��
		Color =			1 << 7,		//		��ʂ̐F�ύX
		PlayerView =	1 << 8,		//		�v���C���[�̕`��
		UIBack =		1 << 9,		//		UI�̌�`��
		Glitch =		1 << 10,	//		�O���b�`�m�C�Y
		Fade =			1 << 11,	//		�t�F�[�h
	};

public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(notFlagTrue) �r�b�g�t���O�̏����̒l��S��True�ɂ��邩�H
	*/
	PostEffectFlag(bool notFlagTrue = false)
	{
		m_flag = Flag::None;

		if (notFlagTrue)
		{
			m_flag = ~Flag::None;
		}
	};

	//		�f�X�g���N�^
	~PostEffectFlag() {};

private:

	//		�t���O
	int m_flag;

public:

	/*
	*	�t���O���󂯎��
	* 
	*	@return �t���O
	*/
	int GetFlag() { return m_flag; }

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
};