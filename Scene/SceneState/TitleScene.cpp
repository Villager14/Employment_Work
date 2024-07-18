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

	//		�^�C�g����BGM�̍Đ�
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		���j���[�̏���ݒ肷��
	m_titleSelectManager->SetMenuInformation(m_sceneManager->GetMenuManager()->GetInformation());
}

void TitleScene::Update()
{
	//		���j���[���g�����Ԃɂ��邩�ǂ����H
	m_sceneManager->GetMenuManager()->GetInformation()->SetMenuUseJudgement(m_titleSelectManager->GetMenuUseJudgement());

	//		�^�C�g���I���}�l�[�W���[�̍X�V����
	m_titleSelectManager->Update();

	//		�V�[�����I�����邩�ǂ���
	if (m_titleSelectManager->GetChangeScnenJudgemnet())
	{
		//		�v���C�V�[���ɐ؂�ւ���
		m_sceneManager->ChangeScene(SceneManager::SceneType::Play);
	}
}

void TitleScene::Render()
{
	//		�^�C�g���I���}�l�[�W���[�̕`�揈��
	m_titleSelectManager->Render();
}

void TitleScene::Finalize()
{
	m_titleSelectManager.reset();
}
