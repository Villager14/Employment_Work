/*
* @file		SelectPlayerState.h
* @brief	�v���C��I���������
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleFlowManager.h"

class TitleFlowManager;

class SelectPlayState : public ITitleSelect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleFlowManager)	�^�C�g������̃C���X�^���X�̃|�C���^
	*/
	SelectPlayState(TitleFlowManager* titleFlowManager);

	//		�f�X�g���N�^
	~SelectPlayState();

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