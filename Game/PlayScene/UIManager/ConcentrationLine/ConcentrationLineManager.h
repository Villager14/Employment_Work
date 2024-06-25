/*
* @file		ConcentrationLineManager.h
* @brief	�W�����̃}�l�[�W���[
* @author	Morita
* @date		2024/06/17
*/

#pragma once

#include "../ConcentrationLineShader.h"

class ConcentrationLineManager
{
public:

	//		�R���X�g���N�^
	ConcentrationLineManager();

	//		�f�X�g���N�^
	~ConcentrationLineManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(gameManager)	�Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	//		�W�����V�F�[�_�[
	std::unique_ptr<ConcentrationLineShader> m_concentrationLineShader;

	//		�o�ߎ���
	float m_elapsedTime;

	//		�ړ���
	float m_move;

	//		�X�V����
	float m_updateTime;
};