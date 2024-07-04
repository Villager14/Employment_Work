/*
* @file		WireUseEffect.h
* @brief	���C���[�g�p�G�t�F�N�g
* @author	Morita
* @date		2024/06/10
*/

#pragma once

#include "../Billboard/BillboardEffect.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

class WireUseEffect
{
public:

	//		�R���X�g���N�^
	WireUseEffect(PlayerInformation* m_playerInformation);

	//		�f�X�g���N�^
	~WireUseEffect();

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
	void Render(DirectX::SimpleMath::Vector3 position);

	//		�I������
	void Finalize();

private:
	//		�r���{�[�h�G�t�F�N�g
	std::unique_ptr<BillboardEffect> m_billboardEffect;

	//		�v���C���[�̏��
	PlayerInformation* m_playerInformation;
};
