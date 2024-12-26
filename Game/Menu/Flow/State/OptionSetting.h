/*
* @file		OptionSetting.h
* @brief	�I�v�V�����̐ݒ�
* @author	Morita
* @date		2024/07/10
*/

#pragma once

#include "../IMenu.h"

#include "../MenuFlow.h"

class OptionSetting : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(menuFlow)	���j���[�̗���C���X�^���X�̃|�C���^
	*/
	OptionSetting(MenuFlow* menuFlow);

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