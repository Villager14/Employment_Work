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
	m_scene{}
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	//		�v���C�V�[���𐶐�����
	m_playScene = std::make_unique<PlayScene>(this);

	//		�����V�[����ݒ肷��
	m_scene = m_playScene.get();
	//		�V�[��������������
	m_scene->Initialize();
}

void SceneManager::Update()
{
	//		�V�[���̍X�V����
	m_scene->Update();
}

void SceneManager::Render()
{
	//		�V�[���̕`�揈��
	m_scene->Render();
}

void SceneManager::Finalize()
{
}
