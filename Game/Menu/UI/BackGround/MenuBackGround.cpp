/*
* @file		MenuBackGround.h
* @brief	メニューの背景
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuBackGround.h"

MenuBackGround::MenuBackGround()
{
}

MenuBackGround::~MenuBackGround()
{
}

void MenuBackGround::Initialize()
{
	//		スタンダードシェーダーの生成
	m_standardShader = std::make_unique<StandardShader<UIType>>();

	//		スタンダードシェーダーの初期化処理
	m_standardShader->Initialize();

	m_standardShader->CreateUIInformation(MESSAGE_BACK_FILE_PATH,
		{ 0.0f, 0.0f }, { 0.0f, 1.0f }, UIType::BackGround);
	m_standardShader->CreateUIInformation(MESSAGE_BAR_FILE_PATH,
		MESSAGE_BAR1_CLOSE_POSITION, { 0.0f, 1.0f }, UIType::Bar1);
	m_standardShader->CreateUIInformation(MESSAGE_BAR_FILE_PATH,
		MESSAGE_BAR2_CLOSE_POSITION, { 0.0f, 1.0f }, UIType::Bar2);
}

void MenuBackGround::Update()
{
}

void MenuBackGround::Render()
{
	//		全てのUI描画処理
	for (int i = 0; i < static_cast<int>
		(m_standardShader->GetUIInformation()->size()); ++i)
	{
		m_standardShader->Render(UIType(i));
	}
}

void MenuBackGround::Finalize()
{
}

void MenuBackGround::BarScale(float scale)
{
	//		バー1のスケールの変更
	(*m_standardShader->GetUIInformation())[UIType::Bar1].scale = { scale, 1.0f };
	//		バー2のスケールの変更
	(*m_standardShader->GetUIInformation())[UIType::Bar2].scale = { scale, 1.0f };
}

void MenuBackGround::MenuMoveProcess(float move)
{
	//		バー１の移動
	(*m_standardShader->GetUIInformation())[UIType::Bar1].position =
		DirectX::SimpleMath::Vector2::Lerp
		(MESSAGE_BAR1_CLOSE_POSITION, MESSAGE_BAR1_OPEN_POSITION, move);

	//		バー２の移動
	(*m_standardShader->GetUIInformation())[UIType::Bar2].position =
		DirectX::SimpleMath::Vector2::Lerp
		(MESSAGE_BAR2_CLOSE_POSITION, MESSAGE_BAR2_OPEN_POSITION, move);

	//		背景のスケール変更
	(*m_standardShader->GetUIInformation())[UIType::BackGround].scale =
	{ 1.0f, Library::Lerp(0.0f, 1.0f, move) };
		
}
