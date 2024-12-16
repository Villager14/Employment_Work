/*
* @file		SelectionBarMoveProcess.cpp
* @brief	�I���o�[�̈ړ�����
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
	//		�ړ����������ď�����ς���
	if (direction)
	{
		//		�������W
		m_firstPosition = m_selectionBar->CENTER_POINT;
		//		�I�����W
		m_endPosition = m_selectionBar->UP_POINT;

		DecreaseValue(time);
	}
	else
	{
		//		�������W
		m_firstPosition = m_selectionBar->UP_POINT;
		//		�I�����W
		m_endPosition = m_selectionBar->CENTER_POINT;

		ElevatedValue(time);
	}

	//		���W�ƃX�P�[���̍X�V
	PositionSizeUpdate(position, scale);
}

void SelectionBarMoveProcess::CenterToBottom(bool direction, float time,
	 DirectX::SimpleMath::Vector2* position, DirectX::SimpleMath::Vector2* scale)
{
	//		�ړ����������ď�����ς���
	if (direction)
	{
		//		�������W
		m_firstPosition = m_selectionBar->UNDER_POINT;
		//		�I�����W
		m_endPosition = m_selectionBar->CENTER_POINT;

		ElevatedValue(time);
	}
	else
	{
		//		�������W
		m_firstPosition = m_selectionBar->CENTER_POINT;
		//		�I�����W
		m_endPosition = m_selectionBar->UNDER_POINT;

		DecreaseValue(time);
	}

	//		���W�ƃX�P�[���̍X�V
	PositionSizeUpdate(position, scale);
}

void SelectionBarMoveProcess::FromTopToBottom(bool direction, float time, DirectX::SimpleMath::Vector2* position, DirectX::SimpleMath::Vector2* scale)
{
	//		�����T�C�Y
	m_firstSize = m_selectionBar->MIN_SCALE - 0.5f;
	//		�ŏI�T�C�Y
	m_endSize = m_selectionBar->MIN_SCALE;

	//		�ړ����������ď�����ς���
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

	//		���W�ƃX�P�[���̍X�V
	PositionSizeUpdate(position, scale);
}

inline void SelectionBarMoveProcess::DecreaseValue(float time)
{
	//		�ړ��̑J�ڗ�
	m_move = sqrt(1.0f - pow(time - 1.0f, 2.0f));
	//		�T�C�Y�̑J�ڗ�
	m_size = 1.0f - sqrt(1.0f - pow(time, 2.0f));

	//		�����T�C�Y��ݒ�
	m_firstSize = m_selectionBar->MAX_SCALE;
	//		�ŏI�T�C�Y��ݒ�
	m_endSize = m_selectionBar->MIN_SCALE;
}

inline void SelectionBarMoveProcess::ElevatedValue(float time)
{
	//		�ړ��̑J�ڗ�
	m_move = 1.0f - sqrt(1.0f - pow(time, 2.0f));
	//		�T�C�Y�̑J�ڗ�
	m_size = sqrt(1.0f - pow(time - 1.0f, 2.0f));

	//		�����T�C�Y��ݒ�
	m_firstSize = m_selectionBar->MIN_SCALE;
	//		�ŏI�T�C�Y��ݒ�
	m_endSize = m_selectionBar->MAX_SCALE;
}

void SelectionBarMoveProcess::PositionSizeUpdate
						(DirectX::SimpleMath::Vector2* position,
						 DirectX::SimpleMath::Vector2* scale)
{
	//		���W�̍X�V
	*position = DirectX::SimpleMath::Vector2::Lerp(m_firstPosition, m_endPosition, m_move);
	//		�X�P�[���̍X�V
	*scale = DirectX::SimpleMath::Vector2::Lerp({ m_firstSize, m_firstSize }, { m_endSize, m_endSize }, m_size);
}
