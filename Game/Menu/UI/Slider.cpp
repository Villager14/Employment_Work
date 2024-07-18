/*
* @file		Slider.h
* @brief	スライダーの処理
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "Slider.h"

Slider::Slider()
{
}

Slider::~Slider()
{
}

void Slider::Initialize()
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(L"Resources/Texture/Menu/Slide/Slide.png",
		L"Resources/Shader/Slider/SliderVS.cso",
		L"Resources/Shader/Slider/SliderGS.cso",
		L"Resources/Shader/Slider/SliderPS.cso",
		m_constBuffer,
		{ 200.0f, -100.0f}, { 1.0f,1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	CreateUIInformation({ 200.0f, -100.0f }, { 1.0f, 1.0f }, 1.0f, UIType::MastarVolum);
	CreateUIInformation({ 200.0f, 50.0f }, { 1.0f, 1.0f }, 0.5f, UIType::BGMVolum);
	CreateUIInformation({ 200.0f, 200.0f }, { 1.0f, 1.0f }, 0.5f, UIType::SoundEffect);
	CreateUIInformation({ 200.0f, -100.0f }, { 1.0f, 1.0f }, 0.0f, UIType::FOV);
	CreateUIInformation({ 200.0f, 50.0f }, { 1.0f, 1.0f }, 0.5f, UIType::Mouse);

	//		回転行列を送る
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		ウィンドウサイズを送る
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

void Slider::CreateUIInformation(DirectX::SimpleMath::Vector2 position, 
	DirectX::SimpleMath::Vector2 size, float slideVal, UIType type)
{
	UIInformation uiInformation;

	uiInformation.position = position;
	uiInformation.scale = size;
	uiInformation.slideVal = slideVal;

	m_shaderInformation.insert({ type, uiInformation });
}

void Slider::Render(UIType type, float time)
{
	m_shader->SetPosition(m_shaderInformation[type].position);
	m_shader->SetSize(m_shaderInformation[type].scale);
	m_constBuffer.time = {time, 0.0f, 0.0f, 0.0f};
	m_constBuffer.slideVal = { m_shaderInformation[type].slideVal, 0.0f, 0.0f, 0.0f};

	m_shader->Render(m_constBuffer);
}
