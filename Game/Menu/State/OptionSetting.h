/*
* @file		OptionSetting.h
* @brief	�I�v�V�����̐ݒ�
* @author	Morita
* @date		2024/07/10
*/

#pragma once

#include "../IMenu.h"

#include "../MenuManager.h"

class MenuManager;

class OptionSetting : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(menuManager)	�C���X�^���X�̃|�C���^
	*/
	OptionSetting(MenuManager* menuManager);

	//		�f�X�g���N�^
	~OptionSetting();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:
	//		�X���C�_�[�̍��W�P
	const DirectX::SimpleMath::Vector2 SLIDER_POSITION1 = { 200.0f, -100.0f };

	//		�X���C�_�[�̍��W�Q
	const DirectX::SimpleMath::Vector2 SLIDER_POSITION2 = { 200.0f, 50.0f };

	//		����p�̍ő�l
	const float FOV_MAX_VAL = 120.0f;

	//		����p�̍ŏ��l
	const float FOV_MIN_VAL = 70.0f;

	//		�}�E�X���x�ŏ��l
	const float MOUSE_SENSITIVITY_MIN = 0.1f;

	//		�}�E�X���x�ő�l
	const float MOUSE_SENSITIVITY_MAX = 10.0f;

private:

	//		���j���[�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	MenuManager* m_menuManager;

	//		�^�C�g���̑J�ڎ���
	float m_transitionTitleTime;

	//		��܂��ȃ��j���[�̑J�ڎ���
	float m_transitionRoughTime;

	//		�ݒ肷�镔����UI�̑J�ڎ���
	float m_transitionSettingUITime;

	//		�����J�ڂ��s�����ǂ������f����
	bool m_startJudgement;

	//		�I���J�ڂ��s�����ǂ������f����
	bool m_endJudgement;

	//		�߂邩�ǂ���
	bool m_menuCloseJudgement;

};