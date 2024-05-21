/*
* @file		CoolTime.h
* @brief	クールタイム
* @author	Morita
* @date		2024/05/20
*/
#include "pch.h"

#include "CoolTime.h"

CoolTime::CoolTime()
	:
	m_angle(0.0f),
	m_time(0.0f)
{
}

CoolTime::~CoolTime()
{
}

void CoolTime::Initialize()
{
	//		数字シェーダーの生成
	m_circleShader = std::make_unique<CircleShader>();

	//		数字シェーダーの作製
	m_circleShader->Create(L"Resources/Texture/UI/CoolTime/CoolTime.png",
		{0.0f, 0.0f}, {1.0f, 1.0f});
}

void CoolTime::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	m_angle = Library::Lerp(360.0f, 0.0f, (cosf(m_time) + 1.0f) / 2.0f);
}

void CoolTime::Render()
{
	m_angle = 0.0f;

	m_circleShader->Render(m_angle);
}

void CoolTime::Finalize()
{
}
