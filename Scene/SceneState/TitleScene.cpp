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
	//		UI�̕`��̐���
	m_uiRender = std::make_unique<UIRender>();

	//		UI�̍쐻
	m_uiRender->Create(L"Resources/Texture/TitleScene/TitleRogo.png",
		{ 0.0f,-170.0f }, { 1.0f, 1.0f });

	//		�w�i�̐���
	m_backGroundMove = std::make_unique<BackGroundMove>();

	//		�w�i�̏�����
	m_backGroundMove->Initialize();

	//		�^�C�g���I���}�l�[�W���[�̐���
	m_titleSelectManager = std::make_unique<TitleSelectManager>();

	//		�^�C�g���I���}�l�[�W���[�̏�����
	m_titleSelectManager->Initialize();
}

void TitleScene::Update()
{
	//		�X�V����
	m_backGroundMove->Update();

	//		�^�C�g���I���}�l�[�W���[�̍X�V����
	m_titleSelectManager->Update();
}

void TitleScene::Render()
{
	m_backGroundMove->Render();

	m_uiRender->Render();

	//		�^�C�g���I���}�l�[�W���[�̕`�揈��
	m_titleSelectManager->Render();
}

void TitleScene::Finalize()
{
}
