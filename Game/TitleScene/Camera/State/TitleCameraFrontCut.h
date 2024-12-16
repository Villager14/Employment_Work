/*
* @file		TitleCameraFrontCut.h
* @brief	�^�C�g���J�����̃t�����g�J�b�g
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "../ITitleCamera.h"

class TitleCameraManager;

class TitleCameraFrontCut : public ITitleCamera
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleCameraManager)	�^�C�g���J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	TitleCameraFrontCut(TitleCameraManager* titleCameraManager);

	//		�f�X�g���N�^
	~TitleCameraFrontCut();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�I������
	void Finalize() override;

private:

	//		�����p�x
	const float FIRST_RADIAN = 90.0f;

	//		�ŏI�p�x
	const float END_RADIAN = 210.0f;

	//		�^�[�Q�b�g
	const DirectX::SimpleMath::Vector3 TARGET = { 0.0f, 4.0f, 0.0f };

private:


	//		�o�ߎ���
	float m_elapsedTime;

	//		�^�C�g���J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	TitleCameraManager* m_titleCameraManager;
};