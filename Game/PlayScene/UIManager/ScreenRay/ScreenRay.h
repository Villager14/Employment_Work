/*
* @file		ScreenRay.h
* @brief	�Q�[���I�[�o�[�}�l�[�W���[
* @author	Morita
* @date		2024/05/23
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/PlayScene/UIManager/UIRender.h"

class ScreenRay
{
public:
	//		�R���X�g���N�^
	ScreenRay(GameManager* gameManager);

	//		�f�X�g���N�^
	~ScreenRay();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	//		�Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	GameManager* m_gameManager;

	//		�Q�[���I�[�o�[�̕`��
	std::unique_ptr<UIRender> m_screenRay;
};