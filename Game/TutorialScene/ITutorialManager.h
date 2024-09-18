/*
* @file		ITutorialManager.h
* @brief	�`���[�g���A���}�l�[�W���[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/09/17
*/

#pragma once

class ITutorialManager
{
public:

	//		����������
	virtual void Initialize() = 0;

	//		�X�V����
	virtual void Update() = 0;

	//		�`�揈��
	virtual void Render() = 0;

	//		�I������
	virtual void Finalize() = 0;

	//		�f�X�g���N�^
	virtual ~ITutorialManager() = default;
};