
#pragma once

#include "Game/Menu/MenuInformation.h"

#include "../Observer/MenuUseObserver/ITitleMenuUseObserver.h"

class TitleMenuManagement : public ITitleMenuUseObserver
{
public:

	/*
	*	�^�C�g�����j���[�}�l�[�W���[
	* 
	*	@param	(information)	���j���[�̏��C���X�^���X�̃|�C���^
	*/
	TitleMenuManagement(MenuInformation* information);

	//		�f�X�g���N�^
	~TitleMenuManagement();

	/*
	*	���j���[���g���Ă��邩�ǂ���
	* 
	*	@return true : �g���Ă��� false : �g���Ă��Ȃ�
	*/
	bool MenuUseJudgement();

	//		���j���[���g�p����
	void OpenMenu() override;

	//		���j���[���g�p�ł���悤�ɂ���
	void EnableMenu() override;

	//		���j���[���g�p�ł��Ȃ��悤�ɂ���
	void DisableMenu() override;

private:

	//		���j���[���̃C���X�^���X�̃|�C���^
	MenuInformation* m_menuInformation;
};