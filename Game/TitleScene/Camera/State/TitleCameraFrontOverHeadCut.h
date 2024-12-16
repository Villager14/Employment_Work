/*
* @file		TitleCameraFrontOverHeadCut.h
* @brief	�^�C�g���J�����̓���J�b�g
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "../ITitleCamera.h"

class TitleCameraManager;

class TitleCameraFrontOverHeadCut : public ITitleCamera
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleCameraManager)	�^�C�g���J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	TitleCameraFrontOverHeadCut(TitleCameraManager* titleCameraManager);

	//		�f�X�g���N�^
	~TitleCameraFrontOverHeadCut();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�I������
	void Finalize() override;

private:

	//		�������W
	const DirectX::SimpleMath::Vector3 FIRST_POSITION = { 0.0f, 5.0f, -0.1f };

	//		�ŏI���W
	const DirectX::SimpleMath::Vector3 END_POSITION = { 0.0f, 8.0f, -0.1f };

	//		�����^�[�Q�b�g
	const DirectX::SimpleMath::Vector3 TARGET = { 0.0f, 4.0f, 0.0f };

private:


	//		�o�ߎ���
	float m_elapsedTime;

	//		�^�C�g���J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	TitleCameraManager* m_titleCameraManager;
};