/*
* @file		MenuTabUI.cpp
* @brief	ÉÅÉjÉÖÅ[ÇÃTabUI
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuTabUI.h"

MenuTabUI::MenuTabUI(AboveUI* abvoceUI,
	MenuSummarizeColliderInformation* summarizeColliderInformation)
	:
	m_abvoceUI(abvoceUI),
	m_move(0.0f),
	m_effectElapsedTime(0.0f),
	m_type(MenuUITaype::UIType::Empty),
	m_hitJudgement(false),
	m_summarizeColliderInformation(summarizeColliderInformation),
	m_colliderJudgement(true),
	m_useJudgement(false)
{
	m_menuSelect = std::make_unique<MenuSelect>();
}

MenuTabUI::~MenuTabUI()
{
}

void MenuTabUI::Initialize()
{
	m_colliderJudgement = true;

	m_colliderInformation.clear();

	

	AddMenuColliderInformation(&(*m_abvoceUI->GetInformation())[AboveUI::UIType::AudioSelect].position, UISubType::TabAudio);
	AddMenuColliderInformation(&(*m_abvoceUI->GetInformation())[AboveUI::UIType::OptionSelect].position, UISubType::TabOption);
	AddMenuColliderInformation(&(*m_abvoceUI->GetInformation())[AboveUI::UIType::GamePlaySelect].position, UISubType::TabGamePlay);

	m_menuSelect->Initialize();
}

void MenuTabUI::Update()
{
	if (m_useJudgement)
	{
		if (m_colliderJudgement)
		{
			//		ìñÇΩÇËîªíËÇÃí«â¡
			m_summarizeColliderInformation->AddCollider(m_colliderInformation);

			m_colliderJudgement = false;
		}
	}
	else
	{
		if (!m_colliderJudgement)
		{
			//		ìñÇΩÇËîªíËÇÃí«â¡
			m_summarizeColliderInformation->DeleteCollider(m_colliderInformation);

			m_colliderJudgement = false;
		}
	}

	if (m_hitJudgement)
	{
		m_menuSelect->Update();
	}
	else
	{
		m_menuSelect->TimeReset();
	}

	m_hitJudgement = false;
}

void MenuTabUI::Render()
{
	m_abvoceUI->Render(AboveUI::UIType::AudioSelect, m_move);
	m_abvoceUI->Render(AboveUI::UIType::OptionSelect, m_move);
	m_abvoceUI->Render(AboveUI::UIType::GamePlaySelect, m_move);

	if (m_hitJudgement)
	{
		DirectX::SimpleMath::Vector2 position;

		switch (m_type)
		{
		case MenuUITaype::Audio:
			position = m_abvoceUI->AUDIO_POSITION;
			break;
		case MenuUITaype::Option:
			position = m_abvoceUI->OPTION_POSITION;
			break;
		case MenuUITaype::GamePlay:
			position = m_abvoceUI->GAME_PLAY_POSITION;
			break;
		default:
			break;
		}

		m_menuSelect->Render(position);
	}
}

void MenuTabUI::Finalize()
{
	
}

void MenuTabUI::TabMove(float move)
{
	m_move = move;
}

void MenuTabUI::AddMenuColliderInformation(DirectX::SimpleMath::Vector2 *position, UISubType type)
{
	MenuColliderInformation information;

	information.position = position;
	information.subType = type;
	information.type = UIType::Tab;

	m_colliderInformation.push_back(information);
}
