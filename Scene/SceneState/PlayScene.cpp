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
	m_sceneManager{sceneManager}
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	CreateProjaction();

	//		�Q�[���}�l�[�W���[�𐶐�����
	m_gameManager = std::make_unique<GameManager>();

	//		�v���C���[�J�����}�l�[�W���[�̐���
	m_playerCameraManager = std::make_unique<PlayerCameraManager>(m_gameManager.get());

	//		�v���C���[�J�����}�l�[�W���[�̏���������
	m_playerCameraManager->Initialize();

	//		�v���C���[�̐���
	m_player = std::make_unique<Player>(m_gameManager.get());

	//		�v���C���[�̏���������
	m_player->Initialize();

	//		�e�̐���
	m_shadow = std::make_unique<Shadow>();

	//		�e�̏�����
	m_shadow->Initialize();

	//		�I�u�W�F�N�g�}�l�[�W���[�̐���
	m_objectManager = std::make_unique<ObjectManager>(m_shadow->GetInformation());

	//		�I�u�W�F�N�g�}�l�[�W���[�̏���������
	m_objectManager->Initialize();

	//		�����蔻��}�l�[�W���[�̐���
	m_collitionManager = std::make_unique<CollitionManager>();

	//		�����蔻��}�l�[�W���[�̏�����
	m_collitionManager->Initialize();

	//		�G�l�~�[�}�l�[�W���[�̐���
	m_enemyManager = std::make_unique<EnemyManager>();

	//		�G�l�~�[�}�l�[�W���[�̏�����
	m_enemyManager->Initialize();

	//		UI�}�l�[�W���[�̐���
	m_uiManager = std::make_unique<UIManager>(m_player->GetInformation(), m_gameManager.get());

	//		UI�}�l�[�W���[�̏�����
	m_uiManager->Initialize();

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[�̐���
	m_screenEffectManager = std::make_unique<ScreenEffectManager>(m_gameManager.get());

	//		�X�N���[���G�t�F�N�g�}�l�[�W���[�̏�����
	m_screenEffectManager->Initialize();

	//		�G�t�F�N�g�}�l�[�W���[�̍쐻
	m_effectManager = std::make_unique<EffectManager>(m_player->GetInformation());

	//		�G�t�F�N�g�}�l�[�W���[�̏�����
	m_effectManager->Initialize();
}

void PlayScene::Update()
{
	//		�v���C���[�̃��[���h���W���󂯎��
	m_objectManager->SetPlayerWorld(m_player->GetInformation()->GetWorld());

	//		�I�u�W�F�N�g�}�l�[�W���[�̍X�V����
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		�͈͓��ɂ��郏�C���[�̍��W���󂯎��
	m_player->GetInformation()->SetWirePosition(m_objectManager->GetWirePosition());

	//		�����x�N�g����ݒ肷��
	m_player->GetInformation()->SetViewVelocity(m_playerCameraManager->GetInformation()->GetViewVelocity());

	//		�v���C���[�̍X�V����
	m_player->Update(m_playerCameraManager->GetInformation());

	//		�G�l�~�[�̍X�V����
	//m_enemyManager->Update(m_player->GetInformation()->GetTimeSpeed(), m_player->GetInformation()->GetPosition());

	//		���b�V�����󂯎��
	m_collitionManager->SetObjectMesh(m_objectManager->GetMesh());

	//		�e�̍��W��ݒ肷��
	m_collitionManager->SetBulletPoistion(m_enemyManager->GetBulletPosition());

	//		�����蔻��̍X�V����
	m_collitionManager->Update(m_player->GetPlayerInformationCollition(), m_gameManager.get());

	//		�����蔻��̏��
	m_player->SetCollitionInformation(m_collitionManager->GetCollitionInformation());

	//		���b�V���A�b�v�f�[�g
	m_player->MeshUpdate();

	//		�J�����}�l�[�W���[�̍X�V����
	m_playerCameraManager->Update(m_player->GetInformation());

	//		�v���C���[�ɃJ�����̊p�x�𑗂�
	m_player->GetInformation()->SetCameraAngle(m_playerCameraManager->GetInformation()->GetAngle());

	//		�A�j���[�V�����̃A�b�v�f�[�g
	m_player->AnimationUpdate();

	//		UI�}�l�[�W���[�̍X�V
	m_uiManager->Update();

	//		�X�N���[���G�t�F�N�g�̍X�V����
	m_screenEffectManager->Update(m_playerCameraManager->GetInformation());

	//		�Q�[���}�l�[�W���[�̍X�V����
	m_gameManager->Update();

	//		���C���[�I�u�W�F�N�g�̍��W���󂯎��
	m_effectManager->SetWirePosition(m_objectManager->GetWirePosition());

	//		�G�t�F�N�g�}�l�[�W���[�̕`��
	m_effectManager->Update(m_playerCameraManager->GetInformation());

	//		���̃V�[���ɐ؂�ւ��邩�ǂ���
	if (m_gameManager->GetNextSceneJudgement())
	{
		//		�N���A�^�C�����󂯎��
		m_sceneManager->SetClearTime(static_cast<int>(m_gameManager->GetTime()));

		//		���S�񐔂��󂯎��
		m_sceneManager->SetDeathCount(static_cast<int>(m_gameManager->GetDeathCount()));

		//		���̃V�[���ɐ؂�ւ���i���U���g�V�[���j
		m_sceneManager->ChangeState(m_sceneManager->GetResultScene());
	}
}

void PlayScene::Render()
{
	//		�����_�[�^�[�Q�b�g�̕ύX
	m_shadow->ChangeRenderTarget(m_player->GetInformation()->GetPosition());

	//		�v���C���[�̕`�揈��
	m_player->Render(m_shadow.get());

	//		�����_�[�^�[�Q�b�g�̕ύX
	m_screenEffectManager->ChangeRenderTarget();

	//		�I�u�W�F�N�g�}�l�[�W���[�̕`�揈��
	m_objectManager->Render(m_player->GetCameraInformation()->GetViewVelocity(),
							m_player->GetInformation()->GetPlayerHeight());

	//		�v���C���[�̃��f���`��
	m_player->ModelRender();

	//		�G�l�~�[�̕`��
	//m_enemyManager->Render();

	//		�f�o�b�N�`��
	m_player->DebugRender();

	//		�G�t�F�N�g�}�l�[�W���[�̕`��
	m_effectManager->Render();

	//		UI�}�l�[�W���[�̕`��
	m_uiManager->FrontRender();

	//		�����_�[�^�[�Q�b�g����ɖ߂�
	m_screenEffectManager->FirstRenderTarget();

	//		��ʃG�t�F�N�g�̕`��
	m_screenEffectManager->Render();

	//		UI�}�l�[�W���[�̕`��
	m_uiManager->BackRender();
}

void PlayScene::Finalize()
{
	m_player.reset();
	m_objectManager.reset();
}

void PlayScene::CreateProjaction()
{
	/*
	*	����p90�x
	*		
	*	�߂�����0.1f
	* �@��������500.0f
	*/
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(70.0f), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			0.1f, 500.0f);

	//		�v���W�F�N�V�����s���ݒ肷��
	LibrarySingleton::GetInstance()->SetProj(proj);
}
