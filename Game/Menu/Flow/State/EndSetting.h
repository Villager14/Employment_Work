/*
* @file		EndSetting.h
* @brief	�I���ݒ�̐ݒ�
* @author	Morita
* @date		2024/07/10
*/
#pragma once

#include "../IMenu.h"

#include "../MenuFlow.h"

class EndSetting : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(menuFlow)	���j���[�̗���C���X�^���X�̃|�C���^
	*/
	EndSetting(MenuFlow* menuFlow);

	//		�f�X�g���N�^
	~EndSetting();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	//		�{�^���̏���
	void ButtonProcess();

private:

	//		���j���[����̃C���X�^���X�̃|�C���^
	MenuFlow* m_menuFlow;

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