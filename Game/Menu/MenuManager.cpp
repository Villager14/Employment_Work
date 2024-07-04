/*
* @file		MenuManager.cpp
* @brief	���j���[�̃}�l�[�W���[
* @author	Morita
* @date		2024/07/03
*/

#include "pch.h"

#include "MenuManager.h"

MenuManager::MenuManager()
	:
	m_state()
{
}

MenuManager::~MenuManager()
{
}

void MenuManager::Initialize()
{
	//		��Ԃ̐���
	m_menuStateInformation.insert({ Start, std::make_unique<MenuStart>(this) });
	m_menuStateInformation.insert({ Audio, std::make_unique<AudioSetting>(this) });

	m_type = Start;

	//		�����̏��
	m_state = m_menuStateInformation[m_type].get();

	//		����������
	m_state->Initialize();

	//		�o�[�P
	CreateUIRender(Bar1, L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, 13.0f }, { 0.0f, 1.0f });

	//		�o�[�Q
	CreateUIRender(Bar2, L"Resources/Texture/UI/GameClear/messegeBer.png",
		{ 0.0f, -13.0f }, { 0.0f, 1.0f });

	//		�w�i
	CreateUIRender(BackGround, L"Resources/Texture/UI/GameClear/messegeBack.png",
		{ 0.0f, 0.0f }, { 1.0f, 0.0f });

	//		Audio�I��
	CreateUIRender(AudioSelect, L"Resources/Texture/Menu/Select/Audio.png",
		{ -380.0f, -200.0f }, { 1.0f, 1.0f });

	//		GamePlay�I��
	CreateUIRender(GamePlaySelect, L"Resources/Texture/Menu/Select/GamePlay.png",
		{ -380.0f, -80.0f }, { 1.0f, 1.0f });

	//		Opetion�I��
	CreateUIRender(OptionSelect, L"Resources/Texture/Menu/Select/Opetion.png",
		{ -380.0f, 40.0f }, { 1.0f, 1.0f });

	//		�X���C�_�[�I��
	CreateUIRender(Slide, L"Resources/Texture/Menu/Slide/SlideBack.png",
		{ 0.0f, 0.0f }, { 0.8f, 0.8f });

	//		Audio�^�C�g��
	CreateUIRender(AudioTitle, L"Resources/Texture/Menu/Title/AudioSetting.png",
		{ 200.0f, -240.0f }, { 1.0f, 1.0f });


	
}

void MenuManager::Update()
{
	//		�X�V����
	m_state->Update();
}

void MenuManager::Render()
{
	//		�`�揈��
	m_state->Render();
}

void MenuManager::Finalize()
{
}

void MenuManager::MenuBackRneder()
{
	m_uiRender[BackGround]->Render();
	m_uiRender[Bar1]->Render();
	m_uiRender[Bar2]->Render();
}

void MenuManager::SliderRender(DirectX::SimpleMath::Vector2 position)
{
	m_uiRender[Slide]->SetPosition(position);
	m_uiRender[Slide]->Render();
}

void MenuManager::ChangState(MenuType type)
{
	//		�����^�C�v�̏ꍇ���������Ȃ�
	if (m_type == type) return;

	//		�I������
	m_state->Finalize();

	//		�^�C�v�̍X�V
	m_type = type;

	//		��Ԃ̍X�V
	m_state = m_menuStateInformation[type].get();

	//		����������
	m_state->Initialize();
}

void MenuManager::CreateUIRender(UIType type, const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 size)
{
	//		UIRender�̐���
	std::unique_ptr<UIRender> uiRender = std::make_unique<UIRender>();

	//		UIRender�̍쐬
	uiRender->Create(path, position, size);

	//		UiRender�ɑ����
	m_uiRender.insert({type, move(uiRender)});
}
