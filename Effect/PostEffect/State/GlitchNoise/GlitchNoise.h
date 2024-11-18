/*
* @file		GlitchNoise.h
* @brief	�O���b�`�m�C�Y
* @author	Morita
* @date		2024/10/22
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"


class GlitchNoise : public IPostEffect
{
public:

	/*
	*	�R���X�g���N�^
	*
	*	@param	(manager)	�|�C���^�̃C���X�^���X
	*/
	GlitchNoise(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~GlitchNoise();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�I�u�W�F�N�g�`��
	void ObjectRender() override;

	//		�|�X�g�G�t�F�N�g��̕`��
	void PostEffectRender() override;

	//		�I������
	void Filanize() override;

	//		�e�N�X�`�����󂯎��
	ID3D11ShaderResourceView* GetTexture() override { return nullptr; };

	//		�����_�[�^�[�Q�b�g���쐬����
	void CreateRenderTarget();

public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
	};

private:

	//		���v�w�i�e�N�X�`���p�X
	const wchar_t* CLOCK_BACK_GROUND_TEXTURE_PATH = L"Resources/Texture/UI/Clock/ClockBackGround.png";

	//		�O���b�`VS�p�X
	const wchar_t* GLITCH_NOIZE_VS_PATH = L"Resources/Shader/PostEffect/GlitchNoise/GlitchNoiseVS.cso";

	//		�O���b�`GS�p�X
	const wchar_t* GLITCH_NOIZE_GS_PATH = L"Resources/Shader/PostEffect/GlitchNoise/GlitchNoiseGS.cso";

	//		�O���b�`PS�p�X
	const wchar_t* GLITCH_NOIZE_PS_PATH = L"Resources/Shader/PostEffect/GlitchNoise/GlitchNoisePS.cso";

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^�̃C���X�^���X
	PostEffectManager* m_postEffectManager;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�t�H�O�e�N�X�`��
	ID3D11ShaderResourceView* m_colorTexture;

	//		�[�x�̕`��
	std::unique_ptr<UIRenderManager> m_depthShaderView;

	ConstBuffer m_constBuffer;

};