/*
* @file		MenuStart.h
* @brief	���j���[�X�^�[�g���̏���
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include "../IMenu.h"

#include "../MenuFlow.h"

class MenuStart : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(menuFlow)	���j���[�̗���C���X�^���X�̃|�C���^
	*/
	MenuStart(MenuFlow* menuFlow);

	//		�f�X�g���N�^
	~MenuStart();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	//		�X���C�_�[�̕`��
	void SliderView(float transitionTime);

private:

	//		���j���[�̑��x
	const float MENU_SPEED = 2.0f;

private:

	//		���j���[����̃C���X�^���X�̃|�C���^
	MenuFlow* m_menuFlow;

	//		�X�P�[��
	float m_scale;

	//		�ړ�
	float m_move;


	//		�^�C�g���̑J�ڎ���
	float m_transitionTitleTime;

	//		��܂��ȃ��j���[�̑J�ڎ���
	float m_transitionRoughTime;

	//		�ݒ肷�镔����UI�̑J�ڎ���
	float m_transitionSettingUITime;

	//		�����J�ڂ��s�����ǂ������f����
	bool m_startJudgement;
};