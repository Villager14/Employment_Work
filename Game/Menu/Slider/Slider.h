/*
* @file		Slider.h
* @brief	�X���C�_�[�̏���
* @author	Morita
* @date		2024/07/03
*/
#pragma once

//#include "FadeRender.h"

#include "Game/PlayScene/GameManager/GameManager.h"

class Slider
{
public:

	Slider();

	~Slider();

	void Initialize();

	void Update(GameManager* gameManager);

	void Render();

	void Finalize();


private:

	//		�t�F�[�h�̕`��
	//std::unique_ptr<FadeRender> m_fadeRender;

	//		����
	float m_time;

	//		�ҋ@����
	float m_stayTime;

	//		�t�F�[�h�C�������邩�ǂ������f����
	bool m_fadeinResetJudgement;

	//		�t�F�[�h�A�E�g�����邩�ǂ������f����
	bool m_fadeoutResetJudgement;

	//		���߂̃t�F�[�h�C�����ǂ���
	bool m_firstJudgement;
};
