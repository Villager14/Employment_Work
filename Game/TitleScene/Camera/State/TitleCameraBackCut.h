/*
* @file		TitleCameraBackCut.cpp
* @brief	�^�C�g���J�����̔w�i�J�b�g
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "../ITitleCamera.h"

class TitleCameraManager;

class TitleCameraBackCut : public ITitleCamera
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleCameraManager)	�^�C�g���J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	TitleCameraBackCut(TitleCameraManager* titleCameraManager);

	//		�f�X�g���N�^
	~TitleCameraBackCut();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�I������
	void Finalize() override;

private:

	//		�����p�x
	const float FIRST_RADIAN = 70.0f;

	//		�ŏI�p�x
	const float END_RADIAN = -100.0f;

	//		�����^�[�Q�b�g
	const DirectX::SimpleMath::Vector3 FIRST_TARGET = { 0.0f, 1.0f, 0.0f };

	//		�ŏI�^�[�Q�b�g
	const DirectX::SimpleMath::Vector3 END_TARGET = { 0.0f, 3.5f, 0.0f };

private:


	//		�o�ߎ���
	float m_elapsedTime;

	//		�^�C�g���J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	TitleCameraManager* m_titleCameraManager;
};