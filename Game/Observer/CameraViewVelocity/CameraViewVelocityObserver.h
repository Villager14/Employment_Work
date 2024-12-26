/*
* @file		CameraViewVelocityObserver.h
* @brief	�J�����̃r���[�x�N�g���I�u�U�[�o�[
* @author	Morita
* @date		2024/12/16
*/

#pragma once

#include "ICameraViewVelocityObserver.h"

class CameraViewVelocityObserver
{
public:

	//		�R���X�g���N�^
	CameraViewVelocityObserver();

	//		�f�X�g���N�^
	~CameraViewVelocityObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(ICameraViewVelocityObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(ICameraViewVelocityObserver* observer);

	/*
	*	�J������View�x�N�g��
	* 
	*	@param	(velocity)	�J������View�x�N�g��
	*/
	void CameraViewVelocity(DirectX::SimpleMath::Vector3 velocity);

	/*
	*	�J������View
	*
	*	@param	(view)	�J������View
	*/
	void CameraView(DirectX::SimpleMath::Vector3 view);

	/*
	*	�J������Up
	* 
	*	@param	(up)	�J������Up
	*/
	void CameraUp(DirectX::SimpleMath::Vector3 up);

	//		�S�폜
	void Dalete();
private:

	std::vector<ICameraViewVelocityObserver*> m_observer;

};