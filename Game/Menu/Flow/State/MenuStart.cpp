/*
* @file		MenuStart.cpp
* @brief	メニュースタート時の処理
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuStart.h"

#include "../MenuFlowCommonProcess.h"

MenuStart::MenuStart(MenuFlow* menuFlow)
	:
	m_menuFlow(menuFlow),
	m_scale(0.0f),
	m_move(0.0f),
	m_transitionTitleTime(0.0f),
	m_transitionRoughTime(0.0f),
	m_transitionSettingUITime(0.0f),
	m_startJudgement(true)
{
}

MenuStart::~MenuStart()
{
}

void MenuStart::Initialize()
{
	m_scale = 0.0f;
	m_move = 0.0f;
	m_transitionTitleTime = 0.0f;
	m_transitionRoughTime = 0.0f;
	m_transitionSettingUITime = 0.0f;
	m_startJudgement = true;

	//		オーディオを選択する
	m_menuFlow->GetSelectTypeObserver()->SelectType(MenuUITaype::Audio);

	//m_menuManager->GetCommonProcess()->SliderVal(AboveUI::UIType::MasterKnob, Slider::UIType::MastarVolum);
	//m_menuManager->GetCommonProcess()->SliderVal(AboveUI::UIType::BGMKnob, Slider::UIType::BGMVolum);
	//m_menuManager->GetCommonProcess()->SliderVal(AboveUI::UIType::SoundEffectKnob, Slider::UIType::SoundEffect);
}

void MenuStart::Update()
{
	
	//m_menuManager->GetInformation()->SetMenuTransrationJudgement(true);

	if (m_scale < 1.0f)
	{
		m_scale += LibrarySingleton::GetInstance()->GetElpsedTime() * MENU_SPEED;

		m_scale = Library::Clamp(m_scale, 0.0f, 1.0f);

		float transrationTime = m_menuFlow->EasingBackUI(m_scale);

		//		背景のバーのスケールの変更
		m_menuFlow->GetMenuBackGroundUIObserver()->BarScale(transrationTime);
	}
	else
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime() * MENU_SPEED;

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float transrationTime = m_menuFlow->EasingBackUI(m_move);

		//		背景の移動処理
		m_menuFlow->GetMenuBackGroundUIObserver()->MenuMoveProcess(transrationTime);
	}

	if (m_move < 1.0f) return;

	//		メニューの遷移処理
	if (m_menuFlow->GetMenuFlowCommonProcess()->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, false, true))
	{
		//		Tabオブジェクトの移動処理
		m_menuFlow->GetMenuTabUIObserver()->TabMove(m_transitionRoughTime);

		//		タイトルオブジェクトの移動処理
		m_menuFlow->GetTitleUIUObserver()->TitleMoveProcess(m_transitionSettingUITime);

		return;
	}

	if (!m_startJudgement)
	{
		m_menuFlow->ChangState(MenuFlow::MenuType::Audio);
	}
	
}

void MenuStart::Render()
{
	/*
	//		メニューの背景の描画
	m_menuManager->MenuBackRneder();

	//		Audioのタイトル描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::AudioTitle, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionTitleTime)));

	//		Audioの描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::AudioSelect, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionRoughTime)));

	//		Opetionの描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::OptionSelect, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionRoughTime)));

	//		GamePlayの描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::GamePlaySelect, m_menuManager->EasingIcon(m_menuManager->EasingIcon(m_transitionRoughTime)));

	//		スライダーの描画
	SliderView(m_menuManager->EasingIcon(m_transitionSettingUITime));
	*/
}

void MenuStart::Finalize()
{
	//		TabUIを使用できるようにする
	m_menuFlow->GetMenuTabUIObserver()->TabUseJudgement(true);
}

void MenuStart::SliderView(float transitionTime)
{
	/*
	//		マスターボリュームの描画
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, -100.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MastarVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::MastarVolum, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MasterKnob, transitionTime);

	//		BGMボリュームの描画
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, 50.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::BGMVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::BGMVolum, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::BGMKnob, transitionTime);

	//		効果音の描画
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = { 200.0f, 200.0f };
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SoundEffectVolume, transitionTime);
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::SoundEffect, transitionTime);
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SoundEffectKnob, transitionTime);
	*/
}
