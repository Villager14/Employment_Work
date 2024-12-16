/*
* @file		ITitleCamera.h
* @brief	�^�C�g���J�����}�l�[�W���[
* @author	Morita
* @date		2024/12/15
*/

#pragma once

class ITitleCamera
{
public:

	//		�f�X�g���N�^
	virtual ~ITitleCamera() = default;

	//		����������
	virtual void Initialize() = 0;

	//		�J�����̍X�V
	virtual void Update() = 0;

	//		�I������
	virtual void Finalize() = 0;
};