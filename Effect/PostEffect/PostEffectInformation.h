/*
* @file		PostEffectInformation.h
* @brief	ポストエフェクトの情報
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
		FadeJudgement		= 1 << 0,		//		フェードをするかどうか
		SceneEndFade		= 1 << 1,		//		シーンの終了フェード
		SceneEnd			= 1 << 2,		//		シーンの終了
		TimeLimitJudgement	= 1 << 3,		//		タイムリミット時
		FadeEnd				= 1 << 4,		//		フェードの終了
		RedScreen			= 1 << 5,		//		画面を明るくするか
		FadeInEnd			= 1 << 6,		//		フェードインが終了したか？
	};

public:

	/*
	*	フラグが立っているか
	*
	*	@param	(flag)	確認したいフラグ
	*	@return true : yes false : no
	*/
	bool FlagJudgement(Flag flag)
	{
		//		両方のビットが１の場合
		if (m_flag & flag) return true;

		return false;
	}

	/*
	*	フラグをOnにする
	*
	*	@param	(flag)	オンにしたいフラグ
	*/
	void TrueFlag(Flag flag)
	{
		m_flag |= flag;
	}


	/*
	*	フラグをofにする
	*
	*	@param	(flag)	オフにしたいフラグ
	*/
	void FalseFlag(Flag flag)
	{
		//		フラグがオンの時はオフにする
		m_flag &= ~flag;
	}

private:

	//		フラグ
	int m_flag;




};