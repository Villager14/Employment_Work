/*
* @file		TitleCameraManager.cpp
* @brief	�^�C�g���J�����}�l�[�W���[
* @author	Morita
* @date		2024/12/15
*/

#include "pch.h"

#include "TitleCameraManager.h"

#include "State/TitleCameraFrontCut.h"
#include "State/TitleCameraFrontAscendingCut.h"
#include "State/TitleCameraFrontOverHeadCut.h"
#include "State/TitleCameraBackCut.h"

TitleCameraManager::TitleCameraManager()
	:
	m_state(NULL),
	m_cameraType(CameraType::Non),
	m_fadeOutUseJudgement(false)
{
	m_fadeObserver = std::make_unique<FadeObserver>();

	m_cameraViewVelocityObserver = std::make_unique<CameraViewVelocityObserver>();
}

TitleCameraManager::~TitleCameraManager()
{
}

void TitleCameraManager::Initialize()
{
	//		�t�F�[�h���s���Ă��Ȃ�
	m_fadeOutUseJudgement = false;

	//		��Ԃ̒ǉ�
	m_cameraInformation.insert({CameraType::Front, std::make_unique<TitleCameraFrontCut>(this)});
	m_cameraInformation.insert({ CameraType::FrontAscending, std::make_unique<TitleCameraFrontAscendingCut>(this) });
	m_cameraInformation.insert({ CameraType::OverHead, std::make_unique<TitleCameraFrontOverHeadCut>(this) });
	m_cameraInformation.insert({ CameraType::Back, std::make_unique<TitleCameraBackCut>(this) });

	m_cameraType = CameraType::Front;

	m_state = m_cameraInformation[m_cameraType].get();

	m_state->Initialize();

	m_state->Update();

	CreateProj();
}

void TitleCameraManager::Update()
{
	m_state->Update();
}

void TitleCameraManager::Finalize()
{
	m_fadeObserver->Dalete();
}

void TitleCameraManager::CreateView(DirectX::SimpleMath::Vector3 position,
									DirectX::SimpleMath::Vector3 target)
{
	//		�A�b�v�x�N�g��
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		�r���[�s���ݒ肷��
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	(position, target, up));

	m_cameraViewVelocityObserver->CameraViewVelocity(target - position);
	m_cameraViewVelocityObserver->CameraUp(up);
	m_cameraViewVelocityObserver->CameraView(position);
}

void TitleCameraManager::CreateProj()
{
	//		�r���[�s����쐬����
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(60.0f), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			0.1f, 360.0f);

	//		�v���W�F�N�V�����s���ݒ肷��
	LibrarySingleton::GetInstance()->SetProj(proj);
}

void TitleCameraManager::ChangeState(CameraType changeState)
{
	//		�����V�[���̏ꍇ���������Ȃ�
	if (m_cameraType == changeState) return;

	//		�t�F�[�h���s���Ă��Ȃ���Ԃɂ���
	m_fadeOutUseJudgement = false;

	//		���݂̏�Ԃ̏I������������
	m_state->Finalize();

	//		��Ԃ�؂�ւ���
	m_cameraType = changeState;

	m_state = m_cameraInformation[m_cameraType].get();

	//		�V������Ԃ̏���������������
	m_state->Initialize();
}
