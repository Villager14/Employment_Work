/*
* @file		TitleScene.cpp
* @brief	�^�C�g���V�[��
* @author	Morita
* @date		2024/05/24
*/

#include "pch.h"

#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//		�^�C�g���I���}�l�[�W���[�̐���
	m_titleSelectManager = std::make_unique<TitleSelectManager>();

	//		�^�C�g���I���}�l�[�W���[�̏�����
	m_titleSelectManager->Initialize();
}

void TitleScene::Update()
{
	//		�^�C�g���I���}�l�[�W���[�̍X�V����
	m_titleSelectManager->Update();

	//		�V�[�����I�����邩�ǂ���
	if (m_titleSelectManager->GetChangeScnenJudgemnet())
	{
		//		�v���C�V�[���ɐ؂�ւ���
		m_sceneManager->ChangeState(m_sceneManager->GetPlayScene());
	}
}

void TitleScene::Render()
{
	//		�^�C�g���I���}�l�[�W���[�̕`�揈��
	m_titleSelectManager->Render();
}

void TitleScene::Finalize()
{
}
