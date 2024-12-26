/*
* @file		TitleEffectManager.cpp
* @brief	�^�C�g���G�t�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/12/13
*/

#pragma once

#include "Effect/Effect/DigitalRain/DegitalRain.h"

#include "Game/Observer/CameraViewVelocity/ICameraViewVelocityObserver.h"

class TitleEffectManager : public ICameraViewVelocityObserver
{
public:

	//		�R���X�g���N�^
	TitleEffectManager();

	//		�f�X�g���N�^
	~TitleEffectManager();

	//		����������
	void Initialize();
	
	//		�X�V����
	void Update();

	//		�`�揈��
	void Render(PostEffectFlag::Flag flag);

	//		�I������
	void Finalize();

	//		�J�����̃r���[�x�N�g��
	void CameraViewVelocity(DirectX::SimpleMath::Vector3 velocity) override;

	//		�J�����̃r���[
	void CameraView(DirectX::SimpleMath::Vector3 view) override;

	//		�J�����̃A�b�v
	void CameraUp(DirectX::SimpleMath::Vector3 up) override;

private:

	//		�f�W�^���J
	std::unique_ptr<DegitalRain> m_degitalRain;

};