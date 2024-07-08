/*
* @file		BackGroundMove.h
* @brief	背景の移動
* @author	Morita
* @date		2024/05/24
*/

#include "pch.h"

#include "BackGroundMove.h"

BackGroundMove::BackGroundMove()
	:
	m_time(0.0f),
	m_fadeinResetJudgement(true),
	m_fadeoutResetJudgement(false)
{
}

BackGroundMove::~BackGroundMove()
{
}

void BackGroundMove::Initialize()
{
	//		UI描画の生成
	m_uiRenderManager = std::make_unique<UIRenderManager>();

	//		シェーダーの生成
	m_uiRenderManager->Create(L"Resources/Texture/TitleScene/TitleBack.png",
		L"Resources/Shader/BackGroundMove/BackGroundMoveVS.cso",
		L"Resources/Shader/BackGroundMove/BackGroundMoveGS.cso",
		L"Resources/Shader/BackGroundMove/BackGroundMovePS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

void BackGroundMove::Update()
{
	//		背景の移動時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.1f;
}

void BackGroundMove::Render()
{
	//		コンストバッファの値を設定する
	buffer.rotationMatrix = m_uiRenderManager->GetRotationMatrix();
	buffer.time = { m_time, 0.0f, 0.0f, 0.0f };

	//		背景の描画
	m_uiRenderManager->Render(buffer);
}

void BackGroundMove::Finalize()
{
}
