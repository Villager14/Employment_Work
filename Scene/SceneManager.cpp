/*
* @file		SceneManager.cpp
* @brief	�V�[���}�l�[�W���[
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "SceneManager.h"

#include "SceneState/TutorialScene.h"
#include "SceneState/PlayScene.h"
#include "SceneState/TitleScene.h"
#include "SceneState/ResultScene.h"

SceneManager::SceneManager()
	:
	m_scene{},
	m_sceneType{}
{
	//		�V�[���}�l�[�W���[�̏��
	m_information = std::make_unique<SceneManagerInformation>();

	//		���j���[�}�l�[�W���[�̐���
	m_menuManager = std::make_unique<MenuManager>(this);

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[���󂯎��
	m_postEffectManager = std::make_unique<PostEffectManager>(m_menuManager->GetInformation());
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	m_information->Initialize(m_postEffectManager.get(), m_menuManager.get());

	//		���j���[�}�l�[�W���[�̏�����
	m_menuManager->Initialize();

	//		�V�[�����쐬����
	m_sceneInformation.insert({ SceneType::Title, std::make_unique<TitleScene>(this) });
	m_sceneInformation.insert({ SceneType::Play, std::make_unique<PlayScene>(this) });
	m_sceneInformation.insert({ SceneType::Result, std::make_unique<ResultScene>(this) });
	m_sceneInformation.insert({ SceneType::Tutorial, std::make_unique<TutorialScene>(this) });

	//		�����̃V�[���^�C�v��ݒ肷��
	m_sceneType = SceneType::Title;

	//		�V�[����ݒ肷��
	m_scene = m_sceneInformation[m_sceneType].get();

	//		�V�[��������������
	m_scene->Initialize();
}

void SceneManager::Update()
{
	//		�V�[���̍X�V����
	m_scene->Update();

	//		���j���[�}�l�[�W���[�̍X�V
	m_menuManager->Update();

	//		�Q�[�����I�����邩�H
	if (m_information->GetEndJudgement())
	{
		Finalize();
	}
}

void SceneManager::Render()
{
	//		�Q�[���I�����ɂ͕`�悵�Ȃ�
	if (m_information->GetEndJudgement()) return;

	//		�V�[���̕`�揈��
	m_scene->Render();

	//		���j���[�}�l�[�W���[�̕`��
	m_menuManager->Render();
}

void SceneManager::Finalize()
{
	//		���݂̏�Ԃ̏I������������
	m_scene->Finalize();

	//		�V�[���̏����폜����
	m_sceneInformation.clear();
}

void SceneManager::ChangeScene(SceneType type)
{
	//		�����V�[���̏ꍇ���������Ȃ�
	if (m_sceneType == type) return;

	//		���݂̏�Ԃ̏I������������
	m_scene->Finalize();

	//		��Ԃ�؂�ւ���
	m_sceneType = type;

	m_scene = m_sceneInformation[m_sceneType].get();

	//		�V������Ԃ̏���������������
	m_scene->Initialize();
}