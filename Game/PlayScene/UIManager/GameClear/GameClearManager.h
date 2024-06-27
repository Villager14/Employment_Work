/*
* @file		GameOverManager.h
* @brief	�Q�[���I�[�o�[�}�l�[�W���[
* @author	Morita
* @date		2024/05/23
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/PlayScene/UIManager/UIRender.h"

#include "../CenterShader.h"

#include "../GlitchShader.h"

class GameClearManager
{
public:
	//		�R���X�g���N�^
	GameClearManager(GameManager* gameManager);

	//		�f�X�g���N�^
	~GameClearManager();

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
	std::vector<std::unique_ptr<UIRender>> m_gameOverRender;

	//		���S�V�F�[�_�[
	std::unique_ptr<CenterShader> m_centerShader;

	//		�O���b�`�V�F�[�_�[
	std::unique_ptr<GlitchShader> m_glitchShader;

	//		�o�ߎ���
	float m_elapsedTime;

	//		�X�P�[��
	float m_scale;

	//		�ړ���
	float m_move;
};