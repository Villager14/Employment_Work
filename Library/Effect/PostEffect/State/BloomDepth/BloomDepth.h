/*
* @file		BloomDepth.h
* @brief	�u���[���̐[�x����
* @author	Morita
* @date		2024/10/14
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../IPostEffect.h"

class BloomDepth : public IPostEffect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(posteffectManager)	�|�X�g�G�t�F�N�g�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	*/
	BloomDepth(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~BloomDepth();

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

	//		�[�x�쐬
	void CreateDepth();

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
	};

private:
	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_depthRenderTexture;

	//		�[�x�̕`��
	std::unique_ptr<UIRenderManager> m_depthShaderView;

	//		�e�N�X�`��
	ID3D11ShaderResourceView* m_texture;

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	PostEffectManager* m_postEffectManager;

	//		�[�x�X�e���V��
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	//		�[�x���\�[�X
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_depthSRV;

	//		�[�x�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthTexture;

public:

};