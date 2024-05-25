/*
* @file		TitleScene.h
* @brief	�^�C�g���V�[��
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Scene/IScene.h"

#include "../SceneManager.h"

#include "Game/PlayScene/UIManager/UIRender.h"

#include "Game/TitleScene/UI/BackGroundMove.h"

#include "Game/TitleScene/UI/Select/TitleSelectManager.h"

class SceneManager;

class TitleScene : public IScene
{
public:

	//		�R���X�g���N�^
	TitleScene(SceneManager* sceneManager);

	//		�f�X�g���N�^
	~TitleScene();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:
	//		�V�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	SceneManager* m_sceneManager;

	//		UI�`��
	std::unique_ptr<UIRender> m_uiRender;

	//		�w�i�ړ�����
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	//		�^�C�g���I�����
	std::unique_ptr<TitleSelectManager> m_titleSelectManager;
};
