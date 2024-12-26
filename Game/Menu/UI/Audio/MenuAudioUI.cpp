/*
* @file		MenuAudioUI.cpp
* @brief	メニューオーディオUIのタイトル
* @author	Morita
* @date		2024/12/25
*/

#include "pch.h"

#include "MenuAudioUI.h"

MenuAudioUI::MenuAudioUI(AboveUI* aboveUI,
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

MenuAudioUI::~MenuAudioUI()
{
}

void MenuAudioUI::Initialize()
{
	//		当たり判定の追加
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::BGMKnob].position, UISubType::BGMKnob);
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::SoundEffectKnob].position, UISubType::SoundEffectKnob);
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::MasterKnob].position, UISubType::MastarVolumKnob);

	m_colliderJudgement = true;
}

void MenuAudioUI::Update()
{
	//		タイトルが上がり切ったら当たり判定をオンにする
	if (m_titleMove >= 1.0f && m_colliderJudgement
		&& m_type == MenuUITaype::UIType::Audio)
	{
		//		当たり判定を追加
		m_summarizeColliderInformation->AddCollider(m_colliderInformation);

		//		フラグをオンにする
		m_colliderJudgement = false;
	}
	//		Audio以外の場合
	else if (m_type != MenuUITaype::UIType::Audio)
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

void MenuAudioUI::Render()
{
	//		ゲームプレイ以外の場合処理をしない
	if (m_type != MenuUITaype::UIType::Audio) {return;}

	//		タイトル
	m_aboveUI->Render(AboveUI::UIType::AudioTitle, m_titleMove);

	//		スライダーの背景
	SliderBackGroundRender(m_slider->MASTER_VOLUM_POSITION);
	SliderBackGroundRender(m_slider->BGM_VOLUM_POSITION);
	SliderBackGroundRender(m_slider->SOUND_EFFECT_POSITION);

	//		スライダーの名称
	m_aboveUI->Render(AboveUI::UIType::MastarVolume, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::BGMVolume, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::SoundEffectVolume, m_buttonMove);

	//		スライダーの描画
	m_slider->Render(Slider::BGMVolum, m_buttonMove);
	m_slider->Render(Slider::SoundEffect, m_buttonMove);
	m_slider->Render(Slider::MastarVolum, m_buttonMove);

	//		スライダーのノブ
	m_aboveUI->Render(AboveUI::UIType::MasterKnob, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::BGMKnob, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::SoundEffectKnob, m_buttonMove);
}

void MenuAudioUI::Finalize()
{
	m_colliderInformation.clear();
}

void MenuAudioUI::SetType(MenuUITaype::UIType type)
{
	m_type = type;
}

void MenuAudioUI::SliderBackGroundRender(DirectX::SimpleMath::Vector2 position)
{
	(*m_aboveUI->GetInformation())[AboveUI::UIType::SliderBack].position = position;
	m_aboveUI->Render(AboveUI::UIType::SliderBack, m_buttonMove);
}

void MenuAudioUI::TitleMoveProcess(float move)
{
	m_titleMove = move;
}

void MenuAudioUI::ButtonMoveProcess(float move)
{
	m_buttonMove = move;
}

void MenuAudioUI::AddMenuColliderInformation(DirectX::SimpleMath::Vector2* position, UISubType type)
{
	MenuColliderInformation information;

	information.position = position;
	information.subType = type;
	information.type = UIType::Knob;

	m_colliderInformation.push_back(information);
}
