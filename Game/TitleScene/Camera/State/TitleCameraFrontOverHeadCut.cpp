/*
* @file		TitleCameraFrontOverHeadCut.cpp
* @brief	�^�C�g���J�����̓���J�b�g
* @author	Morita
* @date		2024/12/15
*/

#include "pch.h"

#include "TitleCameraFrontOverHeadCut.h"

#include "../TitleCameraManager.h"

TitleCameraFrontOverHeadCut::TitleCameraFrontOverHeadCut(TitleCameraManager* titleCameraManager)
	:
	m_titleCameraManager(titleCameraManager),
	m_elapsedTime(0.0f)
{
}

TitleCameraFrontOverHeadCut::~TitleCameraFrontOverHeadCut()
{
}

void TitleCameraFrontOverHeadCut::Initialize()
{
	m_elapsedTime = 0.0f;
}

void TitleCameraFrontOverHeadCut::Update()
{
	//		�J�ڎ���
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;

	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Lerp(
								FIRST_POSITION, END_POSITION, m_elapsedTime);

	//		�v���W�F�̍쐻
	m_titleCameraManager->CreateView(position, TARGET);

	//		�t�F�[�h�A�E�g
	m_titleCameraManager->FadeOut(m_elapsedTime);

	if (m_elapsedTime >= 1.0f)
	{
		//		
		m_titleCameraManager->ChangeState(TitleCameraManager::Back);
	}
}

void TitleCameraFrontOverHeadCut::Finalize()
{
	m_elapsedTime = 0.0f;
}
