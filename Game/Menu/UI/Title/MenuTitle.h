/*
* @file		MenuTitle.h
* @brief	���j���[�̃^�C�g��
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "../MenuUITabEnums.h"

class MenuTitle
{
public:

	MenuTitle(AboveUI* aboveUI);

	~MenuTitle();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

	//		�^�C�g���̎擾
	void SetTitleType(MenuUITaype::UIType type);

	/*
	*	�^�C�g���̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	void TitleMoveProcess(float move);

private:

	AboveUI* m_aboveUI;

	MenuUITaype::UIType m_titleType;

	//		�ړ���
	float m_move;
};