/*
* @file		Transparency.h
* @brief	�A���t�@�G�t�F�N�g�̏���
* @author	Morita
* @date		2024/10/16
*/


#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"

class EffectRender : public IPostEffect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(manager)	�|�C���^�̃C���X�^���X
	*/
	EffectRender(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~EffectRender();

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

	//		�V�F�[�_�[�̓ǂݍ���
	void LoadShader(
		const wchar_t* vsPath,
		const wchar_t* psPath
	);

	void SetObjectShader(PostEffectObjectShader* shader);

	//		�����_�[�^�[�Q�b�g�̍쐻
	void CreateRenderTarget();

public:
	struct FogShaderConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
	};

private:

	//		���v�w�i�e�N�X�`���p�X
	const wchar_t* CLOCK_BACK_GROUND_TEXTURE_PATH = L"Resources/Texture/UI/Clock/ClockBackGround.png";

	//		�����V�F�[�_�[VS�p�X
	const wchar_t* TRANSPARENCY_VS_PATH = L"Resources/Shader/PostEffect/Transparency/TransparencyVS.cso";

	//		�����V�F�[�_�[GS�p�X
	const wchar_t* TRANSPARENCY_GS_PATH = L"Resources/Shader/PostEffect/Transparency/TransparencyGS.cso";

	//		�����V�F�[�_�[PS�p�X
	const wchar_t* TRANSPARENCY_PS_PATH = L"Resources/Shader/PostEffect/Transparency/TransparencyPS.cso";

	//		�I�u�W�F�N�g�V�F�[�_�[�p�X
	const wchar_t* TRANSPARENCY_OBJECT_PATH = L"Resources/Shader/PostEffect/Transparency/TransparencyObject/TransparencyObject.cso";

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^�̃C���X�^���X
	PostEffectManager* m_postEffectManager;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

	//		���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�����_�[�e�N�X�`��(����)
	std::unique_ptr<DX::RenderTexture> m_transparencyRenderTexture;

	//		�e�N�X�`��
	ID3D11ShaderResourceView* m_texture;

	//		�����e�N�X�`��
	ID3D11ShaderResourceView* m_alphaEffectTexture;

	//		���������_�[�}�l�[�W���[
	std::unique_ptr<UIRenderManager> m_transparencyRenderManager;

	//		�t�H�O�V�F�[�_�[�萔�o�b�t�@
	FogShaderConstBuffer m_fogShaderConstBuffer;

	//		�I�u�W�F�N�g�ɑ΂���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_objectShader;
};