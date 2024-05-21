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

	//		�v���C���[�J�����}�l�[�W���[�̐���
	m_playerCameraManager = std::make_unique<PlayerCameraManager>();

	//		�v���C���[�J�����}�l�[�W���[�̏���������
	m_playerCameraManager->Initialize();

	//		�v���C���[�̐���
	m_player = std::make_unique<Player>();

	//		�v���C���[�̏���������
	m_player->Initialize();

	//		�I�u�W�F�N�g�}�l�[�W���[�̐���
	m_objectManager = std::make_unique<ObjectManager>();

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
	m_uiManager = std::make_unique<UIManager>(m_player.get());

	//		UI�}�l�[�W���[�̏�����
	m_uiManager->Initialize();
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
	m_player->GetInformation()->SetViewVelocity(m_playerCameraManager->GetViewVelocity());

	//		�v���C���[�̍X�V����
	m_player->Update();

	//		�G�l�~�[�̍X�V����
	m_enemyManager->Update(m_player->GetInformation()->GetTimeSpeed(), m_player->GetInformation()->GetPosition());

	//		���b�V�����󂯎��
	m_collitionManager->SetObjectMesh(m_objectManager->GetMesh());

	//		�e�̍��W��ݒ肷��
	m_collitionManager->SetBulletPoistion(m_enemyManager->GetBulletPosition());

	//		�����蔻��̍X�V����
	m_collitionManager->Update(m_player->GetPlayerInformationCollition());

	//		�����蔻��̏��
	m_player->SetCollitionInformation(m_collitionManager->GetCollitionInformation());

	//		���b�V���A�b�v�f�[�g(��)
	m_player->MeshUpdate();

	//		�J�����}�l�[�W���[�̍X�V����
	m_playerCameraManager->Update(m_player->GetPlayerInformationCamera());

	//		�v���C���[�ɃJ�����̊p�x�𑗂�
	m_player->GetInformation()->SetCameraAngle(m_playerCameraManager->GetAngle());

	//		UI�}�l�[�W���[�̍X�V
	m_uiManager->Update();
}

void PlayScene::Render()
{
	//		�I�u�W�F�N�g�}�l�[�W���[�̕`�揈��
	m_objectManager->Render();

	//		�v���C���[�̕`�揈��
	m_player->Render();

	//		�G�l�~�[�̕`��
	m_enemyManager->Render();

	//		UI�}�l�[�W���[�̕`��
	m_uiManager->Render();
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
