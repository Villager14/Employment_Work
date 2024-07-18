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
#include "UI/FrameWalkUI.h"

class MenuInformation
{
public:
	//		�R���X�g���N�^
	MenuInformation() 
	:
		m_aboveUI{nullptr},
		m_standardShader{nullptr},
		m_menuSelect{nullptr},
		m_slider{nullptr},
		m_frameWalkUI{ nullptr },
		m_viewAngle(70.0f),
		m_cameraSpeed(5.0f),
		m_menuUseJudgement(false),
		m_menuJudgement(false),
		m_mouseModeChangeJdugement(true),
		m_menuTransitionJudgement(false)
	{}

	//		�f�X�g���N�^
	~MenuInformation() {}


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

public:

	/*
	*	������
	* 
	*	@param	(standardShader)	�X�^���_�[�h�V�F�[�_�[�̃C���X�^���X�̃|�C���^
	*	@param	(aboveUI)			�㏸�V�F�[�_�[�̃C���X�^���X�̃|�C���^
	*	@param	(slider)			�X���C�_�[�V�F�[�_�[�̃C���X�^���X�̃|�C���^
	*	@param	(menuSelect)		���j���[�I���V�F�[�_�[�̃C���X�^���X�̃|�C���^
	*	@param	(frameWalkUI)		�t���[�����[�N�V�F�[�_�[�̃C���X�^���X�̃|�C���^
	*/
	void Initialzie(StandardShader<MenuInformation::UIType>* standardShader,
		AboveUI* aboveUI,
		Slider* slider,
		MenuSelect* menuSelect, FrameWalkUI* frameWalk)
	{
		m_standardShader = standardShader;
		m_aboveUI = aboveUI;
		m_slider = slider;
		m_menuSelect = menuSelect;
		m_frameWalkUI = frameWalk;
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

private:

	//		�X�^���_�[�h�V�F�[�_�[
	StandardShader<UIType>* m_standardShader;

	//		�㏸UI
	AboveUI* m_aboveUI;

	//		�X���C�_�[UI
	Slider* m_slider;

	//		���j���[�̑I��
	MenuSelect* m_menuSelect;

	//		�t���[�����[�N
	FrameWalkUI* m_frameWalkUI;

	//		����p
	float m_viewAngle;

	//		�J�����̑��x
	float m_cameraSpeed;

	//		���j���[���g�p���邱�Ƃ��ł��邩
	bool m_menuUseJudgement;

	//		���j���[���g���Ă��邩
	bool m_menuJudgement;

	//		�}�E�X�̃��[�h��ύX���邩�ǂ���
	bool m_mouseModeChangeJdugement;

	//		���j���[���J�ڒ����ǂ���
	bool m_menuTransitionJudgement;

public:

	/*
	*	�X�^���_�[�h�V�F�[�_�[���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader; }

	/*
	*	�㏸UI���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	AboveUI* GetAboveUI() { return m_aboveUI; }

	/*
	*	�X���C�_�[UI���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	Slider* GetSlider() { return m_slider; }

	/*
	*	���j���[�I��UI���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	MenuSelect* GetMenuSelect() { return m_menuSelect; }

	/*
	*	�t���[�����[�NUI���󂯎��
	* 
	*	@return �t���[�����[�N�̃|�C���^
	*/
	FrameWalkUI* GetFramWalkUI() { return m_frameWalkUI; }

	/*
	*	����p��ݒ肷��
	* 
	*	@param	(angle)	�p�x
	*/
	void SetViewAngle(float angle) { m_viewAngle = angle; }

	/*
	*	����p���󂯎��
	* 
	*	@return �p�x
	*/
	float GetViewAngle() { return m_viewAngle; }

	/*
	*	�J�����̑��x��ݒ肷��
	* 
	*	@param	(speed)	���x
	*/
	void SetCameraSpeed(float speed) { m_cameraSpeed = speed; }

	/*
	*	�J�������x���󂯎��
	* 
	*	@retuen	���x
	*/
	float GetCameraSpeed() { return m_cameraSpeed; }

	/*
	*	���j���[���g���邩�ǂ������f����
	*
	*	@return true : �g���� false : �g���Ȃ�
	*/
	bool GetMenuUseJudgement() { return m_menuUseJudgement; }

	/*
	*	���j���[���g���邩�ǂ����ݒ肷��
	*
	*	@param	(judgement)	true : �g���� false : �g���Ȃ�
	*/
	void SetMenuUseJudgement(bool judgement) { m_menuUseJudgement = judgement; }

	/*
	*	���j���[���g���Ă��邩�ǂ����󂯎��
	* 
	*	@returen true : �g���Ă���@false �g���Ă��Ȃ�
	*/
	bool GetMenuJudgement() { return m_menuJudgement; }

	/*
	*	���j���[���g���Ă��邩�ǂ����ݒ肷��
	* 
	*	@param	(judgement)	true : �g���Ă���@false �g���Ă��Ȃ�
	*/
	void SetMenuJudgement(bool judgement) { m_menuJudgement = judgement; }

	/*
	*	�}�E�X�̃��[�h��ύX���邩�ǂ����󂯎��
	*
	*	@returen true : �ύX����@false �ύX���Ȃ�
	*/
	bool GetMouseModeJudgement() { return m_mouseModeChangeJdugement; }

	/*
	*	�}�E�X�̃��[�h��ύX���邩�ǂ����ݒ肷��
	*
	*	@param	(judgement)	true : �ύX����@false �ύX���Ȃ�
	*/
	void SetMouseModeJudgement(bool judgement) { m_mouseModeChangeJdugement = judgement; }

	/*
	*	���j���[�̑J�ڏ�Ԃ��ǂ����󂯎��
	*
	*	@returen true : �J�ڏ�ԊJ�n�@false �J�ڏ�ԏI��
	*/
	bool GetMenuTransrationJudgement() { return m_menuTransitionJudgement; }

	/*
	*	���j���[�̑J�ڏ�Ԃ��ǂ����ݒ肷��
	*
	*	@returen true : �J�ڏ�ԊJ�n�@false �J�ڏ�ԏI��
	*/
	void SetMenuTransrationJudgement(bool judgement) { m_menuTransitionJudgement = judgement; }

};