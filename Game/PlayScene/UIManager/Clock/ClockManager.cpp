/*
* @file		ClockManager.h
* @brief	UI���v�̃}�l�[�W���[
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "ClockManager.h"

ClockManager::ClockManager()
	:
	m_elapsedTime(0.0f)
{
}

ClockManager::~ClockManager()
{
}

void ClockManager::Initialize()
{
	//		���v�̔w�i�̐���
	m_clockBackGround = std::make_unique<ClockBackGround>();

	//		���v�̔w�i�̏�����
	m_clockBackGround->Initialize();

	//		���v�̐����̐���
	m_clockTime = std::make_unique<ClockTime>();

	//		���v�̐����̏�����
	m_clockTime->Initialize();
}

void ClockManager::Update(GameManager* gameManager)
{
	if (gameManager->GetGameStartJudgement() && !gameManager->GetDeathJudgement() && !gameManager->GetGoalJudgement())
	{
		//		�o�ߎ���
		m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();
	}

	gameManager->SetTime(m_elapsedTime);

	//		�w�i�̍X�V
	m_clockBackGround->Update(m_elapsedTime);

	//		�����̍X�V
	m_clockTime->Update(m_elapsedTime);
}

void ClockManager::Render()
{
	//		�w�i�̍X�V
	m_clockBackGround->Render();

	//		�����̍X�V
	m_clockTime->Render();
}

void ClockManager::Finalize()
{
}
