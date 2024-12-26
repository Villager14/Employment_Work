/*
* @file		EndSetting.cpp
* @brief	終了設定の設定
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "EndSetting.h"

#include "Scene/SceneManager.h"

#include "../MenuFlowCommonProcess.h"

EndSetting::EndSetting(MenuFlow* menuFlow)
	:
	m_menuFlow(menuFlow),
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
	m_transitionTitleTime = 0.0f;
	m_transitionSettingUITime = 0.0f;
	m_startJudgement = true;
	m_endJudgement = false;
	m_transitionRoughTime = 1.0f;
	m_menuCloseJudgement = false;

	//		オーディオを選択する
	m_menuFlow->GetSelectTypeObserver()->SelectType(MenuUITaype::GamePlay);
}

void EndSetting::Update()
{
	//		メニューの遷移処理
	if (m_menuFlow->GetMenuFlowCommonProcess()->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, m_endJudgement, m_menuCloseJudgement))
	{
		//		タイトルオブジェクトの移動処理
		m_menuFlow->GetTitleUIUObserver()->TitleMoveProcess(m_transitionSettingUITime);

		//		Tabオブジェクトの移動処理
		m_menuFlow->GetMenuTabUIObserver()->TabMove(m_transitionRoughTime);

		return;
	}

	//		TabUIを選択したときの処理
	if (m_menuFlow->TabProcess(MenuFlow::GamePlay))
	{
		m_endJudgement = true;
	}

	//		メニューを閉じるかどうか
	if (m_menuFlow->FlagJudgement(MenuFlow::K_MenuClose))
	{
		//		メニューを閉じる状態にする
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}

	//		Exitボタンを押した場合
	if (m_menuFlow->ButtonHitJudgement(UISubType::GameExitButton))
	{
		//		ゲームを閉じる
		//PostQuitMessage(0);
		//m_menuManager->GetSceneManager()->GetInformation()->SetEndJudgement(true);
	}

	//		MenuCloseボタンを押した場合
	if (m_menuFlow->ButtonHitJudgement(UISubType::CloseMenuButton))
	{
		//		メニューを閉じる状態にする
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}
	/*
	//		メニューの遷移処理
	if (m_menuManager->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, m_endJudgement, m_menuCloseJudgement)) return;

	//		大まかなメニューボタンの処理
	if (m_menuManager->GetCommonProcess()->ButtonCollider(MenuInformation::MenuType::GamePlay))
	{
		m_endJudgement = true;
	}

	//		ESCでメニューをとじる処理
	if (m_menuManager->GetCommonProcess()->MenuEscCloseProcess())
	{
		//		メニューを閉じる状態にする
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}

	//		ボタンの処理
	ButtonProcess();
	*/
}

void EndSetting::Render()
{
	/*
	m_menuManager->MenuBackRneder();

	//		Optionのタイトル描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::GamePlayTitle, m_menuManager->EasingIcon(m_transitionTitleTime));

	//		大まかなメニューの描画
	m_menuManager->RoughMenuViwe(m_menuManager->EasingIcon(m_transitionRoughTime));

	//		メニュー選択中の描画
	if (!m_menuCloseJudgement) m_menuManager->MenuSelectView();

	//		メニューを閉じる
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MenuClose, m_menuManager->EasingIcon(m_transitionSettingUITime));

	//		メニューを閉じるの枠
	m_menuManager->GetInformation()->GetFramWalkUI()->Render(m_menuManager->EasingIcon(m_transitionSettingUITime), FrameWalkUI::MenuClear);

	//		Exit
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::Exit, m_menuManager->EasingIcon(m_transitionSettingUITime));

	//		EXITの枠
	m_menuManager->GetInformation()->GetFramWalkUI()->Render(m_menuManager->EasingIcon(m_transitionSettingUITime), FrameWalkUI::EXIT);

	//		マウスポインタの描画
	m_menuManager->GetCommonProcess()->MousePointa();
	*/
}

void EndSetting::Finalize()
{
}

void EndSetting::ButtonProcess()
{
	/*
	//		メニューを閉じるかどうか
	if (m_menuManager->GetCommonProcess()->BoxCollider({ 640, 200.0f }, { 1039.0f, 317.0f }))
	{
		//		左クリック
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().PRESSED)
		{
			m_endJudgement = true;
			m_menuCloseJudgement = true;

			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);
		}

		//		当たっている
		(*m_menuManager->GetInformation()->GetFramWalkUI()->GetFrameInformation())
			[FrameWalkUI::FrameType::MenuClear].boxhitJudgement = true;

	}
	else
	{
		//		当たっている
		(*m_menuManager->GetInformation()->GetFramWalkUI()->GetFrameInformation())
			[FrameWalkUI::FrameType::MenuClear].boxhitJudgement = false;
	}

	//		ゲームを閉じるかどうか
	if (m_menuManager->GetCommonProcess()->BoxCollider({ 640.0f, 351.0f }, { 1039.0f, 470.0f }))
	{
		//		左クリック
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton
			== DirectX::Mouse::ButtonStateTracker().PRESSED)
		{
			//		ゲームを閉じる
			//PostQuitMessage(0);
			m_menuManager->GetSceneManager()->GetInformation()->SetEndJudgement(true);
		}

		//		当たっている
		(*m_menuManager->GetInformation()->GetFramWalkUI()->GetFrameInformation())
			[FrameWalkUI::FrameType::EXIT].boxhitJudgement = true;
	}
	else
	{
		//		当たっている
		(*m_menuManager->GetInformation()->GetFramWalkUI()->GetFrameInformation())
			[FrameWalkUI::FrameType::EXIT].boxhitJudgement = false;
	}
	*/
}
