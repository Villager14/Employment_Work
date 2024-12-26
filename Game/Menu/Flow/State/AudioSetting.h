/*
* @file		AudioSetting.h
* @brief	���̐ݒ�
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include "../IMenu.h"

#include "../MenuFlow.h"

class AudioSetting : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(menuFlow)	���j���[�̗���C���X�^���X�̃|�C���^
	*/
	AudioSetting(MenuFlow* menuFlow);

	//		�f�X�g���N�^
	~AudioSetting();

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

	//		�X���C�_�[�̍X�V����
	void SliderUpdate();

public:

	//			�}�X�^�[�{�����[���X���C�_�[�̍��W
	const DirectX::SimpleMath::Vector2 MASTER_SLIDER_POSITION = { 200.0f, -100.0f };

	//			BGM�{�����[���X���C�_�[�̍��W
	const DirectX::SimpleMath::Vector2 BGM_SLIDER_POSITION = { 200.0f, 50.0f };

	//			���ʉ��{�����[���X���C�_�[�̍��W
	const DirectX::SimpleMath::Vector2 SOUND_EFFECT_SLIDER_POSITION = { 200.0f, 200.0f };

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