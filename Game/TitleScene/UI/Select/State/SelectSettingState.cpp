/*
* @file		SelectSettingState.cpp
* @brief	設定を選択した状態
* @author	Morita
* @date		2024/05/26
*/

#include "pch.h"

#include "SelectSettingState.h"

SelectSettingState::SelectSettingState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(0.0f)
{
}

SelectSettingState::~SelectSettingState()
{
}

void SelectSettingState::Initialize()
{
}

void SelectSettingState::Update()
{
	//		キー入力処理
	m_titleSelectManager->InputKey();
	
	//		UIの移動処理
	UIMove();

	//		シーン切り替え処理
	ChangeSceneProcess();

}

void SelectSettingState::Render()
{
}

void SelectSettingState::Finalize()
{
	m_titleSelectManager->SetKeyInput(false);
	m_time = 0.0f;
}

void SelectSettingState::UIMove()
{
	//		キー処理がなかった場合処理をしない
	if (!m_titleSelectManager->GetKeyInput()) return;

	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetMoveSpeed();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		上に移動
	if (m_titleSelectManager->GetDirection())
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Setting);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::End);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Play);
	}
	//		下に移動
	else
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Play);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Setting);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::End);
	}
}

void SelectSettingState::ChangeSceneProcess()
{
	//		時間が１以下の場合処理をしない
	if (m_time < 1.0f)
	{

	}
	else
	{

		if (m_titleSelectManager->GetDirection())
		{
			//		設定選択状態にする
			m_titleSelectManager->ChangeState(TitleSelectManager::State::EndState);
		}
		else
		{
			//		終了選択状態にする
			m_titleSelectManager->ChangeState(TitleSelectManager::State::PlayState);
		}
	}

}
