/*
* @file		ClockBackGround.cpp
* @brief	UI時計の背景
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "ClockBackGround.h"

ClockBackGround::ClockBackGround()
	:
	m_rotationMax(ROTATION_RADIAN),
	m_rotationMin(0.0f),
	m_pastTime(0.0f)
{
}

ClockBackGround::~ClockBackGround()
{
}

void ClockBackGround::Initialize()
{
	//		UI描画の生成
	m_uiRender = std::make_unique<UIRender>();

	//		UI描画の作製
	m_uiRender->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		{480.0f, 200.0f}, {0.8f, 0.8f});

	//		コロンの生成
	m_colonRender = std::make_unique<UIRender>();

	//		コロンの作製
	m_colonRender->Create(L"Resources/Texture/UI/Clock/ClockColon.png",
		{ 480.0f, 200.0f }, { 0.8f, 0.8f });
}

void ClockBackGround::Update(float elapsedTime)
{
	float time = elapsedTime;

	//		小数点のみを取得する
	int integer = static_cast<int>(elapsedTime);

	time -= static_cast<float>(integer);

	if (m_pastTime > time)
	{
		m_rotationMin += ROTATION_RADIAN;
		m_rotationMax += ROTATION_RADIAN;
	}

	float move = 0.0f;
	
	if (time == 0.0f)
	{
		move = 0.0f;
	}
	else
	{
		move = pow(2.0f, 10.0f * time - 10.0f);
	}
	
	float rotation = 0;

	rotation = Library::Lerp(m_rotationMin, m_rotationMax, move);

	m_pastTime = time;

	m_uiRender->SetRotationMatrix(DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rotation)));
}

void ClockBackGround::Render()
{
	//		背景の描画
	m_uiRender->Render();

	//		コロン描画
	m_colonRender->Render();
}

void ClockBackGround::Finalize()
{
}
