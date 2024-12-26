/*
* @file		MenuStandby.h
* @brief	���j���[�ҋ@��Ԃ̏���
* @author	Morita
* @date		2024/12/24
*/

#pragma once

#include "../IMenu.h"

#include "../MenuFlow.h"

class MenuStandby : public IMenu
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(menuFlow)	���j���[�̗���C���X�^���X�̃|�C���^
	*/
	MenuStandby(MenuFlow* menuFlow);

	//		�f�X�g���N�^
	~MenuStandby();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:

	//		���j���[����̃C���X�^���X�̃|�C���^
	MenuFlow* m_menuFlow;
};