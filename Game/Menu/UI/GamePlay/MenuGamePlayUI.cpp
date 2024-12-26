/*
* @file		MenuGamePlayUI.cpp
* @brief	メニューゲームプレイUIのタイトル
* @author	Morita
* @date		2024/12/23
*/

#include "pch.h"

#include "MenuGamePlayUI.h"

MenuGamePlayUI::MenuGamePlayUI(AboveUI* aboveUI,
	MenuSummarizeColliderInformation* summarizeColliderInformation)
	:
	m_aboveUI(aboveUI),
	m_titleMove(0.0f),
	m_summarizeColliderInformation(summarizeColliderInformation),
	m_colliderJudgement(false)
{
	//		フレームワークUIの生成
	m_frameWalkUI = std::make_unique<FrameWalkUI>();
}

MenuGamePlayUI::~MenuGamePlayUI()
{
}

void MenuGamePlayUI::Initialize()
{
	m_colliderJudgement = false;

	m_frameWalkUI->Initialize();

	//		当たり判定の追加
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::MenuClose].position, UISubType::CloseMenuButton);
	AddMenuColliderInformation(&(*m_aboveUI->GetInformation())[AboveUI::UIType::Exit].position, UISubType::GameExitButton);
}

void MenuGamePlayUI::Update()
{
	m_frameWalkUI->Update(FrameWalkUI::FrameType::EXIT);
	m_frameWalkUI->Update(FrameWalkUI::FrameType::MenuClear);

	if (m_type == MenuUITaype::UIType::GamePlay)
	{
		//		当たり判定フラグをオフにする
		for (auto& e : (*m_frameWalkUI->GetFrameInformation()))
		{
			e.second.boxhitJudgement = false;
		}
	}

	//		タイトルが上がり切ったら当たり判定をオンにする
	if (m_titleMove >= 1.0f && m_colliderJudgement
		&& m_type == MenuUITaype::UIType::GamePlay)
	{
		//		当たり判定を追加
		m_summarizeColliderInformation->AddCollider(m_colliderInformation);

		//		フラグをオンにする
		m_colliderJudgement = false;
	}
	//		GamePlay以外の場合
	else if (m_type != MenuUITaype::UIType::GamePlay)
	{
		//		当たり判定がオフの場合
		if (!m_colliderJudgement)
		{
			//		当たり判定の削除
			m_summarizeColliderInformation->DeleteCollider(m_colliderInformation);

			//		フラグをオフにする
			m_colliderJudgement = true;

			//		当たり判定フラグをオフにする
			for (auto& e : (*m_frameWalkUI->GetFrameInformation()))
			{
				e.second.boxhitJudgement = false;
			}
		}
	}
}

void MenuGamePlayUI::Render()
{
	//		ゲームプレイ以外の場合処理をしない
	if (m_type != MenuUITaype::UIType::GamePlay) {return;}

	//		タイトル
	m_aboveUI->Render(AboveUI::UIType::GamePlayTitle, m_titleMove);

	//		ボタン
	m_aboveUI->Render(AboveUI::UIType::MenuClose, m_buttonMove);
	m_aboveUI->Render(AboveUI::UIType::Exit, m_buttonMove);

	m_frameWalkUI->Render(m_buttonMove, FrameWalkUI::FrameType::EXIT);
	m_frameWalkUI->Render(m_buttonMove, FrameWalkUI::FrameType::MenuClear);
}

void MenuGamePlayUI::Finalize()
{
	m_colliderInformation.clear();
}

void MenuGamePlayUI::SetType(MenuUITaype::UIType type)
{
	m_type = type;
}

void MenuGamePlayUI::TitleMoveProcess(float move)
{
	m_titleMove = move;
}

void MenuGamePlayUI::ButtonMoveProcess(float move)
{
	m_buttonMove = move;
}

void MenuGamePlayUI::AddMenuColliderInformation(DirectX::SimpleMath::Vector2* position, UISubType type)
{
	MenuColliderInformation information;

	information.position = position;
	information.subType = type;
	information.type = UIType::Button;

	m_colliderInformation.push_back(information);
}

void MenuGamePlayUI::HitBunnton(UISubType type)
{
	if (type == UISubType::GameExitButton)
	{
		(*m_frameWalkUI->GetFrameInformation())[FrameWalkUI::FrameType::EXIT].boxhitJudgement = true;
	}
	else if (type == UISubType::CloseMenuButton)
	{
		(*m_frameWalkUI->GetFrameInformation())[FrameWalkUI::FrameType::MenuClear].boxhitJudgement = true;
	}
}
