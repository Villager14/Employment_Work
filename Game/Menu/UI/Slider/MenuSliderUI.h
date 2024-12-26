/*
* @file		MenuSliderUI.h
* @brief	���j���[�̃X���C�_�[UI
* @author	Morita
* @date		2024/12/20
*/

#pragma once

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "Effect/UI/Menu/Slider/Slider.h"

#include "../MenuUITabEnums.h"

#include "../../Collider/MenuColliderInformation.h"

class MenuSliderUI
{
public:

	//		�R���X�g���N�^
	MenuSliderUI(AboveUI* abvoceUI);

	//		�f�X�g���N�^
	~MenuSliderUI();

	//		����������
	void Initialize();
	
	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	//		�I�[�f�B�I�̕`��
	void AudioRender();

	//		�Q�[���v���C�̕`��
	void GamePlayRender();

	//		�I�v�V�����̕`��
	void OptionRender();

	/*
	*	�X���C�_�[�w�i�̕`��
	* 
	*	@param	(position)	���W
	*/
	void SliderBackGroundRender(DirectX::SimpleMath::Vector2 position);

	/*
	*	�X���C�_�[�̓����蔻����̒ǉ�
	* 
	*	@param	(position)	���W
	*	@param	(type)		UI�^�C�v
	*/
	void AddMenuColliderInformation(DirectX::SimpleMath::Vector2 position, UISubType type);

public:

	/*
	*	�X���C�_�[UI�̈ړ�
	*
	*	@param	(move)	�ړ���(0~1)
	*/
	void SliderMove(float move);

	std::vector<MenuColliderInformation>* GetMeshColliderInformation() { return &m_colliderInformation; }

private:

	//		�㏸UI
	AboveUI* m_abvoceUI;

	//		�ړ���
	float m_move;

	//		���j���[�̃^�C�v
	MenuUITaype::UIType m_type;

	//		�G�t�F�N�g�o�ߎ���
	float m_effectElapsedTime;

	//		�X���C�_�[UI
	std::unique_ptr<Slider> m_slider;

	//		�����蔻����
	std::vector<MenuColliderInformation> m_colliderInformation;

public:

	/*
	*	���j���[��ނ�ݒ肷��
	* 
	*	@param	(type)	UI�̎��
	*/
	void SetSliderType(MenuUITaype::UIType type);
};