/*
* @file		PlayerCameraManager.h
* @brief	�v���C���[�̃J�����̃}�l�[�W���[
* @author	Morita
* @date		2024/05/08
*/

#pragma once

#include "IPlayerCamera.h"

#include "PlayerCameraInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/PlayScene/Player/Observer/HeightObserver/IPHeightObserver.h"

#include "Game/PlayScene/Player/Observer/SpeedObserver/IPSpeedObserver.h"

#include "Game/PlayScene/Player/Observer/PCameraObserver/IPCameraObserver.h"

#include "Game/Observer/CameraViewVelocity/CameraViewVelocityObserver.h"

#include <unordered_map>

class PlayerCameraManager : public IPHeightObserver,
							public IPSpeedObserver,
							public IPCameraObserver
{
public:
	//		�R���X�g���N�^
	PlayerCameraManager(GameManager* gameManager);

	//		�f�X�g���N�^
	~PlayerCameraManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	* 
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update();

	//		�I������
	void Finalize();

	//		�J�����̈ړ�����
	void CameraMove();

	//		����p
	void ViewingAngleUpdate();

	/*
	*	�v���W�F�N�g�V�����̍쐻
	* 
	*	@param	(fov)			����p
	*	@param	(nearPlane)�@	�ŒZ���싗��
	*	@param	(farPlane)		�Œ����싗��
	*/
	void CreateProj(float fov, float nearPlane, float farPlane);

	//		eye�̍쐻
	void CreateEye(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY);

	//		���_�̗h��
	void ShakingView();

	//		���h��
	void HorizontalShaking();

	//		�c�h��
	void VerticalShaking();

	void PlayerHeght(DirectX::SimpleMath::Vector3 height) override;

	void NowSpeed(float speed) override;

	void ShakeHead() override;

	void CameraStop() override;

	void WallWalkMove(float height) override;

	void Direction(DirectX::SimpleMath::Vector3 direction) override;

	void WallNormalize(DirectX::SimpleMath::Vector3 noramlize) override;

public:

	//		�J�����̃^�C�v
	enum CameraType
	{
		Debug,
		Standard,
		WallWalk,
		Start,
		Stop,
		Goal,
		Death,
	};

private:

	//		���
	IPlayerCamera* m_state;

	//		�J�����̏��
	std::unique_ptr<PlayerCameraInformation> m_information;
	
	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;

	//		�h���N���X�̊i�[
	std::unordered_map<CameraType, std::unique_ptr<IPlayerCamera>> m_stateInformation;

	//		�J�����̃r���[Velocity�I�u�U�[�o�[
	std::unique_ptr<CameraViewVelocityObserver> m_cameraViewVelocityObserver;

	//		���݂̃J�����^�C�v
	CameraType m_cameraType;

	//		�h�ꎞ��
	float m_shakingTime;

	//		����U�銄��
	float m_shakingRatio;

	//		���𓮂������x
	float m_shakingSpeed;

public:
	/*
	*	�J�����̏�Ԃ̐؂�ւ�
	* 
	*	@param	(type)	�J�����̎��
	*/
	void ChangeState(CameraType type);


	/*
	*	�Q�[���}�l�[�W���[���󂯎��
	* 
	*	@return �Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	/*
	*	�J�����̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PlayerCameraInformation* GetInformation() { return m_information.get(); }
	
	/*
	*	�I�u�U�[�o�[�̒ǉ�
	* 
	*	@param	(observer)	�I�u�U�[�o�[�̃|�C���^�̃C���X�^���X
	*/
	void AddCameraObserver(ICameraViewVelocityObserver* observer) { m_cameraViewVelocityObserver->AddObserver(observer); }
};
