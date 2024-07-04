/*
* @file		TitleScene.h
* @brief	�^�C�g���V�[��
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Scene/IScene.h"

#include "../SceneManager.h"

#include "Game/TitleScene/UI/Select/TitleSelectManager.h"

#include "Library/Shader/UIRenderManager.h"

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

public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
	};

private:
	//		�V�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	SceneManager* m_sceneManager;

	//		�^�C�g���I���}�l�[�W���[
	std::unique_ptr<TitleSelectManager> m_titleSelectManager;

	//		UI�V�F�[�_�[�}�l�[�W���[
	std::unique_ptr<UIRenderManager> m_uiShaderManager;
};
