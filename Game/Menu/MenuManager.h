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
#include "State/OptionSetting.h"
#include "State/EndSetting.h"
#include "State/MenuClose.h"


#include "MenuInformation.h"

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

	//		�l�p�̓����蔻��
	bool BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max);

public:
	enum MenuType
	{
		Start,
		Audio,
		Option,
		GamePlay,
		Close,

		Empty,
	};

private:

	//		���݂̃^�C�v
	MenuType m_type;

	//		���̏�Ԃ�ݒ肷��
	MenuType m_selectUI;

	//		���݂̏��
	IMenu* m_state;

	//		���j���[�̏�Ԃ̏��
	std::unordered_map<MenuType, std::unique_ptr<IMenu>> m_menuStateInformation;

	//		�I��UI
	AboveUI::UIType m_rangeUI;

	//		�X���C�_�[���g���Ă���UI�̎��
	AboveUI::UIType m_slideUIType;

	//		���j���[���J���Ă��邩�ǂ���
	bool *m_menuJudgement;

	//		���߂ĉ��y���j���[���J���Ă��邩�ǂ���
	bool m_firstAudioMenuJudgement;

	//		���j���[�̏��
	std::unique_ptr<MenuInformation> m_information;

public:

	/*
	*	���j���[�̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	MenuInformation* GetInformation() { return m_information.get(); }

	/*
	*	��܂��ȃ��j���[�̕`��
	* 
	*	@param	(transitionTime)	�J�ڎ���
	*/
	void RoughMenuViwe(float transitionTime);

	//		�I���������j���[�̕`��
	void MenuSelectView();

	/*
	*	��Ԃ̐؂�ւ�
	* 
	*	@param	(type)	���
	*/
	void ChangState(MenuType type);

	//		���j���[��ESC�{�^���ŕ��鏈��
	bool MenuEscCloseProcess();

	/*
	*	�I���������ǂ���
	* 
	*	@param	(type)	�I�����Ȃ����j���[�̎��
	*/
	bool ButtonCollider(MenuType type);

	/*
	*	UI�̑J�ڏ���
	* 
	*	@param	(transitionTime1)	�J�ڎ��ԂP
	*	@param	(transitionTime2)	�J�ڎ��ԂQ
	*	@param	(transitionTime3)	�J�ڎ��ԂR
	*	@param	(startJudgement)	�X�^�[�g���Ă��邩�ǂ������f����
	*	@param	(endJudgement)		�I��点�邩�ǂ������f����
	*	@param	(moveJudgement)		�J�ڎ��ԂR�𓮂��������f����
	*/
	bool Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3,
		bool *startJudgement, bool endJudgement, bool moveJudgement);

	/*
	*	�X���C�_�[�̏���
	* 
	*	@param	(type)	���
	*/
	void SlideProcess(AboveUI::UIType type);

	/*
	*	�C�[�W���O�֐��ʏ�UI�p
	* 
	*	@param	(time)	����
	*/
	float EasingIcon(float time) { return 1.0f - pow(1.0f - time, 3.0f); }

	/*
	*	�C�[�W���O�֐��w�i�p
	* 
	*	@param	(time) ����
	*/
	float EasingBackUI(float time) {
		if (time == 1.0f)
		{
			return 1.0f;
		}
		else
		{
			return 1.0f - pow(2.0f, -10.0f * time);
		}
	}

	/*
	*	���j���[���J���Ă��邩��ݒ肷��
	*	
	*	@param	true : �J���Ă��� false : �J���Ă��Ȃ�
	*/
	void SetMenuJudgement(bool* judgement) { m_menuJudgement = judgement; }

	/*
	*	���j���[���J���Ă��邩���󂯎��
	* 
	*	@param	true : �J���Ă��� false : �J���Ă��Ȃ�
	*/
	bool* GetMenuJudgement() { return m_menuJudgement; }

	/*
	*	Audio���j���[�����j���[���J��������x�����s���������󂯎��
	* 
	*	@retun	true : �s�� false : �s��Ȃ�
	*/
	bool GetFirstAudioMenuJudgement() { return m_firstAudioMenuJudgement; }

	/*
	*	Audio���j���[�����j���[���J��������x�����s��������ݒ肷��
	*
	*	@param	(judgement)	true : �s�� false : �s��Ȃ�
	*/
	void SetFirstAudioMenuJudgement(bool judgement) { m_firstAudioMenuJudgement = judgement; }
};