/*
* @file		ScreenEffectManager.h
* @brief	�X�N���[���G�t�F�N�g�̃}�l�[�W���[
* @author	Morita
* @date		2024/05/22
*/

#pragma once

class ScreenEffectManager
{
public:

	//		�R���X�g���N�^
	ScreenEffectManager();

	//		�f�X�g���N�^
	~ScreenEffectManager();

	//		����������
	void Initialize();

	//		�A�b�v�f�[�g
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:



};
