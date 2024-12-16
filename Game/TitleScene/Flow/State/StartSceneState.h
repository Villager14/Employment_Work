/*
* @file		ChangeSceneState.h
* @brief	�V�[���؂�ւ����������
* @author	Morita
* @date		2024/05/27
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleFlowManager.h"

class StartSceneState : public ITitleSelect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleFlowManager)	�^�C�g������̃C���X�^���X�̃|�C���^
	*/
	StartSceneState(TitleFlowManager* titleFlowManager);

	//		�f�X�g���N�^
	~StartSceneState();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�I������
	void Finalize() override;

private:

	//		�^�C�g���̗���̃C���X�^���X�̃|�C���^
	TitleFlowManager* m_titleFlow;
};