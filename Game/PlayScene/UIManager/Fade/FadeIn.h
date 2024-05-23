/*
* @file		FadeIn.h
* @brief	�t�F�[�h�̏���
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "FadeRender.h"

#include "Game/PlayScene/GameManager/GameManager.h"

class FadeIn
{
public:

	FadeIn();

	~FadeIn();

	void Initialize();

	void Update(GameManager* gameManager);

	void Render();

	void Finalize();


private:

	//		�t�F�[�h�̕`��
	std::unique_ptr<FadeRender> m_fadeRender;

	//		����
	float m_time;

	//		�t�F�[�h�C�������邩�ǂ������f����
	bool m_fadeinResetJudgement;

	//		�t�F�[�h�A�E�g�����邩�ǂ������f����
	bool m_fadeoutResetJudgement;
};
