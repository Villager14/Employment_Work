
#pragma once

#include "Game/Menu/MenuInformation.h"

#include "../Observer/MenuUseObserver/ITitleMenuUseObserver.h"

#include "Game/Observer/Menu/MenuUsedObserver/MenuUsedObserver.h"

#include "Game/Observer/Menu/MenuOpenObserver/MenuOpenObserver.h"

class TitleMenuManagement : public ITitleMenuUseObserver
{
public:

	/*
	*	�^�C�g�����j���[�}�l�[�W���[
	* 
	*	@param	(observer)�@�I�u�U�[�o�[
	*/
	TitleMenuManagement(MenuUsedObserver* observer,
						MenuOpenObserver* menuOpenObserver);

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

	//		���j���[���J���Ă��邩
	bool m_menuUseJudgement;

	//		���j���[���g�p����I�u�U�[�o�[
	MenuUsedObserver* m_menuUsedObserver;

	//		���j���[���J���I�u�U�[�o�[
	MenuOpenObserver* m_menuOpenObserver;
public:

	/*
	*	���j���[���g�p���Ă��邩�ݒ肷��
	* 
	*	@param	(judgement)	true : �g�p���Ă��� false : �g�p���Ă��Ȃ�
	*/
	void SetMenuUseJudgement(bool judgement) { m_menuUseJudgement = judgement; }

};