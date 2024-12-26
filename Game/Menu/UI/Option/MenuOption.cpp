/*
* @file		MenuOption.cpp
* @brief	メニューオプションUIのタイトル
* @author	Morita
* @date		2024/12/25
*/

#include "pch.h"

#include "MenuOption.h"

MenuOption::MenuOption(AboveUI* aboveUI,
	Slider* slider,
	MenuSummarizeColliderInformation* summarizeColliderInformation)
	:
	m_aboveUI(aboveUI),
	m_slider(slider),
	m_titleMove(0.0f),
	m_buttonMove(0.0f),
	m_colliderJudgement(false),
	m_type(MenuUITaype::UIType::Empty),
	m_summarizeColliderInformation(summarizeColliderInformation)
{
}

MenuOption::~MenuOption()
{
}

void MenuOption::Initialize()
{
	//		当たり判定の追加
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::MouseKnob].position, UISubType::MouseSpeedKnob);
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::FOVKnob].position, UISubType::FovKnob);

	m_colliderJudgement = true;
}

void MenuOption::Update()
{
	//		タイトルが上がり切ったら当たり判定をオンにする
	if (m_titleMove >= 1.0f && m_colliderJudgement
		&& m_type == MenuUITaype::UIType::Option)
	{
		//		当たり判定を追加
		m_summarizeColliderInformation->AddCollider(m_colliderInformation);

		//		フラグをオンにする
		m_colliderJudgement = false;
	}
	//		Option以外の場合
	else if (m_type != MenuUITaype::UIType::Option)
	{
		//		当たり判定がオフの場合
		if (!m_colliderJudgement)
		{
			//		当たり判定の削除
			m_summarizeColliderInformation->DeleteCollider(m_colliderInformation);

			//		フラグをオフにする
			m_colliderJudgement = true;
		}
	}
}

void MenuOption::Render()
{
	//		ゲームプレイ以外の場合処理をしない
	if (m_type != MenuUITaype::UIType::Option) {return;}

	//		タイトル
	m_aboveUI->Render(AboveUI::UIType::OptionTitle, m_titleMove);

	//		スライダーの背景
	SliderBackGroundRender(m_slider->FOV_POSITION);
	SliderBackGroundRender(m_slider->MOUSE_POSITION);

	//		スライダーの名称
	m_aboveUI->Render(AboveUI::UIType::FOV, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::Mouse, m_buttonMove);

	//		スライダーの描画
	m_slider->Render(Slider::Mouse, m_buttonMove);
	m_slider->Render(Slider::FOV, m_buttonMove);

	//		スライダーのノブ
	m_aboveUI->Render(AboveUI::UIType::FOVKnob, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::MouseKnob, m_buttonMove);
}

void MenuOption::Finalize()
{
	m_colliderInformation.clear();
}

void MenuOption::SetType(MenuUITaype::UIType type)
{
	m_type = type;
}

void MenuOption::SliderBackGroundRender(DirectX::SimpleMath::Vector2 position)
{
	(*m_aboveUI->GetInformation())[AboveUI::UIType::SliderBack].position = position;
	m_aboveUI->Render(AboveUI::UIType::SliderBack, m_buttonMove);
}

void MenuOption::TitleMoveProcess(float move)
{
	m_titleMove = move;
}

void MenuOption::ButtonMoveProcess(float move)
{
	m_buttonMove = move;
}

void MenuOption::AddMenuColliderInformation(DirectX::SimpleMath::Vector2* position, UISubType type)
{
	MenuColliderInformation information;

	information.position = position;
	information.subType = type;
	information.type = UIType::Knob;

	m_colliderInformation.push_back(information);
}
