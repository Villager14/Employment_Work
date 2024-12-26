/*
* @file		MenuGamePlayUI.h
* @brief	���j���[�Q�[���v���CUI�̃^�C�g��
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "../MenuUITabEnums.h"

#include "Effect/UI/Menu/FrameWalkUI/FrameWalkUI.h"

#include "../../Collider/MenuColliderInformation.h"

#include "../SummarizeColliderInformation/MenuSummarizeColliderInformation.h"

class MenuGamePlayUI
{
public:

	MenuGamePlayUI(AboveUI* aboveUI,
		MenuSummarizeColliderInformation* summarizeColliderInformation);

	~MenuGamePlayUI();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

	//		�^�C�v�̎擾
	void SetType(MenuUITaype::UIType type);

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
	void AddMenuColliderInformation(DirectX::SimpleMath::Vector2 *position, UISubType type);

	/*
	*	���������{�^��
	* 
	*	@param	(type)	���������{�^���^�C�v
	*/
	void HitBunnton(UISubType type);

private:

	AboveUI* m_aboveUI;

	MenuUITaype::UIType m_type;

	//		�ړ��ʃ^�C�g��
	float m_titleMove;

	//		�ړ��ʃ{�^��
	float m_buttonMove;

	//		�����蔻���ǉ����邩�ǂ���
	bool m_colliderJudgement;

	//		�����蔻����
	std::vector<MenuColliderInformation> m_colliderInformation;

	//		UI�̃t���[�����[�N
	std::unique_ptr<FrameWalkUI> m_frameWalkUI;

	//		�����蔻����܂Ƃ߂�1
	MenuSummarizeColliderInformation* m_summarizeColliderInformation;
public:

	//		���b�V���̓����蔻��
	std::vector<MenuColliderInformation>* GetMeshColliderInformation() { return &m_colliderInformation; }
};