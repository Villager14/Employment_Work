/*
* @file		CoolTime.h
* @brief	�N�[���^�C��
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "../CircleShader.h"

#include "../UIRender.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "../NumberShader.h"

class CoolTime
{
public:

	//		�R���X�g���N�^
	CoolTime();

	//		�f�X�g���N�^
	~CoolTime();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	*	
	*	�v���C���[�̏����󂯂Ƃ�
	*/
	void Update(PlayerInformation* playerInformation);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	enum State
	{
		None,		//		�����Ȃ����
		Reduce,		//		���炷���
		Increase	//		���₷���
	};

private:

	//		�����̒��S�̍��W
	const float NUMBER_CENTER_POSITION = 1179.0f;

	//		�����̊Ԋu
	const float NUMBER_INTERVAL = 30.0f;

private:

	//		�����̕`��
	std::unique_ptr<CircleShader> m_circleShader;

	//		�w�i�̕`��
	std::unique_ptr<UIRender> m_backRender;;

	//		�p�x
	float m_angle;

	//		����
	float m_time;

	//		�p�[�Z���g
	float m_ratio;

	//		�N�[���^�C���ɓ��������ǂ������f����
	bool m_coolTimeJudgement;

	//		���
	State m_state;

	//		�����̕`��
	std::unique_ptr<NumberShader> m_numberShader;

};
