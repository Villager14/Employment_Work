/*
* @file		MenuClose.h
* @brief	���j���[����鎞�̏���
* @author	Morita
* @date		2024/07/11
*/

#pragma once

#include "../IMenu.h"

#include "../MenuFlow.h"

class MenuClose : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(menuFlow)	���j���[�̗���C���X�^���X�̃|�C���^
	*/
	MenuClose(MenuFlow* menuFlow);

	//		�f�X�g���N�^
	~MenuClose();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

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

	float m_mainClose;
};