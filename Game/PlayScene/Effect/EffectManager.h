/*
* @file		EffectManager.h
* @brief	�G�t�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/06/10
*/

#pragma once

#include "WireUseEffect/WireUseEffect.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "../Player/PlayerInformation.h"

#include "Game/PlayScene/ObjectManager/WireObject/WireObjectInformation.h"

class EffectManager
{
public:

	//		�R���X�g���N�^
	EffectManager(PlayerInformation* playerInformation);

	//		�f�X�g���N�^
	~EffectManager();

	//		����������
	void Initialize();

	/*
	*	�X�V����
	*
	*	@param	(playerPosition)	�v���C���[�̍��W
	*/
	void Update(PlayerCameraInformation* cameraInformation);

	/*
	*	�`�揈��
	*
	*	@param	(cameraVelocity)	�����x�N�g��
	*/
	void Render();

	//		�I������
	void Finalize();

private:

	//		���C���[�G�t�F�N�g
	std::unique_ptr<WireUseEffect> m_wireUseEffect;

	//		�v���C���[�̏��
	PlayerInformation* m_playerInformation;

	//		���C���[�̏��
	std::vector<WireObjectInformation>* m_wireInformation;

public:

	void SetWireInformation(std::vector<WireObjectInformation>* wire) { m_wireInformation = wire; }
};
