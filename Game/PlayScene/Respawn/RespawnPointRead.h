/*
* @file		RespawnPointRead.h
* @brief	���X�|�[���|�C���g�̓ǂݍ��ݏ���
* @author	Morita
* @date		2024/10/03
*/

#pragma once

#include <string>

class RespawnPointRead
{
public:

	//		�R���X�g���N�^
	RespawnPointRead();

	//		�f�X�g���N�^
	~RespawnPointRead();

	//		����������
	void ReadProcess(int stageNumber);

	/*
	*	�p�����[�^�[��ݒ肷��
	* 
	*	@param	(val)		�l
	*	@param	(index)		�v�f��
	*	@param	(position)	���W
	*	@param	(length)	����
	*/
	void SetParameter(std::string val, int index, DirectX::SimpleMath::Vector3 *position,
					 float *length);

private:

	//		���W
	std::vector<DirectX::SimpleMath::Vector3> m_position;

	//		����
	std::vector<float> m_length;

public:

	/*
	*	���X�|�[�����W���󂯎��
	* 
	*	@return ���W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetPosition() { return m_position; }

	/*
	*	�������󂯎��
	* 
	*	@return ����
	*/
	const std::vector<float>& GetLength() { return m_length; }
};