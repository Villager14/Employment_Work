/*
* @file		ClockTime.h
* @brief	UI時計の数字
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "ClockTime.h"

ClockTime::ClockTime()
	:
	m_time(0)
{
}

ClockTime::~ClockTime()
{
}

void ClockTime::Initialize()
{
	//		シェーダー描画マネージャーの生成
	m_shader = std::make_unique<UIRenderManager>();

	//		数字シェーダーの作製
	m_shader->Create(L"Resources/Texture/UI/Clock/ClockNumber.png",
		L"Resources/Shader/Number/NumberVS.cso",
		L"Resources/Shader/Number/NumberGS.cso",
		L"Resources/Shader/Number/NumberPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 0.8f, 0.8f });

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	buffer.rotationMatrix = m_shader->GetRotationMatrix();
}

void ClockTime::Update(float elapsedTime)
{
	m_time = static_cast<int>(elapsedTime);

	//		最大時間
	if (m_time > MAX_TIME)
	{
		m_time = MAX_TIME;
	}
}

void ClockTime::Render()
{
	//		十分単位
	m_shader->SetPosition(TEN_PLACE_MINUTES_POSITION);
	buffer.number = { static_cast<float>(m_time / 60 / 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_shader->Render(buffer);

	//		分単位
	m_shader->SetPosition(ONE_PLACE_MINUTES_POSITION);
	buffer.number = { static_cast<float>(m_time / 60 % 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_shader->Render(buffer);

	//		十秒
	m_shader->SetPosition(TEN_PLACE_SECONDS_POSITION);
	buffer.number = { static_cast<float>(m_time % 60 / 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_shader->Render(buffer);

	//		秒
	m_shader->SetPosition(ONE_PLACE_SECONDS_POSITION);
	buffer.number = { static_cast<float>(m_time % 60 % 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_shader->Render(buffer);
}

void ClockTime::Finalize()
{
}
