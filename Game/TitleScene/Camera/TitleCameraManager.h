/*
* @file		TitleCameraManager.h
* @brief	�^�C�g���J�����}�l�[�W���[
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "ITitleCamera.h"

#include "../Observer/FadeObserver/FadeObserver.h"

class TitleCameraManager
{
public:

	//		�R���X�g���N�^
	TitleCameraManager();

	//		�f�X�g���N�^
	~TitleCameraManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�I������
	void Finalize();

	/*
	*	�r���[�̍쐻
	* 
	*	@param	(position)	���W
	*	@param	(target)	���_�̃^�[�Q�b�g
	*/
	void CreateView(DirectX::SimpleMath::Vector3 position,
					DirectX::SimpleMath::Vector3 target);

	/*
	*	�t�F�[�h�A�E�g���s����
	* 
	*	@param	(time)	����
	*/
	void FadeOut(float time) { if (time > FADE_START_TIME && !m_fadeOutUseJudgement) 
	{ 
		m_fadeObserver->FadeOut();
		m_fadeOutUseJudgement = true;
	} }

private:

	//		�v���W�F�̍쐻
	void CreateProj();

public:

	enum CameraType
	{
		Non,
		Front,
		FrontAscending,
		OverHead,
		Back,

	};

public:
	/*
	*	��Ԃ̑J��
	* 
	*	@param	(changeState)	��Ԃ̑J��
	*/
	void ChangeState(CameraType changeState);

private:

	//		�t�F�[�h�J�n����
	const float FADE_START_TIME = 0.95f;

private:

	//		�J�����̏��
	std::unordered_map<CameraType, std::unique_ptr<ITitleCamera>> m_cameraInformation;

	//		�J�����̃^�C�v
	CameraType m_cameraType;

	//		�J�����̏��
	ITitleCamera* m_state;

	//		�t�F�[�h�I�u�U�[�o�[
	std::unique_ptr<FadeObserver> m_fadeObserver;

	//		�t�F�[�h�A�E�g���s�������ǂ���
	bool m_fadeOutUseJudgement;

public:

	/*
	*	�t�F�[�h�I�u�U�[�o�[��ǉ�����
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃|�C���^
	*/
	void AddFadeObserver(IFadeObserver* observer) { m_fadeObserver->AddObserver(observer); };
};