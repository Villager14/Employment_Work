/*
* @file		MenuManager.h
* @brief	���j���[�̃}�l�[�W���[
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include <unordered_map>

#include "IMenu.h"

#include "State/AudioSetting.h"
#include "State/MenuStart.h"


#include "Game/PlayScene/UIManager/UIRender.h"

class MenuManager
{
public:
	//		�R���X�g���N�^
	MenuManager();

	//		�f�X�g���N�^
	~MenuManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();
	
	//		���j���[�̔w�i�̕`��
	void MenuBackRneder();

	//		�X���C�_�[�̕`��
	void SliderRender(DirectX::SimpleMath::Vector2 position);

public:

	enum MenuType
	{
		Start,
		Audio,

	};

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

	//		���݂̃^�C�v
	MenuType m_type;

	//		���݂̏��
	IMenu* m_state;

	//		���j���[�̏�Ԃ̏��
	std::unordered_map<MenuType, std::unique_ptr<IMenu>> m_menuStateInformation;

	//		UI�̕`��
	//std::vector<std::unique_ptr<UIRender>> m_uiRender;

	std::unordered_map<UIType, std::unique_ptr<UIRender>> m_uiRender;

public:

	/*
	*	��Ԃ̐؂�ւ�
	* 
	*	@param	(type)	���
	*/
	void ChangState(MenuType type);

	/*
	*	UIRneder�̐���
	*
	*	@param	(type)		UI�̎��
	*	@param	(path)		�t�@�C���p�X
	*	@param	(position)	���W
	*	@param	(size)		�T�C�Y
	*/
	void CreateUIRender(UIType type, const wchar_t* path, DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size);


	/*
	*	UI�̃C���X�^���X���󂯎��
	* 
	*	@return �C���X�^���X
	*/
	std::unordered_map<UIType, std::unique_ptr<UIRender>>* GetUIRender() { return &m_uiRender; }
};