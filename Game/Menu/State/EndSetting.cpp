/*
* @file		EndSetting.cpp
* @brief	終了設定の設定
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "EndSetting.h"

EndSetting::EndSetting(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
	m_transitionTitleTime(0.0f),
	m_transitionSettingUITime(0.0f),
	m_startJudgement(true),
	m_endJudgement(false),
	m_transitionRoughTime(1.0f),
	m_menuCloseJudgement(false)
{
}

EndSetting::~EndSetting()
{
}

void EndSetting::Initialize()
{
	m_menuCloseJudgement = false;
}

void EndSetting::Update()
{
	//		メニューの遷移処理
	if (m_menuManager->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, m_endJudgement, m_menuCloseJudgement)) return;

	//		大まかなメニューボタンの処理
	if (m_menuManager->ButtonCollider(MenuManager::MenuType::GamePlay))
	{
		m_endJudgement = true;
	}

	//		ESCでメニューをとじる処理
	if (m_menuManager->MenuEscCloseProcess())
	{
		//		メニューを閉じる状態にする
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}

	//		ボタンの処理
	ButtonProcess();

}

void EndSetting::Render()
{
	m_menuManager->MenuBackRneder();

	//		Optionのタイトル描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::GamePlayTitle, m_menuManager->EasingIcon(m_transitionTitleTime));

	//		大まかなメニューの描画
	m_menuManager->RoughMenuViwe(m_menuManager->EasingIcon(m_transitionRoughTime));

	//		メニュー選択中の描画
	if (!m_menuCloseJudgement) m_menuManager->MenuSelectView();

	//		メニューを閉じる
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MenuClose, m_menuManager->EasingIcon(m_transitionSettingUITime));

	//		Exit
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::Exit, m_menuManager->EasingIcon(m_transitionSettingUITime));

}

void EndSetting::Finalize()
{
	m_transitionTitleTime = 0.0f;
	m_transitionSettingUITime = 0.0f;
	m_startJudgement = true;
	m_endJudgement = false;
	m_transitionRoughTime = 1.0f;
	m_menuCloseJudgement = false;
}

void EndSetting::ButtonProcess()
{
	//		メニューを閉じるかどうか
	if (m_menuManager->BoxCollider({ 617.0f, 200.0f }, { 1064.0f, 317.0f }))
	{
		//		左クリック
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().PRESSED)
		{
			m_endJudgement = true;
			m_menuCloseJudgement = true;
		}
	}

	//		ゲームを閉じるかどうか
	if (m_menuManager->BoxCollider({ 617.0f, 351.0f }, { 1064.0f, 470.0f }))
	{
		//		左クリック
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().PRESSED)
		{
			//		ゲームを閉じる
			PostQuitMessage(0);
		}
	}
}
