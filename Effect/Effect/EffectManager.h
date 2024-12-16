/*
* @file		EffectManager.h
* @brief	�G�t�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/06/10
*/

#pragma once

#include "WireUseEffect/WireUseEffect.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Game/PlayScene/ObjectManager/WireObject/WireObjectInformation.h"

#include "Effect/Effect/DigitalRain/DegitalRain.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Effect/Effect/Smoke/SmokeEffect.h"

class EffectManager
{
public:

	//		�R���X�g���N�^
	EffectManager(PlayerInformation* playerInformation, PlayerCameraInformation* cameraInformation);

	//		�f�X�g���N�^
	~EffectManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	*
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update();

	/*
	*	�`�揈��
	*
	*	@param	(cameraVelocity)	�����x�N�g��
	*/
	void Render(PostEffectFlag::Flag flag);

	//		�I������
	void Finalize();

private:

	//		���C���[�G�t�F�N�g
	std::unique_ptr<WireUseEffect> m_wireUseEffect;

	//		�v���C���[�̏��
	PlayerInformation* m_playerInformation;

	//		���C���[�̏��
	std::vector<WireObjectInformation>* m_wireInformation;

	//		�f�W�^���J
	std::unique_ptr<DegitalRain> m_degitalRain;

	//		�J�����̏��
	PlayerCameraInformation* m_cameraInformation;

	//		���G�t�F�N�g
	//std::unique_ptr<SmokeEffect> m_smokeEffect;

public:

	void SetWireInformation(std::vector<WireObjectInformation>* wire) { m_wireInformation = wire; }

	//		�J�����̏��
	PlayerCameraInformation* GetCameraInformation() { return m_cameraInformation; }

	PlayerInformation* GetPlayerInformation() { return m_playerInformation; }
};
