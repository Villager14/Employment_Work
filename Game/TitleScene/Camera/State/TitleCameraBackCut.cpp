/*
* @file		TitleCameraBackCut.cpp
* @brief	�^�C�g���J�����̔w�i�J�b�g
* @author	Morita
* @date		2024/12/15
*/

#include "pch.h"

#include "TitleCameraBackCut.h"

#include "../TitleCameraManager.h"

TitleCameraBackCut::TitleCameraBackCut(TitleCameraManager* titleCameraManager)
	:
	m_titleCameraManager(titleCameraManager),
	m_elapsedTime(0.0f)
{
}

TitleCameraBackCut::~TitleCameraBackCut()
{
}

void TitleCameraBackCut::Initialize()
{
	m_elapsedTime = 0.0f;
}

void TitleCameraBackCut::Update()
{
	//		�J�ڎ���
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	float radian = Library::Lerp(FIRST_RADIAN, END_RADIAN, m_elapsedTime);

	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Lerp(
		FIRST_TARGET, END_TARGET, m_elapsedTime);


	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::
		CreateRotationY(DirectX::XMConvertToRadians(radian));

	DirectX::SimpleMath::Vector3 eye = { 0.0f, 0.0f, 1.0f };

	eye = DirectX::SimpleMath::Vector3::Transform(eye, rotation.Invert());

	//		�����_����̋���
	eye *= (2.0f - 0.0f / 100.0f);

	eye += target;

	//		�v���W�F�̍쐻
	m_titleCameraManager->CreateView(eye, target);

	//		�t�F�[�h�A�E�g
	m_titleCameraManager->FadeOut(m_elapsedTime);

	if (m_elapsedTime >= 1.0f)
	{
		//		�O���J�b�g�J�����ɕύX
		m_titleCameraManager->ChangeState(TitleCameraManager::Front);
	}
}

void TitleCameraBackCut::Finalize()
{
	m_elapsedTime = 0.0f;
}
