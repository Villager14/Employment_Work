/*
* @file		TitleCameraFrontCut.cpp
* @brief	�^�C�g���J�����̃t�����g�J�b�g
* @author	Morita
* @date		2024/12/15
*/

#include "pch.h"

#include "TitleCameraFrontCut.h"

#include "../TitleCameraManager.h"

TitleCameraFrontCut::TitleCameraFrontCut(TitleCameraManager* titleCameraManager)
	:
	m_titleCameraManager(titleCameraManager),
	m_elapsedTime(0.0f)
{
}

TitleCameraFrontCut::~TitleCameraFrontCut()
{
}

void TitleCameraFrontCut::Initialize()
{
	m_elapsedTime = 0.0f;
}

void TitleCameraFrontCut::Update()
{
	//		�J�ڎ���
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	float radian = Library::Lerp(FIRST_RADIAN, END_RADIAN, m_elapsedTime);

	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::
		CreateRotationY(DirectX::XMConvertToRadians(radian));

	DirectX::SimpleMath::Vector3 eye = { 0.0f, 0.0f, 1.0f };

	eye = DirectX::SimpleMath::Vector3::Transform(eye, rotation.Invert());

	//		�����_����̋���
	eye *= (2.0f - 0.0f / 100.0f);

	eye += TARGET;

	//		�v���W�F�̍쐻
	m_titleCameraManager->CreateView(eye, TARGET);

	//		�t�F�[�h�A�E�g
	m_titleCameraManager->FadeOut(m_elapsedTime);

	if (m_elapsedTime >= 1.0f)
	{
		//		
		m_titleCameraManager->ChangeState(TitleCameraManager::FrontAscending);
	}
}

void TitleCameraFrontCut::Finalize()
{
	m_elapsedTime = 0.0f;
}
