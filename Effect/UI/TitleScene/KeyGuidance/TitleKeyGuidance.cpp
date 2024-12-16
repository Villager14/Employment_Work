/*
* @file		TitleKeyGuidance.cpp
* @brief	タイトルのキーガイド
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitleKeyGuidance.h"

TitleKeyGuidance::TitleKeyGuidance()
{
}

TitleKeyGuidance::~TitleKeyGuidance()
{
}

void TitleKeyGuidance::Initialize()
{
	//		中心UIをPlayにする
	m_centerUIType = CenterUIType::Play;

	//		UIの生成
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	m_standardShader->Initialize();

	//		Spaceの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/Space.png",
		SPACE_PLAY, { MAX_SCALE, MAX_SCALE },
		UIType::Space);

	//		Wの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/W.png",
		W_END, { MAX_SCALE, MAX_SCALE },
		UIType::W);

	//		Aの生成
	m_standardShader->CreateUIInformation(L"Resources/Texture/TitleScene/Select/A.png",
		A_SETTING, { MAX_SCALE, MAX_SCALE },
		UIType::A);
}

void TitleKeyGuidance::Render()
{
	//		スペースの描画
	m_standardShader->Render(UIType::Space);
}

void TitleKeyGuidance::Finalize()
{
	m_standardShader.reset();
}

void TitleKeyGuidance::UpSelect(float processingTime)
{
	DirectX::SimpleMath::Vector2 m_start;
	DirectX::SimpleMath::Vector2 m_end;

	CenterUIType type = CenterUIType::Not;

	if (m_centerUIType == CenterUIType::Play)
	{
		m_start = SPACE_PLAY;
		m_end = SPACE_SETTING;

		type = CenterUIType::Setting;
	}
	else if (m_centerUIType == CenterUIType::Setting)
	{
		m_start = SPACE_SETTING;
		m_end = SPACE_END;

		type = CenterUIType::End;
	}
	if (m_centerUIType == CenterUIType::End)
	{
		m_start = SPACE_END;
		m_end = SPACE_PLAY;

		type = CenterUIType::Play;
	}

	//		スペースの移動処理
	(*m_standardShader->GetUIInformation())[UIType::Space].position = 
		DirectX::SimpleMath::Vector2::Lerp(m_start, m_end,
			sqrt(1.0f - pow(processingTime - 1.0f, 2.0f)));

	//		時間が経過したら
	if (processingTime >= 1.0f)
	{
		//		中心のUIタイプを更新する
		m_centerUIType = type;
	}
}

void TitleKeyGuidance::DownSelect(float processingTime)
{
	DirectX::SimpleMath::Vector2 m_start;
	DirectX::SimpleMath::Vector2 m_end;

	CenterUIType type = CenterUIType::Not;

	if (m_centerUIType == CenterUIType::Play)
	{
		m_start = SPACE_PLAY;
		m_end = SPACE_END;

		type = CenterUIType::End;
	}
	else if (m_centerUIType == CenterUIType::Setting)
	{
		m_start = SPACE_SETTING;
		m_end = SPACE_PLAY;

		type = CenterUIType::Play;
	}
	if (m_centerUIType == CenterUIType::End)
	{
		m_start = SPACE_END;
		m_end = SPACE_SETTING;

		type = CenterUIType::Setting;
	}

	//		スペースの移動処理
	(*m_standardShader->GetUIInformation())[UIType::Space].position =
		DirectX::SimpleMath::Vector2::Lerp(m_start, m_end,
			sqrt(1.0f - pow(processingTime - 1.0f, 2.0f)));

	//		時間が経過したら
	if (processingTime >= 1.0f)
	{
		//		中心のUIタイプを更新する
		m_centerUIType = type;
	}
}
