/*
* @file		ScreenRay.cpp
* @brief	�Q�[���I�[�o�[�}�l�[�W���[
* @author	Morita
* @date		2024/05/23
*/

#include "pch.h"

#include "ScreenRay.h"


ScreenRay::ScreenRay(GameManager* gameManager)
	:
	m_gameManager(gameManager)
{
}

ScreenRay::~ScreenRay()
{
}

void ScreenRay::Initialize()
{
		//		UI�`��̐���
	m_screenRay = std::make_unique<UIRender>();

	//		UI�`��̍쐻(Continue)
	m_screenRay->Create(L"Resources/Texture/UI/ScreenRay/ScreenRay.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });
}

void ScreenRay::Update()
{
}

void ScreenRay::Render()
{	
	m_screenRay->Render();
}

void ScreenRay::Finalize()
{
}
