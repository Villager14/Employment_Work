/*
* @file		BackGroundMove.h
* @brief	�w�i�̈ړ�
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class BackGroundMove
{
public:

	//		�R���X�g���N�^
	BackGroundMove();

	//		�f�X�g���N�^
	~BackGroundMove();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		�E�B���h�E�T�C�Y
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		��]�s��
		DirectX::SimpleMath::Vector4 time;				//		����
	};

private:

	//		�w�i�̑��x
	const float BACK_GROUND_SPEED = 0.1f;

	//		�w�i�e�N�X�`���̃t�@�C���p�X
	const wchar_t* BACK_GROUND_TEXTURE_PATH = L"Resources/Texture/TitleScene/TitleBack.png";

	//		�w�i�ړ�VS�p�X
	const wchar_t* BACK_GROUND_VS_PATH = L"Resources/Shader/UI/BackGroundMove/BackGroundMoveVS.cso";

	//		�w�i�ړ�GS�p�X
	const wchar_t* BACK_GROUND_GS_PATH = L"Resources/Shader/UI/BackGroundMove/BackGroundMoveGS.cso";

	//		�w�i�ړ�PS�p�X
	const wchar_t* BACK_GROUND_PS_PATH = L"Resources/Shader/UI/BackGroundMove/BackGroundMovePS.cso";

private:

	//		UI�`��}�l�[�W���[
	std::unique_ptr<UIRenderManager> m_uiRenderManager;

	//		����
	float m_time;

	//		�R���X�g�o�b�t�@
	ConstBuffer buffer;
};
