/*
* @file		AboveUI.h
* @brief	UIの上昇処理
* @author	Morita
* @date		2024/07/09
*/

#include "pch.h"

#include "AboveUI.h"

AboveUI::AboveUI()
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(L"Resources/Texture/Menu/Select/Audio.png",
		L"Resources/Shader/AboveUI/AboveUIVS.cso",
		L"Resources/Shader/AboveUI/AboveUIGS.cso",
		L"Resources/Shader/AboveUI/AboveUIPS.cso",
		m_constBuffer,
		{ 0.0f, 0.0f , }, { 1.0f,1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	CreateUIInformation(L"Resources/Texture/Menu/Select/Audio.png",
		{ -380.0f, -200.0f }, { 1.0f, 1.0f }, UIType::AudioSelect);
	CreateUIInformation(L"Resources/Texture/Menu/Select/GamePlay.png",
		{ -380.0f, 40.0f }, { 1.0f, 1.0f }, UIType::GamePlaySelect);
	CreateUIInformation(L"Resources/Texture/Menu/Select/Opetion.png",
		{ -380.0f, -80.0f }, { 1.0f, 1.0f }, UIType::OptionSelect);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/SlideBack.png",
		{ 0.0f, 0.0f }, { 0.8f, 0.8f }, UIType::Slide);
	CreateUIInformation(L"Resources/Texture/Menu/Title/AudioSetting.png",
		{ 200.0f, -240.0f }, { 0.8f, 0.8f }, UIType::AudioTitle);
	CreateUIInformation(L"Resources/Texture/Menu/Title/OptionSetting.png",
		{ 200.0f, -240.0f }, { 0.8f, 0.8f }, UIType::OptionTitle);
	CreateUIInformation(L"Resources/Texture/Menu/Title/GamePlay.png",
		{ 200.0f, -240.0f }, { 0.8f, 0.8f }, UIType::GamePlayTitle);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/SlideBack.png",
		{ 200.0f, -100.0f }, { 1.0f, 1.0f }, UIType::SliderBack);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/MasterVloume.png",
		{ 70.0f, -160.0f }, { 1.0f, 1.0f }, UIType::MastarVolume);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/BGM.png",
		{ 25.0f, -10.0f }, { 1.0f, 1.0f }, UIType::BGMVolume);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/SoundEffect.png",
		{ 150.0f, 140.0f }, { 1.0f, 1.0f }, UIType::SoundEffectVolume);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/Knob.png",
		{ 480.0f, -100.0f }, { 1.0f, 1.0f }, UIType::MasterKnob);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/Knob.png",
		{ Library::Lerp(-81.0f, 480.0f,  MusicLibrary::GetInstance()->FIRST_BMG_VOLUME), 50.0f},
		{1.0f, 1.0f}, UIType::BGMKnob);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/Knob.png",
		{ Library::Lerp(-81.0f, 480.0f,  MusicLibrary::GetInstance()->FIRST_SOUND_EFFECT_VOLUME), 200.0f },
		{ 1.0f, 1.0f }, UIType::SoundEffectKnob);
	CreateUIInformation(L"Resources/Texture/Menu/GamePlay/CloseMenu.png",
		{ 200.0f, -100.0f }, { 1.0f, 1.0f }, UIType::MenuClose);
	CreateUIInformation(L"Resources/Texture/Menu/GamePlay/Exit.png",
		{ 200.0f, 50.0f }, { 1.0f, 1.0f }, UIType::Exit);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/FOV.png",
		{ -70.0f, -160.0f }, { 1.0f, 1.0f }, UIType::FOV);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/Knob.png",
		{ -80.0f, -100.0f }, { 1.0f, 1.0f }, UIType::FOVKnob);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/mouseSe.png",
		{ 90.0f, -10.0f }, { 1.0f, 1.0f }, UIType::Mouse);
	CreateUIInformation(L"Resources/Texture/Menu/Slide/Knob.png",
		{ 200.0f, 50.0f }, { 1.0f, 1.0f }, UIType::MouseKnob);
}

AboveUI::~AboveUI()
{
}

void AboveUI::Initialize()
{
	//		回転行列を送る
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		ウィンドウサイズを送る
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

void AboveUI::CreateUIInformation(const wchar_t* path,
	DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 size, UIType type,
	CENTER_POINT centerPoint)
{
	UIInformation uiInformation;

	uiInformation.position = position;
	uiInformation.scale = size;
	m_shader->LoadTexture(path);
	uiInformation.texture = m_shader->GetTexture();
	uiInformation.textureSize = m_shader->GetTextureSize();
	uiInformation.time = 0.0f;
	uiInformation.centerPoint = centerPoint;

	m_shaderInformation.insert({ type, uiInformation });
}

void AboveUI::Render(UIType type, float time)
{
	if (type == UIType::Empty) return;

	m_shader->SetPosition(m_shaderInformation[type].position);
	m_shader->SetSize(m_shaderInformation[type].scale);
	m_shader->SetTexture(m_shaderInformation[type].texture);
	m_shader->SetTextureSize(static_cast<int>(m_shaderInformation[type].textureSize.x),
		static_cast<int>(m_shaderInformation[type].textureSize.y));
	m_shader->SetCenterPoint(m_shaderInformation[type].centerPoint);
	m_constBuffer.time = {time, 0.0f, 0.0f, 0.0f};

	m_shader->Render(m_constBuffer);
}
