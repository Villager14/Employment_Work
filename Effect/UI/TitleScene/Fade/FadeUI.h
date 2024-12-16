/*
* @file		FadeUI.h
* @brief	�t�F�[�hUI
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class FadeUI
{
public:

	//		�R���X�g���N�^
	FadeUI();

	//		�f�X�g���N�^
	~FadeUI();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		�t�F�[�h�A�E�g���g��
	void FadeOutUse();

private:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		�A�X�y�N�g��
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		��]�s��
		float time = 0.0f;								//		����
		DirectX::SimpleMath::Vector3 pad;
	};

private:

	//		�t�F�[�h�e�N�X�`���p�X
	const wchar_t* FADE_TEXTURE_PATH = L"Resources/Texture/UI/Fade/BlackTexture.png";

	//		�t�F�[�hVS�p�X
	const wchar_t* FADE_VS_PATH = L"Resources/Shader/UI/Fade/FadeShaderVS.cso";

	//		�t�F�[�hGS�p�X
	const wchar_t* FADE_GS_PATH = L"Resources/Shader/UI/Fade/FadeShaderGS.cso";

	//		�t�F�[�hPS�p�X
	const wchar_t* FADE_PS_PATH = L"Resources/Shader/UI/Fade/FadeShaderPS.cso";

private:

	ConstBuffer m_buffer;

	float m_time;

	//		�t�F�[�h�A�E�g
	bool m_fadeOutFlag;

	//		�t�F�[�h�C��
	bool m_fadeInFlag;

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;
};