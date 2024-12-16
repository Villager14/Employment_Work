/*
* @file		TutorialManager.h
* @brief	�`���[�g���A���V�[�����Ǘ�����
* @author	Morita
* @date		2024/09/17
*/

#pragma once

#include "ITutorialManager.h"

#include "State/TutorialWalkState.h"

#include "TutorialInformation.h"

#include "Test/Renderer.h"

#include "Test/RendererObject.h"

#include "Test/ModelMake.h"

#include "Test/IObjectMove.h"

class SceneManager;

class TutorialManager
{
public:

	//		�R���X�g���N�^
	TutorialManager(SceneManager* sceneManager);

	//		�f�X�g���N�^
	~TutorialManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		����
	void Generation();

public:

	enum TutorialState
	{
		Walk,	//		���s���
	};

private:

	//		�e��Ԃɉ������`���[�g���A���Ǘ��I�u�W�F�N�g��ێ�
	std::unordered_map<TutorialState, std::unique_ptr<ITutorialManager>> m_tutorialInformation;

	//		���݂̃`���[�g���A���̏��
	ITutorialManager* m_state;

	//		���݂̃`���[�g���A���̐i�s���
	TutorialState m_tutorialState;

	//		���
	std::unique_ptr<TutorialInformation> m_information;

	//		�`��
	std::unique_ptr<Renderer> m_renderer;

	//		�I�u�W�F�N�g
	std::unique_ptr<RendererObject> m_object;
	std::unique_ptr<RendererObject> m_object2;

	std::unique_ptr<ModelMake> m_modelMake;

	std::vector<std::unique_ptr<IObjectMove>> m_objectMove;

private:

	//		�V�[���}�l�[�W���[
	SceneManager* m_sceneManager;
};