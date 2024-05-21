/*
* @file		ClockTime.h
* @brief	UI時計の数字
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "ClockTime.h"

ClockTime::ClockTime()
{
}

ClockTime::~ClockTime()
{
}

void ClockTime::Initialize()
{
	//		数字シェーダーの生成
	m_numberShader = std::make_unique<NumberShader>();

	//		数字シェーダーの作製
	m_numberShader->Create(L"Resources/Texture/UI/Clock/ClockNumber.png",
		{1050.0f, 560.0f}, {1.0f, 1.0f});
}

void ClockTime::Update(float elapsedTime)
{
	m_time = static_cast<float>(elapsedTime);

	if (m_time > 5999)
	{
		m_time = 5999;
	}
}

void ClockTime::Render()
{
	//		十分単位
	m_numberShader->SetPosition({1050.0f, 560.0f});
	m_numberShader->Render(m_time / 60 / 10);

	//		分単位
	m_numberShader->SetPosition({1090.0f, 560.0f});
	m_numberShader->Render(m_time / 60 % 10);

	//		十秒
	m_numberShader->SetPosition({ 1150.0f, 560.0f });
	m_numberShader->Render(m_time % 60 / 10);

	//		秒
	m_numberShader->SetPosition({ 1190.0f, 560.0f });
	m_numberShader->Render(m_time % 60 % 10);
}

void ClockTime::Finalize()
{
}
