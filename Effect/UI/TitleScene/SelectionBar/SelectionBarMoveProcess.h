/*
* @file		SelectionBarMoveProcess.h
* @brief	�I���o�[�̈ړ�����
* @author	Morita
* @date		2024/12/12
*/

#pragma once

class SelectionBar;

class SelectionBarMoveProcess
{
public:

	/*
	*	�R���X�g���N�^
	*
	*	@param	(selectionBar)	�I���o�[�̃|�C���^
	*/
	SelectionBarMoveProcess(SelectionBar* selectionBar);

	//		�f�X�g���N�^
	~SelectionBarMoveProcess();

	/*
	*	���S�Ə�̊Ԃ̏���
	*
	*	@param	(direction)	����
	*	@param	(time)		�o�ߎ���
	*	@param	(position)	���W
	*	@param	(scale)		�X�P�[��
	*/
	void CenterToTopProcess(bool direction, float time,
		DirectX::SimpleMath::Vector2* position,
		DirectX::SimpleMath::Vector2* scale);

	/*
	*	���S�Ɖ��̊Ԃ̏���
	*
	*	@param	(direction)	����
	*	@param	(time)		�o�ߎ���
	*	@param	(position)	���W
	*	@param	(scale)		�X�P�[��
	*/
	void CenterToBottom(bool direction, float time,
		DirectX::SimpleMath::Vector2* position,
		DirectX::SimpleMath::Vector2* scale);

	/*
	*	��Ɖ��̊Ԃ̏���
	*
	*	@param	(direction)	����
	*	@param	(time)		�o�ߎ���
	*	@param	(position)	���W
	*	@param	(scale)		�X�P�[��
	*/
	void FromTopToBottom(bool direction, float time,
		DirectX::SimpleMath::Vector2* position,
		DirectX::SimpleMath::Vector2* scale);

private:

	/*
	*	��������
	*
	*	@param	(time)	����
	*/
	inline void DecreaseValue(float time);

	/*
	*	�㏸����
	*
	*	@param	(time)	����
	*/
	inline void ElevatedValue(float time);

	/*
	*	���W�ƃT�C�Y�̍X�V
	* 
	*	@param	(position)	���W
	*	@param	(scale)		�X�P�[��
	*/
	void PositionSizeUpdate(DirectX::SimpleMath::Vector2* position,
		DirectX::SimpleMath::Vector2* scale);

private:

	//		�������W
	DirectX::SimpleMath::Vector2 m_firstPosition;

	//		�ŏI���W
	DirectX::SimpleMath::Vector2 m_endPosition;

	SelectionBar* m_selectionBar;

	//		�J�ڗ�(�ړ�)
	float m_move;

	//		�J�ڗ�(�T�C�Y)
	float m_size;

	//		�����T�C�Y
	float m_firstSize;

	//		�ŏI�T�C�Y
	float m_endSize;

};