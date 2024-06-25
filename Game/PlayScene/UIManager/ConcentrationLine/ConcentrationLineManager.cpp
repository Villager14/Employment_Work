/*
* @file		ConcentrationLineManager.h
* @brief	�W�����̃}�l�[�W���[
* @author	Morita
* @date		2024/06/17
*/

#include "pch.h"

#include "ConcentrationLineManager.h"

ConcentrationLineManager::ConcentrationLineManager()
	:
	m_elapsedTime(0.0f),
	m_move(0.0f),
	m_updateTime(0.0f)
{
}

ConcentrationLineManager::~ConcentrationLineManager()
{
}

void ConcentrationLineManager::Initialize()
{
	//		�W�����V�F�[�_�[�̐���
	m_concentrationLineShader = std::make_unique<ConcentrationLineShader>();

	//		�W�����V�F�[�_�[�̍쐻
	m_concentrationLineShader->Create(
		L"Resources/Texture/UI/ConcentrationLine/ConcentrationLineTexture.png",
		{ 0.0f, 0.0f }, { LibrarySingleton::GetInstance()->GetScreenSize().x, 
		LibrarySingleton::GetInstance()->GetScreenSize().y});

	
}

void ConcentrationLineManager::Update()
{
	if (m_updateTime < 0.3f)
	{
		m_updateTime += LibrarySingleton::GetInstance()->GetElpsedTime();
	}

	m_updateTime = 0.0f;

	m_move = LibrarySingleton::GetInstance()->Random(0.0f, LibrarySingleton::GetInstance()->GetScreenSize().x);
}

void ConcentrationLineManager::Render()
{
	//		�W�����̕`��
	m_concentrationLineShader->Render(m_move);
}

void ConcentrationLineManager::Finalize()
{
}
