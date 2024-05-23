/*
* @file		GameOverManager.cpp
* @brief	�Q�[���I�[�o�[�}�l�[�W���[
* @author	Morita
* @date		2024/05/23
*/

#include "pch.h"

#include "GameOverManager.h"


GameOverManager::GameOverManager(GameManager* gameManager)
	:
	m_gameManager(gameManager),
	m_elapsedTime(0.0f)
{
}

GameOverManager::~GameOverManager()
{
}

void GameOverManager::Initialize()
{
	for (int i = 0; i < 3; ++i)
	{
		//		UI�`��̐���
		m_gameOverRender.push_back(std::make_unique<UIRender>());
	}

	//		UI�`��̍쐻(GameOver)
	m_gameOverRender[0]->Create(L"Resources/Texture/UI/GameOver/GameOver.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		UI�`��̍쐻(Continue)
	m_gameOverRender[1]->Create(L"Resources/Texture/UI/GameOver/Continue.png",
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		UI�`��̍쐻(Continue)
	m_gameOverRender[2]->Create(L"Resources/Texture/UI/GameOver/button.png",
		{ 0.0f, 200.0f }, { 1.0f, 1.0f });
}

void GameOverManager::Update()
{
	//		�Q�[���I�[�o�[��Ԃł͂Ȃ��Ȃ珈�������Ȃ�
	if (!m_gameManager->GetDeathJudgement())
	{
		m_elapsedTime = 0.0f;

		return;
	}

	//		�o�ߎ���
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

}

void GameOverManager::Render()
{
	//		�Q�[���I�[�o�[��Ԃł͂Ȃ��Ȃ珈�������Ȃ�
	if (!m_gameManager->GetDeathJudgement()) return;
	
	if (m_elapsedTime < 3.0f)
	{
		m_gameOverRender[0]->Render();
	}
	else
	{
		m_gameOverRender[1]->Render();
		m_gameOverRender[2]->Render();
	}
}

void GameOverManager::Finalize()
{
}
