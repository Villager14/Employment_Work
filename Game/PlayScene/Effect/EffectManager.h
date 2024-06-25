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

	std::vector<DirectX::SimpleMath::Vector3> m_wirePosition;

public:

	void SetWirePosition(const std::vector<DirectX::SimpleMath::Vector3>& position) { m_wirePosition = position; }
};
