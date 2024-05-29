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
	m_clearTime(0),
	m_deathCount(0)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	//		�v���C�V�[���𐶐�����
	m_playScene = std::make_unique<PlayScene>(this);
	//		�^�C�g���V�[���𐶐�����
	m_titleScene = std::make_unique<TitleScene>(this);
	//		���U���g�V�[���𐶐�����
	m_resultScene = std::make_unique<ResultScene>(this);
	//		�����V�[����ݒ肷��
	m_scene = m_titleScene.get();
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

void SceneManager::ChangeState(IScene* state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_scene == state) return;

	//		���݂̏�Ԃ̏I������������
	m_scene->Finalize();

	//		��Ԃ�؂�ւ���
	m_scene = state;

	//		�V������Ԃ̏���������������
	m_scene->Initialize();
}
