/*
* @file		TransparencyDepth.h
* @brief	���������̐[�x����
* @author	Morita
* @date		2024/10/18
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../IPostEffect.h"

class EffectDepthRender : public IPostEffect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(posteffectManager)	�|�X�g�G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	EffectDepthRender(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~EffectDepthRender();

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
	ID3D11ShaderResourceView* GetTexture() override { return m_texture; };

	//		�����_�[�^�[�Q�b�g�̍쐻
	void CreateRenderTarget();

private:
	//		�I�u�W�F�N�g�V�F�[�_�[�p�X
	const wchar_t* TRANSPARENCY_OBJECT_PATH = L"Resources/Shader/PostEffect/Transparency/TransparencyObject/TransparencyObject.cso";

private:

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�e�N�X�`��
	ID3D11ShaderResourceView* m_texture;

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	PostEffectManager* m_postEffectManager;

	//		�I�u�W�F�N�g�ɑ΂���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_objectShader;
};
