/*
* @file		MenuUI.h
* @brief	���j���[��UI
* @author	Morita
* @date		2024/12/18
*/

#pragma once

#include "Effect/UI/Menu/AboveUI/AboveUI.h"
#include "Effect/UI/Menu/Slider/Slider.h"

#include "../Collider/MenuColliderInformation.h"

#include "Tab/MenuTabUI.h"
#include "BackGround/MenuBackGround.h"
#include "MousePointer/MenuMousePointerUI.h"
#include "Title/MenuTitle.h"
#include "Slider/MenuSliderUI.h"
#include "GamePlay/MenuGamePlayUI.h"
#include "Audio/MenuAudioUI.h"
#include "Option/MenuOption.h"
#include "SummarizeColliderInformation/MenuSummarizeColliderInformation.h"

#include "../Observer/BackGroundUI/IMenuBackGroundUIObserver.h"
#include "../Observer/TabUI/IMenuTabUIObserver.h"
#include "../Observer/Mouse/IMenuMouseObserver.h"
#include "../Observer/SelectType/IMenuSelectTypeObserver.h"
#include "../Observer/Title/IMenuTitleUIObserver.h"
#include "../Observer/Icon/IMenuIconUIObserver.h"
#include "../Observer/Collider/IMenuColliderObserver.h"

#include "Library/Mouse/Observer/IMouseKeyInputObserver.h"

#include "Process/MenuSliderProcess.h"

class MenuUI : public IMenuBackGroundUIObserver,
			   public IMenuTabUIObserver,
			   public IMenuMouseObserver,
			   public IMenuSelectTypeObserver,
			   public IMenuTitleUIObserver,
			   public IMenuIconUIObserver,
			   public IMouseKeyInputObserver,
			   public IMenuColliderObserver
{
public:

	//		�R���X�g���N�^
	MenuUI();

	//		�f�X�g���N�^
	~MenuUI();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	/*
	*	�o�[�̃X�P�[���̕ύX
	*
	*	@param	(float scale)
	*/
	void BackGroundBarScale(float scale) override;

	/*
	*	���j���[�̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	void MenuMoveProcess(float move) override;

	/*
	*	�^�uUI�̈ړ�
	*
	*	@param	(move)	�ړ���(0~1)
	*/
	void TabMove(float move) override;

	/*
	*	�^�u���g�����ǂ���
	*
	*	@param	(bool) true : �g�� false : �g��Ȃ�
	*/
	void TabUseJudgement(float judgement) override;

	/*
	*	�}�E�X��X���W�̍X�V
	*
	*	@param	(x) x���W
	*/
	void MousePositionX(int x) override;

	/*
	*	�}�E�X��Y���W�̍X�V
	*
	*	@param	(y) y���W
	*/
	void MousePositionY(int y) override;

	/*
	*	�I���^�C�v
	*
	*	@param	(type)�@�^�C�v
	*/
	void SelectType(MenuUITaype::UIType type) override;

	/*
	*	�^�C�g���̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	void TitleMoveProcess(float move) override;

	/*
	*	�A�C�R���̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	void IconMoveProcess(float move) override;

	/*
	*	�}�E�X�̉������u�Ԃ̏���
	*
	*	@param	(key)	�������L�[
	*/
	void IsKeyPressed(KeyInputMouse::MouseList key) override;

	/*
	*	�}�E�X�̗������u�Ԃ̏���
	*
	*	@param	(key)	�������L�[
	*/
	void IsKeyReleased(KeyInputMouse::MouseList key) override;

	/*
	*	�}�E�X�̉����������̎��̏���
	*
	*	@param	(key)	�����������L�[
	*/
	void IsKeepPushing(KeyInputMouse::MouseList key) override;

	/*
	*	��������UI�̃^�C�v
	*
	*	@param	(type)	UI�̃^�C�v
	*/
	void HitUIType(UISubType type) override;

private:

	//		�㏸�X�N���v�g
	std::unique_ptr<AboveUI> m_aboveUI;

	//		���j���[TabUI
	std::unique_ptr<MenuTabUI> m_menuTabUI;

	//		���j���[�̔w�iUI
	std::unique_ptr<MenuBackGround> m_menuBackGround;

	//		�}�E�X�|�C���^UI
	std::unique_ptr<MenuMousePointerUI> m_mousePointer;

	//		�^�C�g��UI
	std::unique_ptr<MenuTitle> m_titleUI;

	//		�X���C�_�[
	std::unique_ptr<Slider> m_slider;

	//		�Q�[���v���C��ʂ�UI
	std::unique_ptr<MenuGamePlayUI> m_gamePlay;
	
	//		�I�[�f�B�I��ʂ�UI
	std::unique_ptr<MenuAudioUI> m_menuAudio;

	//		�I�v�V������ʂ�UI
	std::unique_ptr<MenuOption> m_menuOption;

	//		���j���[�̃X���C�_�[����
	std::unique_ptr<MenuSliderProcess> m_sliderProcess;

	//		�����蔻������܂Ƃ߂�
	std::unique_ptr<MenuSummarizeColliderInformation> m_summarizeColliderInformation;
public:

	/*
	*	�����蔻��̏��
	* 
	*	@return ���j���[�̓����蔻��̏��̃|�C���^
	*/
	const std::vector<MenuColliderInformation>& GetColliderInformation() { return m_summarizeColliderInformation->GetInformation(); }

	/*
	*	�X���C�_�[�̒l��ݒ�̑���I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddSliderSettingValObserver(ISetSliderSettingValObserver* observer) { m_sliderProcess->AddSliderSettingValObserver(observer); }
};