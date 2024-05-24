/*
* @file		ClockManager.h
* @brief	UI���v�̃}�l�[�W���[
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "ClockBackGround.h"

#include "ClockTime.h"

#include "Game/PlayScene/GameManager/GameManager.h"

class ClockManager
{
public:

	//		�R���X�g���N�^
	ClockManager();

	//		�f�X�g���N�^
	~ClockManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(gameManager)	�Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	void Update(GameManager* gameManager);

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	//		���v�̔w�i
	std::unique_ptr<ClockBackGround> m_clockBackGround;

	//		���v�̐���
	std::unique_ptr<ClockTime> m_clockTime;

	//		�o�ߎ���
	float m_elapsedTime;
};