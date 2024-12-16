/*
* @file		TitleEffectManager.cpp
* @brief	�^�C�g���G�t�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/12/13
*/

#pragma once

#include "Effect/Effect/DigitalRain/DegitalRain.h"

class TitleEffectManager
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

private:

	//		�f�W�^���J
	std::unique_ptr<DegitalRain> m_degitalRanin;

};