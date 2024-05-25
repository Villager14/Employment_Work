/*
* @file		BackGroundMove.h
* @brief	�w�i�̈ړ�
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "BackGroundMoveRender.h"

class BackGroundMove
{
public:

	BackGroundMove();

	~BackGroundMove();

	void Initialize();

	void Update();

	void Render();

	void Finalize();


private:

	//		�w�i�ړ��̕`��
	std::unique_ptr<BackGroundMoveRender> m_backGroundMoveRender;

	//		����
	float m_time;

	//		�t�F�[�h�C�������邩�ǂ������f����
	bool m_fadeinResetJudgement;

	//		�t�F�[�h�A�E�g�����邩�ǂ������f����
	bool m_fadeoutResetJudgement;
};
