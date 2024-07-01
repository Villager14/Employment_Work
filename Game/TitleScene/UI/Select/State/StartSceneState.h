/*
* @file		ChangeSceneState.h
* @brief	�V�[���؂�ւ����������
* @author	Morita
* @date		2024/05/27
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleSelectManager.h"

class TitleSelectManager;

class StartSceneState : public ITitleSelect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleSelectManager)	�^�C�g���I���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	StartSceneState(TitleSelectManager* titleSelectManager);

	//		�f�X�g���N�^
	~StartSceneState();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:

	TitleSelectManager* m_titleSelectManager;

	float m_time;
};