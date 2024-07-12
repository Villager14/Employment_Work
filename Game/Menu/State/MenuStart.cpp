/*
* @file		MenuStart.cpp
* @brief	メニュースタート時の処理
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuStart.h"

MenuStart::MenuStart(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
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
}

void MenuStart::Update()
{
	if (m_scale < 1.0f)
	{
		m_scale += LibrarySingleton::GetInstance()->GetElpsedTime() * m_menuManager->GetInformation()->MENU_SPEED;

		m_scale = Library::Clamp(m_scale, 0.0f, 1.0f);

		float transrationTime = m_menuManager->EasingBackUI(m_scale);

		//		バー１のスケール拡大
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar1].scale =
		{ transrationTime, 1.0f };

		//		バー２のスケール拡大
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar2].scale =
		{ transrationTime, 1.0f };
	}
	else
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime() * m_menuManager->GetInformation()->MENU_SPEED;

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float transrationTime = m_menuManager->EasingBackUI(m_move);

		//		バー１の移動
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar1].position =
		{ 0.0f, Library::Lerp(13.0f, 300.0f, transrationTime) };

		//		バー２の移動
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar2].position =
		{ 0.0f, Library::Lerp(-13.0f, -300.0f, transrationTime) };

		//		背景のスケール縮小
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::BackGround].scale =
		{ 1.0f, transrationTime };

	}

	if (m_move < 1.0f) return;

	//		メニューの遷移処理
	if (m_menuManager->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, false, true)) return;

	if (!m_startJudgement)
	{
		m_menuManager->ChangState(MenuManager::MenuType::Audio);
	}

}

void MenuStart::Render()
{
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
}

void MenuStart::Finalize()
{
}

void MenuStart::SliderView(float transitionTime)
{
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
}
