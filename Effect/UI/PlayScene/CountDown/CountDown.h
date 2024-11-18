/*
* @file		CountDown.h
* @brief	�J�E���g�_�E���̏���
* @author	Morita
* @date		2024/11/01
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/UIRenderManager.h"

class CountDown
{
public:

	CountDown();

	~CountDown();

	void Initialize();

	void Update(float time);

	void Render();

	void Finalize();

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		int time = 0;
		DirectX::SimpleMath::Vector3 pad;
		float alpha = 0.0f;
		DirectX::SimpleMath::Vector3 pad2;
	};

public:

	//		�J�E���g�_�E���̍��W
	const DirectX::SimpleMath::Vector2 COUNT_DOWN_POSITION = { 640.0f, 360.0f };

	//		�J�E���g�_�E���̍ō�����
	const float MAX_TIME = 6.0f;

	//		�J�E���g�_�E���̍Œ᎞��
	const float MIN_TIME = 1.0f;

	//		�J�E���g�_�E���e�N�X�`���p�X
	const wchar_t* COUNT_DOWN_TEXTURE_PATH = L"Resources/Texture/UI/CountDown/CountDown.png";
	
	//		�ԍ������xVS�p�X
	const wchar_t* NUMBER_ALPHA_VS_PATH = L"Resources/Shader/UI/NumberAlpha/NumberAlphaVS.cso";

	//		�ԍ������xGS�p�X
	const wchar_t* NUMBER_ALPHA_GS_PATH = L"Resources/Shader/UI/NumberAlpha/NumberAlphaGS.cso";

	//		�ԍ������xPS�p�X
	const wchar_t* NUMBER_ALPHA_PS_PATH = L"Resources/Shader/UI/NumberAlpha/NumberAlphaPS.cso";

private:

	//		����
	float m_time;
	
	//		�A���t�@
	float m_alpha;

	//		�R���X�g�o�b�t�@
	ConstBuffer buffer;

	//		�t�F�[�h�̕`��
	std::unique_ptr<UIRenderManager> m_numberAlpha;
};
