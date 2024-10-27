/*
* @file		SceneManager.cpp
* @brief	�V�[���}�l�[�W���[
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "SceneManager.h"


SceneManager::SceneManager()
	:
	m_scene{},
	m_deathCount(0),
	m_clearTime(0),
	m_sceneType{}
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	//		���j���[�}�l�[�W���[�̐���
	m_menuManager = std::make_unique<MenuManager>();

	//		���j���[�}�l�[�W���[�̏�����
	m_menuManager->Initialize();

	//		�V�[�����쐬����
	m_sceneInformation.insert({ SceneType::Title, std::make_unique<TitleScene>(this) });
	m_sceneInformation.insert({ SceneType::Play, std::make_unique<PlayScene>(this) });
	m_sceneInformation.insert({ SceneType::Result, std::make_unique<ResultScene>(this) });
	m_sceneInformation.insert({ SceneType::Tutorial, std::make_unique<TutorialScene>(this) });

	//		�����̃V�[���^�C�v��ݒ肷��
	m_sceneType = SceneType::Result;

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
}

void SceneManager::Render()
{
	//		�V�[���̕`�揈��
	m_scene->Render();

	//		���j���[�}�l�[�W���[�̕`��
	m_menuManager->Render();
}

void SceneManager::Finalize()
{
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
