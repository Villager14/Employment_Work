/*
* @file		SelectionBarMoveProcess.cpp
* @brief	選択バーの移動処理
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "SelectionBarMoveProcess.h"

#include "SelectionBar.h"

SelectionBarMoveProcess::SelectionBarMoveProcess(SelectionBar* selectionBar)
	:
	m_selectionBar(selectionBar),
	m_size(0.0f),
	m_move(0.0f),
	m_firstSize(0.0f),
	m_endSize(0.0f)
{
}

SelectionBarMoveProcess::~SelectionBarMoveProcess()
{
}

void SelectionBarMoveProcess::CenterToTopProcess(bool direction, float time,
												DirectX::SimpleMath::Vector2* position,
												DirectX::SimpleMath::Vector2* scale)
{
	//		移動方向を見て処理を変える
	if (direction)
	{
		//		初期座標
		m_firstPosition = m_selectionBar->CENTER_POINT;
		//		終了座標
		m_endPosition = m_selectionBar->UP_POINT;

		DecreaseValue(time);
	}
	else
	{
		//		初期座標
		m_firstPosition = m_selectionBar->UP_POINT;
		//		終了座標
		m_endPosition = m_selectionBar->CENTER_POINT;

		ElevatedValue(time);
	}

	//		座標とスケールの更新
	PositionSizeUpdate(position, scale);
}

void SelectionBarMoveProcess::CenterToBottom(bool direction, float time,
	 DirectX::SimpleMath::Vector2* position, DirectX::SimpleMath::Vector2* scale)
{
	//		移動方向を見て処理を変える
	if (direction)
	{
		//		初期座標
		m_firstPosition = m_selectionBar->UNDER_POINT;
		//		終了座標
		m_endPosition = m_selectionBar->CENTER_POINT;

		ElevatedValue(time);
	}
	else
	{
		//		初期座標
		m_firstPosition = m_selectionBar->CENTER_POINT;
		//		終了座標
		m_endPosition = m_selectionBar->UNDER_POINT;

		DecreaseValue(time);
	}

	//		座標とスケールの更新
	PositionSizeUpdate(position, scale);
}

void SelectionBarMoveProcess::FromTopToBottom(bool direction, float time, DirectX::SimpleMath::Vector2* position, DirectX::SimpleMath::Vector2* scale)
{
	//		初期サイズ
	m_firstSize = m_selectionBar->MIN_SCALE - 0.5f;
	//		最終サイズ
	m_endSize = m_selectionBar->MIN_SCALE;

	//		移動方向を見て処理を変える
	if (direction)
	{
		m_firstPosition = m_selectionBar->UP_POINT;
		m_endPosition = m_selectionBar->UNDER_POINT;
	}
	else
	{
		m_firstPosition = m_selectionBar->UNDER_POINT;
		m_endPosition = m_selectionBar->UP_POINT;
	}

	m_move = time * time * time;

	float radian = Library::Lerp(0.0f, 360.0f, m_move);

	m_size = (cosf(DirectX::XMConvertToRadians(radian)) / 2.0f + 0.5f);

	m_size = Library::Clamp(m_size, 0.0f, 1.0f);

	//		座標とスケールの更新
	PositionSizeUpdate(position, scale);
}

inline void SelectionBarMoveProcess::DecreaseValue(float time)
{
	//		移動の遷移量
	m_move = sqrt(1.0f - pow(time - 1.0f, 2.0f));
	//		サイズの遷移量
	m_size = 1.0f - sqrt(1.0f - pow(time, 2.0f));

	//		初期サイズを設定
	m_firstSize = m_selectionBar->MAX_SCALE;
	//		最終サイズを設定
	m_endSize = m_selectionBar->MIN_SCALE;
}

inline void SelectionBarMoveProcess::ElevatedValue(float time)
{
	//		移動の遷移量
	m_move = 1.0f - sqrt(1.0f - pow(time, 2.0f));
	//		サイズの遷移量
	m_size = sqrt(1.0f - pow(time - 1.0f, 2.0f));

	//		初期サイズを設定
	m_firstSize = m_selectionBar->MIN_SCALE;
	//		最終サイズを設定
	m_endSize = m_selectionBar->MAX_SCALE;
}

void SelectionBarMoveProcess::PositionSizeUpdate
						(DirectX::SimpleMath::Vector2* position,
						 DirectX::SimpleMath::Vector2* scale)
{
	//		座標の更新
	*position = DirectX::SimpleMath::Vector2::Lerp(m_firstPosition, m_endPosition, m_move);
	//		スケールの更新
	*scale = DirectX::SimpleMath::Vector2::Lerp({ m_firstSize, m_firstSize }, { m_endSize, m_endSize }, m_size);
}
