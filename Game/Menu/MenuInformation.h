/*
* @file		MenuInformation.h
* @brief	���j���[�̏��
* @author	Morita
* @date		2024/07/12
*/

#pragma once

#include "pch.h"

#include "Library/Shader/StandardShader.h"
#include "UI/AboveUI.h"
#include "UI/Slider.h"
#include "UI/MenuSelect.h"

class MenuInformation
{
public:
	//		�R���X�g���N�^
	MenuInformation()
	{
		//		�X�^���_�[�h�V�F�[�_�[�̐���
		m_standardShader = std::make_unique<StandardShader<UIType>>();

		//		�㏸UI�̐���
		m_aboveUI = std::make_unique<AboveUI>();

		//		�X���C�_�[UI�̐���
		m_slider = std::make_unique<Slider>();

		//		���j���[�I��UI�̐���
		m_menuSelect = std::make_unique<MenuSelect>();
	}

	//		�f�X�g���N�^
	~MenuInformation() {}

	void Initialzie()
	{
		//		�X�^���_�[�h�V�F�[�_�[�̏���������
		m_standardShader->Initialize();

		m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png",
			{ 0.0f, 13.0f }, { 0.0f, 1.0f }, UIType::Bar1);
		m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png",
			{ 0.0f, -13.0f }, { 0.0f, 1.0f }, UIType::Bar2);
		m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBack.png",
			{ 0.0f, 0.0f }, { 0.0f, 1.0f }, UIType::BackGround);

		//		�㏸UI�̏�����
		m_aboveUI->Initialize();

		//		�X���C�_�[UI�̏�����
		m_slider->Initialize();

		//		���j���[�I��UI�̏�����
		m_menuSelect->Initialize();

	}
	


public:
	//		���y�^�C�g���̍��W
	const DirectX::SimpleMath::Vector2 AUDIO_TITLE_POSITION_MIN = { 119.0f, 106.0f };
	const DirectX::SimpleMath::Vector2 AUDIO_TITLE_POSITION_MAX = { 400.0f, 210.0f };

	//		�I�v�V�����^�C�g���̍��W
	const DirectX::SimpleMath::Vector2 OPTION_TITLE_POSITION_MIN = { 119.0f, 227.0f };
	const DirectX::SimpleMath::Vector2 OPTION_TITLE_POSITION_MAX = { 400.0f, 329.0f };

	//		�I���^�C�g���̍��W
	const DirectX::SimpleMath::Vector2 GAMEPLAY_TITLE_POSITION_MIN = { 119.0f, 347.0f };
	const DirectX::SimpleMath::Vector2 GAMEPLAY_TITLE_POSITION_MAX = { 400.0f, 452.0f };

	//		�J�ڑ��x
	const float TRANSITION_SPEED = 3.0f;

	//		���j���[�̑��x
	const float MENU_SPEED = 2.0f;

	//		�܂݂̑傫��
	const DirectX::SimpleMath::Vector2 KNOB_LENGTH = { 15.0f, 33.0f };

public:

	enum UIType
	{
		Bar1,
		Bar2,
		BackGround,
		AudioSelect,
		OptionSelect,
		GamePlaySelect,
		Slide,
		AudioTitle
	};

private:

	//		�X�^���_�[�h�V�F�[�_�[
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

	//		�㏸UI
	std::unique_ptr<AboveUI> m_aboveUI;

	//		�X���C�_�[UI
	std::unique_ptr<Slider> m_slider;

	//		���j���[�̑I��
	std::unique_ptr<MenuSelect> m_menuSelect;

public:

	/*
	*	�X�^���_�[�h�V�F�[�_�[���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader.get(); }

	/*
	*	�㏸UI���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	AboveUI* GetAboveUI() { return m_aboveUI.get(); }

	/*
	*	�X���C�_�[UI���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	Slider* GetSlider() { return m_slider.get(); }

	/*
	*	���j���[�I��UI���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	MenuSelect* GetMenuSelect() { return m_menuSelect.get(); }
};