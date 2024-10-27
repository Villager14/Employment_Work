/*
* @file		PlayScene.cpp
* @brief	�v���C�V�[��
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "PlayScene.h"

#include "Common/DebugDraw.h"

PlayScene::PlayScene(SceneManager* sceneManager)
	:
	m_sceneManager{sceneManager},
	m_menuCloseJugement(false)
{
	Generation();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//		���~�b�g�^�C����ݒ肷��
	m_gameManager->SetLimitTime(90.0f);

	//		�Q�[���}�l�[�W���[�̏���������
	m_gameManager->Initialize();

	//		�v���C���[�J�����}�l�[�W���[�̏���������
	m_playerCameraManager->Initialize(m_player->GetInformation());

	//		�J�����̏����󂯎��
	m_player->SetCameraInformation(m_playerCameraManager->GetInformation());

	//		�v���C���[�̏���������
	m_player->Initialize();

	//		�e�̏�����
	//m_shadow->Initialize();

	//		�I�u�W�F�N�g�}�l�[�W���[�̏���������
	m_objectManager->Initialize();

	//		UI�}�l�[�W���[�̏�����
	m_uiManager->Initialize();

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[�̏�����
	//m_screenEffectManager->Initialize();

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̏�����
	m_postEffectManager->Initialize(m_gameManager->BACK_GROUND_COLOR);

	//		���C���[�̏����󂯎��
	m_effectManager->SetWireInformation(m_objectManager->GetUseWireInformation());

	//		�G�t�F�N�g�}�l�[�W���[�̏�����
	m_effectManager->Initialize();

	//		�G�l�~�[�}�l�[�W���[�̏�����
	m_enemyManager->Initialize();

	//		���X�|�[���}�l�[�W���[�̏�����
	m_respawnManager->Initialize();

	//		�v���C�V�[������BGM���Đ�
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::PlayScene);

	//		����p�̏����󂯎��
	m_playerCameraManager->GetInformation()->SetViewAngle(m_sceneManager->GetMenuManager()->GetInformation()->GetViewAngle());

	//		����p�̍X�V
	m_playerCameraManager->ViewAngleUpdate(m_player->GetInformation());

	//		�J�����̑��x�̍X�V
	m_playerCameraManager->GetInformation()->SetCameraSpeed(m_sceneManager->GetMenuManager()->GetInformation()->GetCameraSpeed());
}

void PlayScene::Generation()
{
	//		�Q�[���}�l�[�W���[�𐶐�����
	m_gameManager = std::make_unique<GameManager>();

	//		�v���C���[�J�����}�l�[�W���[�̐���
	m_playerCameraManager = std::make_unique<PlayerCameraManager>(m_gameManager.get());

	//		�v���C���[�̐���
	m_player = std::make_unique<Player>(m_gameManager.get());

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[�̐���
	//m_screenEffectManager = std::make_unique<ScreenEffectManager>
	//	(ScreenEffectManager::Scene::PlayScene, m_gameManager.get());

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	m_postEffectManager = std::make_unique<PostEffectManager>(m_gameManager.get(),
															  m_sceneManager->GetMenuManager()->GetInformation());

	//		�G�t�F�N�g�}�l�[�W���[�̍쐻
	m_effectManager = std::make_unique<EffectManager>(m_player->GetInformation(), m_playerCameraManager->GetInformation());

	//		UI�}�l�[�W���[�̐���
	m_uiManager = std::make_unique<UIManager>(m_player->GetInformation(), m_gameManager.get());

	//		�����蔻��}�l�[�W���[�̐���
	m_collitionManager = std::make_unique<CollitionManager>(m_gameManager.get());

	//		�e�̐���
	m_shadow = std::make_unique<Shadow>();

	//		�I�u�W�F�N�g�}�l�[�W���[�̐���
	m_objectManager = std::make_unique<ObjectManager>(m_shadow->GetInformation(), m_gameManager.get());

	//		�G�l�~�[�}�l�[�W���[�̐���
	m_enemyManager = std::make_unique<EnemyManager>();

	//		���X�|�[���}�l�[�W���[
	m_respawnManager = std::make_unique<RespawnManager>(m_gameManager.get());
}

bool PlayScene::MenuInformation()
{
	//		���j���[���J���Ă���ꍇ�̏���
	if (m_sceneManager->GetMenuManager()->GetInformation()->GetMenuJudgement())
	{
		//		���j���[���J���Ă���
		m_menuCloseJugement = true;

		//		����p�̏����󂯎��
		m_playerCameraManager->GetInformation()->SetViewAngle(m_sceneManager->GetMenuManager()->GetInformation()->GetViewAngle());

		//		����p�̍X�V
		m_playerCameraManager->ViewAngleUpdate(m_player->GetInformation());

		//		�J�����̑��x�̍X�V
		m_playerCameraManager->GetInformation()->SetCameraSpeed(m_sceneManager->GetMenuManager()->GetInformation()->GetCameraSpeed());

		//		�O���C
		//m_screenEffectManager->GrayScare(m_sceneManager->GetMenuManager()->GetInformation());
		m_postEffectManager->Update(PostEffectFlag::Flag::Color);

		return true;
	}

	return false;
}

void PlayScene::Update()
{
	//		���j���[���J���Ă��邩�ǂ���
	if (MenuInformation()) return;

	//		���j���[���g���邩�ǂ����H
	m_sceneManager->GetMenuManager()->GetInformation()->SetMenuUseJudgement(m_player->GetMenuUseJugement());

	//		�I�u�W�F�N�g�}�l�[�W���[�̍X�V����
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		�͈͓��ɂ��郏�C���[�̍��W���󂯎��
	//m_player->GetInformation()->SetWirePosition(m_objectManager->GetWirePosition());

	//		���C���[�̏����󂯎��
	m_player->SetWireInformation(m_objectManager->GetUseWireInformation());


	//		�����x�N�g����ݒ肷��
	m_player->GetInformation()->SetViewVelocity(m_playerCameraManager->GetInformation()->GetViewVelocity());

	//		�v���C���[�̍X�V����
	m_player->Update(m_playerCameraManager->GetInformation());

	//		���b�V�����󂯎��
	m_collitionManager->SetObjectMesh(m_objectManager->GetMesh());

	//		�����蔻��̍X�V����
	m_collitionManager->Update(m_player->GetPlayerInformationCollition());

	//		�����蔻��̏��
	m_player->SetCollitionInformation(m_collitionManager->GetCollitionInformation());

	//		���b�V���A�b�v�f�[�g
	m_player->MeshUpdate();

	//		�}�E�X��΃��[�h���瑊�΃��[�h�ɐ؂�ւ�鎞��t���[���K�v�Ȃ̂�
	if (m_menuCloseJugement)
	{
		m_menuCloseJugement = false;
	}
	else
	{
		//		�J�����}�l�[�W���[�̍X�V����
		m_playerCameraManager->Update();
	}

	//		�v���C���[�ɃJ�����̊p�x�𑗂�
	m_player->GetInformation()->SetCameraAngle(m_playerCameraManager->GetInformation()->GetAngle());

	//		�A�j���[�V�����̃A�b�v�f�[�g
	m_player->AnimationUpdate();

	//		UI�}�l�[�W���[�̍X�V
	m_uiManager->Update();

	//		�|�X�g�G�t�F�N�g�̍X�V����
	for (int i = 1; i <= PostEffectFlag::Flag::Fade;)
	{
		m_postEffectManager->Update(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		�Q�[���}�l�[�W���[�̍X�V����
	m_gameManager->Update();

	//		�G�t�F�N�g�}�l�[�W���[�̕`��
	m_effectManager->Update();

	//		���X�|�[���|�C���g�̍X�V����
	m_respawnManager->Update(m_player->GetInformation()->GetPosition());

	//		���X�|�[�����W��ݒ肷��
	m_player->GetInformation()->SetRespawnPosition(m_respawnManager->GetRespownPosition());

	//		���̃V�[���ɐ؂�ւ��邩�ǂ���
	if (m_gameManager->FlagJudgement(GameManager::NextScene))
	{
		//		�N���A�^�C�����󂯎��
		m_sceneManager->SetClearTime(static_cast<int>(m_gameManager->GetTime()));

		//		���S�񐔂��󂯎��
		m_sceneManager->SetDeathCount(static_cast<int>(m_gameManager->GetDeathCount()));

		//		���̃V�[���ɐ؂�ւ���i���U���g�V�[���j
		m_sceneManager->ChangeScene(SceneManager::SceneType::Result);
	}

	m_enemyManager->Update(m_gameManager->GetTime(),
		m_player->GetInformation()->GetPosition());
}

void PlayScene::Render()
{
	/*
	//		�����_�[�^�[�Q�b�g�̕ύX
	//m_shadow->ChangeRenderTarget(m_player->GetInformation()->GetPosition());

	//		�v���C���[�̕`�揈��
	//m_player->Render(m_shadow.get());

	//		�����_�[�^�[�Q�b�g�̕ύX
	//m_screenEffectManager->ChangeRenderTarget();

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̕ύX
	m_postEffectManager->Render();

	//		�I�u�W�F�N�g�}�l�[�W���[�̕`�揈��
	m_objectManager->Render(m_player->GetCameraInformation()->GetViewVelocity(),
							m_player->GetInformation()->GetPlayerHeight(),
							PostEffectFlag::Flag::Normal);

	//		���X�|�[���|�C���g�̃f�o�b�N�`��
	m_respawnManager->DebugRender();

	//		�v���C���[�̃��f���`��
	m_player->ModelRender();

	//		�G�l�~�[�}�l�[�W���[�̕`��
	m_enemyManager->Render();

	//		�f�o�b�N�`��
	m_player->DebugRender();

	//		�G�t�F�N�g�}�l�[�W���[�̕`��
	//m_effectManager->Render();

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃��X�g�`��
	//m_postEffectManager->RastRender();

	//		�����_�[�e�N�X�`���̕`��
	//m_postEffectManager->RenderTextureView();
	*/

	for (int i = 1; i <= PostEffectFlag::Flag::Fade;)
	{
		//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̕ύX
		m_postEffectManager->Render(PostEffectFlag::Flag(i));

		//		�I�u�W�F�N�g�}�l�[�W���[�̕`�揈��
		m_objectManager->Render(m_player->GetCameraInformation()->GetViewVelocity(),
			m_player->GetInformation()->GetPlayerHeight(),
			PostEffectFlag::Flag(i), m_postEffectManager->GetPostObjectShader());

		//		�v���C���[�̃��f���`��
		m_player->ModelRender(PostEffectFlag::Flag(i));

		//		�G�t�F�N�g�}�l�[�W���[�̕`��
		m_effectManager->Render(PostEffectFlag::Flag(i));

		if (PostEffectFlag::Flag(i) == PostEffectFlag::Flag::UI)
		{
			//		UI�}�l�[�W���[�̕`��
			m_uiManager->FrontRender();
		}

		if (PostEffectFlag::Flag(i) == PostEffectFlag::Flag::UIBack)
		{
			//		UI�}�l�[�W���[�̌�`��
			m_uiManager->BackRender();
		}

		//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃��X�g�`��
		m_postEffectManager->RastRender(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		�f�o�b�N�`��
	m_player->DebugRender();

	//		�����_�[�e�N�X�`�������Z�b�g����
	m_postEffectManager->ResetRenderTarget();

	//		�����_�[�e�N�X�`���̕`��
	m_postEffectManager->RenderTextureView();

	/*
	//		UI�}�l�[�W���[�̕`��
	//m_uiManager->FrontRender();

	//		�����_�[�^�[�Q�b�g����ɖ߂�
	//m_screenEffectManager->FirstRenderTarget();

	//		��ʃG�t�F�N�g�̕`��
	//m_screenEffectManager->Render();

	//		UI�}�l�[�W���[�̕`��
	//m_uiManager->BackRender();
	*/
}

void PlayScene::Finalize()
{
	m_objectManager->Finalize();

	m_effectManager->Finalize();

	m_gameManager->Finalize();

	m_uiManager->Finalize();

	m_player->Finalize();
}