/*
* @file		SelectionBar.cpp
* @brief	選択バー
* @author	Morita
* @date		2024/12/12
*/
#include "pch.h"

#include "SelectionBar.h"

SelectionBar::SelectionBar()
{
	//		選択バー移動処理の生成
	m_selectionBarMoveProcess = std::make_unique<SelectionBarMoveProcess>(this);
}

SelectionBar::~SelectionBar()
{
}

void SelectionBar::Initialize()
{
	//		中心UIをPlayにする
	m_centerType = UIType::Play;

	//		UIの生成
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	//		スタンダードシェーダーの初期化処理
	m_standardShader->Initialize();

	//		Playの生成
	m_standardShader->CreateUIInformation(TITLE_PLAY_TEXTURE_PATH,
		CENTER_POINT, { MAX_SCALE, MAX_SCALE },
		UIType::Play);

	//		Endの生成
	m_standardShader->CreateUIInformation(TITLE_END_TEXTURE_PATH,
		UP_POINT, { MIN_SCALE, MIN_SCALE },
		UIType::End);

	//		Settingの生成
	m_standardShader->CreateUIInformation(TITLE_SETTING_TEXTURE_PATH,
		UNDER_POINT, { MIN_SCALE, MIN_SCALE },
		UIType::Setting);
}

void SelectionBar::Render()
{
	//		UIの描画
	for (int i = 0; i < m_standardShader->GetUIInformation()->size(); ++i)
	{
		m_standardShader->Render(UIType(i));
	}
}

void SelectionBar::Finalize()
{
	m_standardShader.reset();
}

void SelectionBar::UpSelect(float processingTime)
{
	int centerToTop = 0;
	int centerToBottom = 0;
	int fromTopToBottom = 0;

	if (m_centerType == UIType::Play)
	{
		centerToTop = UIType::Play;
		centerToBottom = UIType::Setting;
		fromTopToBottom = UIType::End;
	}
	else if (m_centerType == UIType::End)
	{
		centerToTop = UIType::End;
		centerToBottom = UIType::Play;
		fromTopToBottom = UIType::Setting;
	}
	else if (m_centerType == UIType::Setting)
	{
		centerToTop = UIType::Setting;
		centerToBottom = UIType::End;
		fromTopToBottom = UIType::Play;
	}

	//		上と中心の移動処理
	m_selectionBarMoveProcess->CenterToTopProcess(true, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(centerToTop)].position,
		&(*m_standardShader->GetUIInformation())[UIType(centerToTop)].scale);

	//		下と中心の移動処理
	m_selectionBarMoveProcess->CenterToBottom(true, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(centerToBottom)].position,
		&(*m_standardShader->GetUIInformation())[UIType(centerToBottom)].scale);

	//		上と下の移動処理
	m_selectionBarMoveProcess->FromTopToBottom(true, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(fromTopToBottom)].position,
		&(*m_standardShader->GetUIInformation())[UIType(fromTopToBottom)].scale);

	//		時間が経過したら
	if (processingTime >= 1.0f)
	{
		//		中心UIを変える
		m_centerType = UIType(centerToBottom);
	}
}

void SelectionBar::DownSelect(float processingTime)
{
	int centerToTop = 0;
	int centerToBottom = 0;
	int fromTopToBottom = 0;

	if (m_centerType == UIType::Play)
	{
		centerToTop = UIType::End;
		centerToBottom = UIType::Play;
		fromTopToBottom = UIType::Setting;
	}
	else if (m_centerType == UIType::End)
	{
		centerToTop = UIType::Setting;
		centerToBottom = UIType::End;
		fromTopToBottom = UIType::Play;
	}
	else if (m_centerType == UIType::Setting)
	{
		centerToTop = UIType::Play;
		centerToBottom = UIType::Setting;
		fromTopToBottom = UIType::End;
	}

	//		上と中心の移動処理
	m_selectionBarMoveProcess->CenterToTopProcess(false, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(centerToTop)].position,
		&(*m_standardShader->GetUIInformation())[UIType(centerToTop)].scale);

	//		下と中心の移動処理
	m_selectionBarMoveProcess->CenterToBottom(false, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(centerToBottom)].position,
		&(*m_standardShader->GetUIInformation())[UIType(centerToBottom)].scale);

	//		上と下の移動処理
	m_selectionBarMoveProcess->FromTopToBottom(false, processingTime,
		&(*m_standardShader->GetUIInformation())[UIType(fromTopToBottom)].position,
		&(*m_standardShader->GetUIInformation())[UIType(fromTopToBottom)].scale);

	//		時間が経過したら
	if (processingTime >= 1.0f)
	{
		//		中心UIを変える
		m_centerType = UIType(centerToTop);
	}
}
