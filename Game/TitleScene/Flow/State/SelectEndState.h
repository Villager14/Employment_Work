/*
* @file		SelectEndState.h
* @brief	�I����I���������
* @author	Morita
* @date		2024/05/26
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleFlowManager.h"

class TitleFlowManager;

class SelectEndState : public ITitleSelect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleFlowManager)	�^�C�g������̃C���X�^���X�̃|�C���^
	*/
	SelectEndState(TitleFlowManager* titleFlowManager);

	//		�f�X�g���N�^
	~SelectEndState();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�I������
	void Finalize() override;

	//		�V�[����؂�ւ��鏈��
	void ChangeSceneProcess();

private:

	//		�^�C�g���̗���̃C���X�^���X�̃|�C���^
	TitleFlowManager* m_titleFlow;

};