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
}

AboveUI::~AboveUI()
{
}

void AboveUI::Initialize()
{
	//		シェーダーの作製
	CreateShader();

	//		回転行列を送る
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		ウィンドウサイズを送る
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

void AboveUI::CreateShader()
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(AUDIO_PATH,
		ABOVE_UI_VS_PATH, ABOVE_UI_GS_PATH, ABOVE_UI_PS_PATH,
		m_constBuffer,
		{ 0.0f, 0.0f , }, { 1.0f,1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		UIの情報を読み込む
	CreateUIInformation(AUDIO_PATH, AUDIO_POSITION, { 1.0f, 1.0f }, UIType::AudioSelect);
	CreateUIInformation(GAME_PLAY_PATH, GAME_PLAY_POSITION, { 1.0f, 1.0f }, UIType::GamePlaySelect);
	CreateUIInformation(OPTION_PATH, OPTION_POSITION, { 1.0f, 1.0f }, UIType::OptionSelect);
	CreateUIInformation(SLIDER_BACK_PATH, { 0.0f, 0.0f }, { 0.8f, 0.8f }, UIType::Slide);
	CreateUIInformation(AUDIO_SETTING_PATH, SETTING_TITLE_POSITION, { 0.8f, 0.8f }, UIType::AudioTitle);
	CreateUIInformation(OPTION_SETTING_PATH, SETTING_TITLE_POSITION, { 0.8f, 0.8f }, UIType::OptionTitle);
	CreateUIInformation(TITLE_GAME_PLAY_PATH, SETTING_TITLE_POSITION, { 0.8f, 0.8f }, UIType::GamePlayTitle);
	CreateUIInformation(SLIDER_BACK_PATH, SLIDE_BACK_POSITION, { 1.0f, 1.0f }, UIType::SliderBack);
	CreateUIInformation(MASTER_VLOUME_PATH, MASTER_VOLUME_POSITION, { 1.0f, 1.0f }, UIType::MastarVolume);
	CreateUIInformation(BGM_PATH, BGM_POSITION, { 1.0f, 1.0f }, UIType::BGMVolume);
	CreateUIInformation(SOUND_EFFECT_PATH, SOUND_EFFECT_POSITION, { 1.0f, 1.0f }, UIType::SoundEffectVolume);
	CreateUIInformation(KNOB_PATH, MASTER_K_NOB_POSITION, { 1.0f, 1.0f }, UIType::MasterKnob);
	CreateUIInformation(KNOB_PATH, { Library::Lerp(MIN_K_NOB, MAX_K_NOB,  MusicLibrary::GetInstance()->FIRST_BMG_VOLUME), BGM_K_NOB_Y_POSITION },
		{ 1.0f, 1.0f }, UIType::BGMKnob);
	CreateUIInformation(KNOB_PATH, { Library::Lerp(MIN_K_NOB, MAX_K_NOB,  MusicLibrary::GetInstance()->FIRST_SOUND_EFFECT_VOLUME), SOUND_K_NOB_Y_POSITION },
		{ 1.0f, 1.0f }, UIType::SoundEffectKnob);
	CreateUIInformation(CLOSE_MENU_PATH, SLIDE_BACK_POSITION, { 1.0f, 1.0f }, UIType::MenuClose);
	CreateUIInformation(EXIT_PATH, EXIT_POSITION, { 1.0f, 1.0f }, UIType::Exit);
	CreateUIInformation(FOV_PATH, FOV_POSITION, { 1.0f, 1.0f }, UIType::FOV);
	CreateUIInformation(KNOB_PATH, FOV_K_NOB_POSITION, { 1.0f, 1.0f }, UIType::FOVKnob);
	CreateUIInformation(MOUSE_POINTA_PATH, MOUSE_POSITION, { 1.0f, 1.0f }, UIType::Mouse);
	CreateUIInformation(KNOB_PATH, MOUSE_K_NOB_POSITION, { 1.0f, 1.0f }, UIType::MouseKnob);
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
