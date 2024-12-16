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
	//		�^�C�g����UI�N���X�̐���
	m_titleUI = std::make_unique<TitleUI>();

	//		�^�C�g���̗���}�l�[�W���[�̐���
	m_titleFlowManager = std::make_unique<TitleFlowManager>();

	//		�^�C�g���|�X�g�G�t�F�N�g�}�l�[�W���[
	m_titlePostEffectManager = std::make_unique<TitlePostEffectManager>
				(sceneManager->GetInformation()->GetPostEffectManager());

	//		�^�C�g���V�[���؂�ւ��̏���
	m_titleSceneChange = std::make_unique<TitleSceneChange>(sceneManager);

	//		���j���[�}�l�W�����g�̐���
	m_menuManagement = std::make_unique<TitleMenuManagement>
		(m_sceneManager->GetInformation()->GetMenuManager()->GetInformation());

	//		�I�u�W�F�N�g�}�l�[�W���[�̐���
	m_objectManager = std::make_unique<ObjectManager>();

	//		�^�C�g���̃v���C���[�̐���
	m_player = std::make_unique<TitlePlayer>();

	//		�^�C�g���G�t�F�N�g�}�l�[�W���[�̐���
	m_titleEffectManager = std::make_unique<TitleEffectManager>();

	//		�^�C�g���J�����}�l�[�W���[
	m_cameraManager = std::make_unique<TitleCameraManager>();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{	
	//		�^�C�g����BGM�̍Đ�
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		�^�C�g����UI�̏�����
	m_titleUI->Initalize();

	//		�^�C�g���̗���}�l�[�W���[�̏�����
	m_titleFlowManager->Initialize();

	//		�^�C�g���|�X�g�G�t�F�N�g�}�l�[�W���[
	m_titlePostEffectManager->Initialize();

	//		�I�u�W�F�N�g�}�l�[�W���[�̏�����
	m_objectManager->Initialize(ObjectManager::Title);

	//		�v���C���[�̏���������
	m_player->Initialize();

	//		�^�C�g���G�t�F�N�g�}�l�[�W���[�̏���������
	m_titleEffectManager->Initialize();

	//		�J�����}�l�[�W���̏�����
	m_cameraManager->Initialize();

	//		�I�u�U�[�o�[�̒ǉ�
	AddObserver();
}

void TitleScene::Update()
{
	//		���j���[���g�p���Ă���ꍇ�͏��������Ȃ�
	if (m_menuManagement->MenuUseJudgement()) return;

	//		�^�C�g���V�[����UI�̍X�V����
	m_titleUI->Update();

	//		�^�C�g���̗���}�l�[�W���[�̍X�V
	m_titleFlowManager->Update();

	//		�|�X�g�G�t�F�N�g�̍X�V
	m_titlePostEffectManager->Update();

	//		�v���C���[�̍X�V
	m_player->Update();

	//		�^�C�g���G�t�F�N�g�}�l�[�W���̍X�V����
	m_titleEffectManager->Update();

	//		�J�����}�l�[�W���[�̍X�V
	m_cameraManager->Update();
}

void TitleScene::Render()
{
	//		�|�X�g�G�t�F�N�g�̍X�V
	for (int i = 1; i <= PostEffectFlag::Fade;)
	{
		//		�|�X�g�G�t�F�N�g���g�p���邩?
		if (!m_titlePostEffectManager->PostEffectUseJudgement(i))
		{
			i = i + i;

			continue;
		}

		//		�|�X�g�G�t�F�N�g�̍X�V
		m_titlePostEffectManager->PostEffectUpdate(i);

		//		�v���C���[�̕`��
		m_player->Render(PostEffectFlag::Flag(i));

		//		�I�u�W�F�N�g�̕`��
		m_objectManager->Render({0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f},
			PostEffectFlag::Flag(i),
			m_sceneManager->GetInformation()->
			GetPostEffectManager()->GetPostObjectShader());

		//		�^�C�g���G�t�F�N�g�}�l�[�W���[�̕`��
		m_titleEffectManager->Render(PostEffectFlag::Flag(i));

		//		�^�C�g���V�[����UI�̕`�揈��
		m_titleUI->Render(i);

		//		�|�X�g�G�t�F�N�g�̕`��
		m_titlePostEffectManager->PostEffectRender(i);

		i = i + i;
	}

	//		�|�X�g�G�t�F�N�g�̃e�N�X�`���`��
	m_titlePostEffectManager->PostEffectTextureRender();
}

void TitleScene::Finalize()
{
	//		�^�C�g��UI�̏I������
	m_titleUI->Finalize();

	//		�^�C�g������}�l�[�W���̏I������
	m_titleFlowManager->Finalize();

	//		�^�C�g���|�X�g�G�t�F�N�g�̏I������
	m_titlePostEffectManager->Finalize();

	//		�I�u�W�F�N�g�}�l�[�W���[�̏I������
	m_objectManager->Finalize();

	//		�v���C���[�̏I������
	m_player->Finalize();

	//		�^�C�g���G�t�F�N�g�}�l�[�W���[�̏I������
	m_titleEffectManager->Finalize();

	//		�J�����}�l�[�W���[�̏I������
	m_cameraManager->Finalize();
}

void TitleScene::AddObserver()
{
	//		�^�C�g���|�X�g�G�t�F�N�g�I�u�U�[�o�[�ɓo�^����i�^�C�g���̗���j
	m_titlePostEffectManager->AddTitlePostEffectObserver(m_titleFlowManager.get());

	//		�^�C�g���|�X�g�G�t�F�N�g�I�u�U�[�o�[�ɓo�^����(�V�[���؂�ւ�)
	m_titlePostEffectManager->AddTitlePostEffectObserver(m_titleSceneChange.get());

	//		�^�C�g��UI�I�u�U�[�o�[�ɓo�^����i�^�C�g��UI�j
	m_titleFlowManager->AddITitleUIObserver(m_titleUI.get());

	//		�^�C�g���t�F�[�h�I�u�U�[�o�[�ɓo�^����i�|�X�g�G�t�F�N�g�j
	m_titleFlowManager->AddIFadeObserver(m_titlePostEffectManager.get());

	//		�^�C�g���J�����̃I�u�U�[�o�[�ɓo�^����i�|�X�g�G�t�F�N�g�j
	m_cameraManager->AddFadeObserver(m_titlePostEffectManager.get());

	//		�^�C�g���J�����̃I�u�U�[�o�[�ɓo�^����(�^�C�g��UI)
	m_cameraManager->AddFadeObserver(m_titleUI.get());

	//		�^�C�g���Q�[���I���I�u�U�[�o�[�ɓo�^����i�V�[���؂�ւ��j
	m_titleFlowManager->AddGameExitObserver(m_titleSceneChange.get());

	//		�^�C�g�����j���[�g�p�I�u�U�[�o�[�ɓo�^����(���j���[�}�l�[�W���[)
	m_titleFlowManager->AddMenUseObserver(m_menuManagement.get());

	//		�^�C�g���̃A�j���[�V�����I�u�U�[�o�[�ɓo�^����i�v���C���[�j
	m_titleFlowManager->AddAnimationObserver(m_player.get());
}