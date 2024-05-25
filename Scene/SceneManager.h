/*
* @file		SceneManager.h
* @brief	�V�[���}�l�[�W���[
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "IScene.h"

#include "SceneState/PlayScene.h"

#include "SceneState/TitleScene.h"

class PlayScene;

class TitleScene;

class SceneManager
{
public:
	//		�R���X�g���N�^
	SceneManager();
	//		�f�X�g���N�^
	~SceneManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:
	//		�V�[��
	IScene* m_scene;

	//		�v���C�V�[��
	std::unique_ptr<PlayScene> m_playScene;

	//		�^�C�g���V�[��
	std::unique_ptr<TitleScene> m_titleScene;
};
