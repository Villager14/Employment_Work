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

	//		�}�E�X�̃L�[���͂̐���
	m_mouseKeyInput = std::make_unique<MouseKeyInput>();

	//		�L�[�{�[�h�̃L�[���͂̐���
	m_keyboardInput = std::make_unique<KeyboardManager>();

	//		���j���[�}�l�[�W���[�̐���
	m_menuManager = std::make_unique<MenuManager>(this);

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[���󂯎��
	m_postEffectManager = std::make_unique<PostEffectManager>();

	//		��������
	m_information->Initialize(m_postEffectManager.get(),
		m_menuManager.get(),
		m_mouseKeyInput.get(),
		m_keyboardInput.get());

	//		�L�[�{�[�h�I�u�U�[�o�[�ɓo�^����
	m_menuManager->KeyboardAddObserver();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	//		���j���[�}�l�[�W���[�̏�����
	m_menuManager->Initialize();

	m_titleScene = std::make_unique<TitleScene>(this);
	m_playScene = std::make_unique<PlayScene>(this);
	m_resultScene = std::make_unique<ResultScene>(this);

	//		�V�[�����쐬����
	m_sceneInformation.insert({ SceneType::Title, m_titleScene.get() });
	m_sceneInformation.insert({ SceneType::Play, m_playScene.get() });
	m_sceneInformation.insert({ SceneType::Result, m_resultScene.get() });

	AddObserver();

	//		�����̃V�[���^�C�v��ݒ肷��
	m_sceneType = SceneType::Play;

	//		�V�[����ݒ肷��
	m_scene = m_sceneInformation[m_sceneType];

	//		�V�[��������������
	m_scene->Initialize();
}

void SceneManager::Update()
{
	//		�}�E�X�̃L�[���͂̍X�V
	m_mouseKeyInput->Update();

	//		�L�[�{�[�h�̓��͂̍X�V
	m_keyboardInput->Update();

	//		�V�[���̍X�V����
	m_scene->Update();

	//		���j���[�}�l�[�W���[�̍X�V
	m_menuManager->Update();

	//		�Q�[�����I�����邩�H
	if (m_information->GetEndJudgement())
	{
		Finalize();

		//		�}�E�X�̃L�[���͏I������
		m_mouseKeyInput->Finalize();
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

void SceneManager::AddObserver()
{
	//		���j���[���J���Ă��邩���f����I�u�U�[�o�[�ɓo�^����i�|�X�g�G�t�F�N�g�j
	m_menuManager->AddMenuOpenObserver(m_postEffectManager.get());
	//		���j���[���J���Ă��邩���f����I�u�U�[�o�[�ɓo�^���� (�^�C�g���V�[��)
	m_menuManager->AddMenuOpenObserver(m_titleScene.get());
	//		���j���[���J���Ă��邩���f����I�u�U�[�o�[�ɓo�^���� (�v���C�V�[��)
	m_menuManager->AddMenuOpenObserver(m_playScene.get());
	//		���j���[���J���Ă��邩���f����I�u�U�[�o�[�ɓo�^���� (���U���g�V�[��)
	m_menuManager->AddMenuOpenObserver(m_resultScene.get());

	//		���j���[���g�p���邩���f����I�u�U�[�o�[�ɓo�^����i���j���[�j
	m_titleScene->GetMenuUsedObserver()->AddObserver(m_menuManager.get());
	//		���j���[���g�p���邩���f����I�u�U�[�o�[�ɓo�^����i���j���[�j
	m_playScene->GetMenuUsedObserver()->AddObserver(m_menuManager.get());
	//		���j���[���g�p���邩���f����I�u�U�[�o�[�ɓo�^����i���j���[�j
	m_resultScene->GetMenuUsedObserver()->AddObserver(m_menuManager.get());

	//		���j���[���J�������f����I�u�U�[�o�[�ɓo�^����(���j���[)
	m_titleScene->AddMenuOpenObserver(m_menuManager.get());

	//		�J�����̑��x�I�u�U�[�o�[�ɓo�^����i�v���C���j
	m_menuManager->AddCameraSpeed(m_playScene.get());
	//		�J�����̎���p�I�u�U�[�o�[�ɓo�^����i�v���C���j
	m_menuManager->AddCameraViewAngle(m_playScene.get());
}

void SceneManager::ChangeScene(SceneType type)
{
	//		�����V�[���̏ꍇ���������Ȃ�
	if (m_sceneType == type) return;

	//		���݂̏�Ԃ̏I������������
	m_scene->Finalize();

	//		��Ԃ�؂�ւ���
	m_sceneType = type;

	m_scene = m_sceneInformation[m_sceneType];

	//		�V������Ԃ̏���������������
	m_scene->Initialize();
}