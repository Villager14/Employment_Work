/*
* @file		PostEffectFlag.h
* @brief	ポストエフェクトマネージャー
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
		Normal =		1 << 0,		//		通常描画
		BloomDepth =	1 << 1,		//		ブルーム深度
		Bloom =			1 << 2,		//		ブルーム
		Fog =			1 << 3,		//		フォグの処理
		AlphaDepth =	1 << 4,		//		アルファ深度処理
		Alpha =			1 << 5,		//		アルファの処理
		UI =			1 << 6,		//		UIの描画
		Color =			1 << 7,		//		画面の色変更
		PlayerView =	1 << 8,		//		プレイヤーの描画
		UIBack =		1 << 9,		//		UIの後描画
		Glitch =		1 << 10,	//		グリッチノイズ
		Fade =			1 << 11,	//		フェード
	};

public:

	/*
	*	コンストラクタ
	* 
	*	@param	(notFlagTrue) ビットフラグの初期の値を全てTrueにするか？
	*/
	PostEffectFlag(bool notFlagTrue = false)
	{
		m_flag = Flag::None;

		if (notFlagTrue)
		{
			m_flag = ~Flag::None;
		}
	};

	//		デストラクタ
	~PostEffectFlag() {};

private:

	//		フラグ
	int m_flag;

public:

	/*
	*	フラグを受け取る
	* 
	*	@return フラグ
	*/
	int GetFlag() { return m_flag; }

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
};