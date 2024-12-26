/*
* @file		MenuOption.h
* @brief	���j���[�I�v�V����UI�̃^�C�g��
* @author	Morita
* @date		2024/12/25
*/

#pragma once

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "../MenuUITabEnums.h"

#include "../../Collider/MenuColliderInformation.h"

#include "../SummarizeColliderInformation/MenuSummarizeColliderInformation.h"

#include "Effect/UI/Menu/Slider/Slider.h"

class MenuOption
{
public:

	MenuOption(AboveUI* aboveUI,
		Slider* slider,
		MenuSummarizeColliderInformation* summarizeColliderInformation);

	~MenuOption();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

	//		�^�C�v�̎擾
	void SetType(MenuUITaype::UIType type);

	/*
	*	�X���C�_�[�w�i�̕`��
	*
	*	@param	(position)	���W
	*/
	void SliderBackGroundRender(DirectX::SimpleMath::Vector2 position);

	/*
	*	�^�C�g���̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	void TitleMoveProcess(float move);
	
	/*
	*	�{�^���̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	void ButtonMoveProcess(float move);

	/*
	*	�X���C�_�[�̓����蔻����̒ǉ�
	*
	*	@param	(position)	���W
	*	@param	(type)		UI�^�C�v
	*/
	void AddMenuColliderInformation(DirectX::SimpleMath::Vector2* position, UISubType type);

private:

	AboveUI* m_aboveUI;

	MenuUITaype::UIType m_type;

	//		�ړ��ʃ^�C�g��
	float m_titleMove;

	//		�ړ��ʃ{�^��
	float m_buttonMove;

	//		�����蔻����s�����ǂ���
	bool m_colliderJudgement;

	//		�X���C�_�[
	Slider* m_slider;

	//		�����蔻����
	std::vector<MenuColliderInformation> m_colliderInformation;

	//		�����蔻����܂Ƃ߂�1
	MenuSummarizeColliderInformation* m_summarizeColliderInformation;
public:

	//		���b�V���̓����蔻��
	std::vector<MenuColliderInformation>* GetMeshColliderInformation() { return &m_colliderInformation; }
};