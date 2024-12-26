/*
* @file		MenuSliderProcess.h
* @brief	���j���[�̃X���C�_�[�̏���
* @author	Morita
* @date		2024/12/25
*/

#pragma once

#include "Effect/UI/Menu/Slider/Slider.h"

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "../../Collider/MenuColliderInformation.h"

#include "../../Observer/SliderSettingObserver/SetSliderSettingValObserver.h"

class MenuSliderProcess
{
public:

	MenuSliderProcess(Slider* slider, AboveUI* aboveUI);

	~MenuSliderProcess();

	void Initilaize();

	void Update();

	void Finalize();

	/*
	*	���������{�^��
	*
	*	@param	(type)	���������{�^���^�C�v
	*/
	void HitBunnton(UISubType type);

private:

	void SliserInformationUpdate();

	float SliderRatio();

	//		�I�[�f�B�I�̍X�V
	void AudioUpdate();

	//		�I�v�V�����̍X�V
	void OptionUpdate();

private:

	//		�m�u�̍ő�l
	const float KNOB_MAX_VAL = 561.0f;

	//		�m�u�̍ŏ��l
	const float KNOB_MIN_VAL = 81.0f;

	//		�X���C�_�[�̍ő�l
	const float SLIDER_MAX_VAL = 590.0f;

	//		�X���C�_�[�̍ŏ��l
	const float SLIDER_MIN_VAL = 95.0f;

private:

	//		�}�E�X�̍��WX
	int m_mousePositionX;

	//		�}�E�X�̓��͏������s���Ă��邩�ǂ���
	bool m_mouseInputJudgement;

	Slider* m_slider;

	AboveUI* m_aboveUI;

	//		�X���C�_�[����������
	AboveUI::UIType m_hitType;

	//		�X���C�_�[�^�C�v
	Slider::UIType m_sliderType;

	//		�ݒ�I�u�U�[�o�[
	std::unique_ptr<SetSliderSettingValObserver> m_settingObserver;

public:

	/*
	*	�}�E�X�̍��W��ݒ肷��
	*
	*	@param	(x) x���W
	*/
	void SetMousePosition(int x) { m_mousePositionX = x; }

	/*
	*	�}�E�X�̓��͏������s���Ă��Ȃ���
	*
	*	@param	(judgement)	true : �����Ă��� false : �����Ă��Ȃ�1
	*/
	void MouseInputJudgement(bool judgement) { m_mouseInputJudgement = judgement; }

	/*
	*	�X���C�_�[�̒l��ݒ�̑���I�u�U�[�o�[�̒ǉ�
	* 
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddSliderSettingValObserver(ISetSliderSettingValObserver* observer) { m_settingObserver->AddObserver(observer); }
};