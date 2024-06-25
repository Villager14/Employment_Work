/*
* @file		PlayerCameraManager.cpp
* @brief	�v���C���[�̃J�����̃}�l�[�W���[
* @author	Morita
* @date		2024/05/08
*/

#include "pch.h"

#include "PlayerCameraManager.h"

PlayerCameraManager::PlayerCameraManager(GameManager* gameManager)
	:
	m_state{},
	m_playerInformation{},
	m_gameManager(gameManager)
{
}

PlayerCameraManager::~PlayerCameraManager()
{
}

void PlayerCameraManager::Initialize()
{
	//		�J�����̏���
	m_information = std::make_unique<PlayerCameraInformation>();

	//		�f�o�b�N�J�����̐���
	m_debugCamera = std::make_unique<DebugCamera>(this);
	//		�v���C���[�J�����̐���
	m_playerCamera = std::make_unique<PlayerCamera>(this);
	//		�v���C���[�Ǒ���J�����̐���
	m_playerWallWalkCamera = std::make_unique<PlayerWallWalkCamera>(this);
	//		�v���C���[�̃X�^�[�g�J�����̐���
	m_playerStartCamera = std::make_unique<PlayerStartCamera>(this);
	//		�v���C���[�̎��S�J�����̐���
	m_playerDeathCamera = std::make_unique<PlayerDeathCamera>(this);
	//		�v���C���[�̓����Ȃ��J�����̐���
	m_playerStopCamera = std::make_unique<PlayerCameraStop>(this);

	//		�����J�����̑I��
	//m_state = m_playerCamera.get();
	m_state = m_playerStartCamera.get();

	//		����������
	m_state->Initialize();

	/*
	*	����p70�x
	*
	*	�߂�����0.1f
	* �@��������500.0f
	*/
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(m_information->GetViewingAngleMin()), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			0.1f, 360.0f);

	//		�v���W�F�N�V�����s���ݒ肷��
	LibrarySingleton::GetInstance()->SetProj(proj);

}

void PlayerCameraManager::Update(PlayerInformation* playerInformation)
{
	m_playerInformation = playerInformation;

	//		�J�����̍X�V����
	m_state->Update();

	ViewingAngle();
}

void PlayerCameraManager::Finalize()
{
}

void PlayerCameraManager::CameraMove()
{
	//		�}�E�X�̑��Έʒu����ړ��ʂ��o��
	float x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x);
	float y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y);

	DirectX::SimpleMath::Vector2 angle = m_information->GetAngle();

	//		�ړ���
	DirectX::SimpleMath::Vector2 move = DirectX::SimpleMath::Vector2::Zero;

	//		�J�����̈ړ��ʂ𑫂�
	move.x += x * m_information->GetCameraSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();
	move.y += -y * (m_information->GetCameraSpeed() / 2.0f) * LibrarySingleton::GetInstance()->GetElpsedTime();

	angle += move;

	//		���_�ړ��̐���
	angle.y = Library::Clamp(angle.y, m_information->GetCameraAngleMin(), m_information->GetMaxAngleY());
	
	m_information->SetAngle(angle);
	m_information->SetCameraMove(move);

}

void PlayerCameraManager::ChangeState(IPlayerCamera* state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I���������s��
	m_state->Finalize();

	//		�V������Ԃɂ���
	m_state = state;

	//		�V������Ԃ̏�����������
	m_state->Initialize();
}

void PlayerCameraManager::ViewingAngle()
{
	if (m_playerInformation->GetAcceleration().Length() > 30.0f)
	{
		float time = Library::Clamp(((m_playerInformation->GetAcceleration().Length() - 30.0f) / 60.0f), 0.0f, 1.0f);

		float move = time;

		float viewAnge = Library::Lerp(m_information->GetViewingAngleMin(), m_information->GetViewingAngleMax(), move);

		//		�r���[�s����쐬����
		DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
			CreatePerspectiveFieldOfView
			(DirectX::XMConvertToRadians(viewAnge), LibrarySingleton::GetInstance()->GetScreenSize().x /
				LibrarySingleton::GetInstance()->GetScreenSize().y,
				0.1f, 360.0f);

		//		�v���W�F�N�V�����s���ݒ肷��
		LibrarySingleton::GetInstance()->SetProj(proj);
	}
}
