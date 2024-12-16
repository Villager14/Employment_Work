/*
* @file		TitleCameraFrontAscendingCut.h
* @brief	�^�C�g���J�����̃t�����g�㏸�J�b�g
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "../ITitleCamera.h"

class TitleCameraManager;

class TitleCameraFrontAscendingCut : public ITitleCamera
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(titleCameraManager)	�^�C�g���J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	TitleCameraFrontAscendingCut(TitleCameraManager* titleCameraManager);

	//		�f�X�g���N�^
	~TitleCameraFrontAscendingCut();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�I������
	void Finalize() override;

private:

	//		�������W
	const DirectX::SimpleMath::Vector3 FIRST_POSITION = { 0.0f, 1.0f, -3.0f };

	//		�ŏI���W
	const DirectX::SimpleMath::Vector3 END_POSITION = { 0.0f, 3.7f, -3.0f };

	//		�����^�[�Q�b�g
	const DirectX::SimpleMath::Vector3 FIRST_TARGET = { 0.0f, 1.0f, 0.0f };

	//		�ŏI�^�[�Q�b�g
	const DirectX::SimpleMath::Vector3 END_TARGET = { 0.0f, 3.7f, 0.0f };

private:


	//		�o�ߎ���
	float m_elapsedTime;

	//		�^�C�g���J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	TitleCameraManager* m_titleCameraManager;
};