/*
* @file		ClockBackGround.h
* @brief	UI���v�̔w�i
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "../UIRender.h"

class ClockBackGround
{
public:
	//		�R���X�g���N�^
	ClockBackGround();

	//		�f�X�g���N�^
	~ClockBackGround();

	//		��������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(elapsedTime)	�o�ߎ���
	*/
	void Update(float elapsedTime);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	const float ROTATION_RADIAN = 60.0f;

private:

	//		UI�̕`��
	std::unique_ptr<UIRender> m_uiRender;

	//		�R�����̕`��
	std::unique_ptr<UIRender> m_colonRender;

	//		�ŏ�����
	float m_rotationMin;

	//		�ő厞��
	float m_rotationMax;

	//		�ߋ��̎���
	float m_pastTime;
};
