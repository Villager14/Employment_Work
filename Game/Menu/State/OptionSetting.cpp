/*
* @file		OptionSetting.cpp
* @brief	オプションの設定
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "OptionSetting.h"

OptionSetting::OptionSetting(MenuManager* menuManager)
	:
	m_menuManager(menuManager),
	m_transitionTitleTime(0.0f),
	m_transitionSettingUITime(0.0f),
	m_startJudgement(true),
	m_endJudgement(false),
	m_menuCloseJudgement(false),
	m_transitionRoughTime(1.0f)
{
}

OptionSetting::~OptionSetting()
{
}

void OptionSetting::Initialize()
{
}

void OptionSetting::Update()
{
	//		メニューの遷移処理
	if (m_menuManager->Transition(&m_transitionTitleTime, &m_transitionSettingUITime,
		&m_transitionRoughTime, &m_startJudgement, m_endJudgement, m_menuCloseJudgement)) return;

	//		ESCでメニューをとじる処理
	if (m_menuManager->GetCommonProcess()->MenuEscCloseProcess())
	{
		//		メニューを閉じる状態にする
		m_endJudgement = true;
		m_menuCloseJudgement = true;
	}

	//		大まかなメニューボタンの処理
	if (m_menuManager->GetCommonProcess()->ButtonCollider(MenuInformation::MenuType::Option))
	{
		m_endJudgement = true;
	}

	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::FOVKnob);
	m_menuManager->GetCommonProcess()->SlideProcess(AboveUI::UIType::MouseKnob);

	//		視野角の更新
	m_menuManager->GetInformation()->SetViewAngle(Library::Lerp(FOV_MIN_VAL, FOV_MAX_VAL,
		m_menuManager->GetCommonProcess()->SliderVal(AboveUI::UIType::FOVKnob, Slider::UIType::FOV)));

	//		マウス感度の更新
	m_menuManager->GetInformation()->SetCameraSpeed(Library::Lerp(MOUSE_SENSITIVITY_MIN, MOUSE_SENSITIVITY_MAX,
		m_menuManager->GetCommonProcess()->SliderVal(AboveUI::UIType::MouseKnob, Slider::UIType::Mouse)));
}

void OptionSetting::Render()
{
	//		メニューの背景の描画
	m_menuManager->MenuBackRneder();

	//		Optionのタイトル描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::OptionTitle, m_menuManager->EasingIcon(m_transitionTitleTime));

	//		メニュー選択中の描画
	if (!m_menuCloseJudgement) m_menuManager->MenuSelectView();

	//		大まかなメニューの描画
	m_menuManager->RoughMenuViwe(m_menuManager->EasingIcon(m_transitionRoughTime));

	float transitionTime = m_menuManager->EasingIcon(m_transitionSettingUITime);

	//		スライダーの背景座標１
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = SLIDER_POSITION1;

	//		スライダー背景描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	//		FOVのテキスト描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::FOV, transitionTime);
	//		FOVのスライダー描画
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::FOV, transitionTime);
	//		スライダーのノブ描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::FOVKnob, transitionTime);

	//		スライダーの背景座標２
	(*m_menuManager->GetInformation()->GetAboveUI()->GetInformation())[AboveUI::UIType::SliderBack].position = SLIDER_POSITION2;
	//		スライダー背景描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::SliderBack, transitionTime);
	//		マウス感度テキスト描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::Mouse, transitionTime);
	//		マウス感度のスライダー描画
	m_menuManager->GetInformation()->GetSlider()->Render(Slider::Mouse, transitionTime);
	//		スライダーのノブ描画
	m_menuManager->GetInformation()->GetAboveUI()->Render(AboveUI::UIType::MouseKnob, transitionTime);

	//		マウスポインタの描画
	m_menuManager->GetCommonProcess()->MousePointa();
}

void OptionSetting::Finalize()
{
	m_transitionTitleTime = 0.0f;
	m_transitionSettingUITime = 0.0f;
	m_startJudgement = true;
	m_endJudgement = false;
	m_menuCloseJudgement = false;
	m_transitionRoughTime = 1.0f;
}
