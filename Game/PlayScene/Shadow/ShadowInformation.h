/*
* @file		ShwdowInformation.h
* @brief	�e�I�u�W�F�N�g�̏��
* @author	Morita
* @date		2024/05/24
*/
#pragma once

#include "Common/DepthStencil.h"

#include "Common/RenderTexture.h"

class ShadowInformation
{
public:

	//		�R���X�g���N�^
	ShadowInformation();

	//		�f�X�g���N�^
	~ShadowInformation();

	//		�[�x�X�e���V�����쐬����
	void CreateDepthStencil();

	//		�����_�[�e�N�X�`�����쐬����
	void CreateRenderTexture();

public:


	//		�萔�o�b�t�@�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantShadowBuffer;

	//		�萔�o�b�t�@�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantDepthBuffer;

private:

	//		�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_proj;

	//		�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	//		���C�g�̕���
	DirectX::SimpleMath::Vector3 m_lightDirection;

	//		�[�x�X�e���V��
	std::unique_ptr<DepthStencil> m_depthStencil;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�e�̃s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowPS;
	
	//		�e�̒��_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowVS;

	//		�e�̐[�x�o�b�t�@�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowDepthPS;

	//		�e�̐[�x�o�b�t�@���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowDepthVS;

	//		�T���v���[�̍쐻
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;

public:

	/*
	*	�v���W�F�N�V�����s���ݒ肷��
	* 
	*	@param	(proj)	�s��
	*/
	void SetProj(DirectX::SimpleMath::Matrix proj) { m_proj = proj; }

	/*
	*	�v���W�F�N�V�����s����󂯎��
	* 
	*	@return �s��
	*/
	const DirectX::SimpleMath::Matrix& GetProj() { return m_proj; }

	/*
	*	�r���[�s���ݒ肷��
	*
	*	@param	(view)	�s��
	*/
	void SetView(DirectX::SimpleMath::Matrix view) { m_view = view; }

	/*
	*	�r���[�s����󂯎��
	* 
	*	@return �s��
	*/
	const DirectX::SimpleMath::Matrix& GetView() { return m_view; }

	/*
	*	���C�g�̕������󂯎��
	* 
	*	@return�@����
	*/
	const DirectX::SimpleMath::Vector3& GetLightDirection() { return m_lightDirection; }

	/*
	*	���C�g�̕�����ݒ肷��
	* 
	*	@param	(direction)	����
	*/
	void SetLightDirection(const DirectX::SimpleMath::Vector3 direction) { m_lightDirection = direction; }

	/*
	*	�[�x�X�e���V�����󂯎��
	* 
	*	@return �[�x�X�e���V���̃C���X�^���X�̃|�C���^
	*/
	DepthStencil* GetDepthStencil() { return m_depthStencil.get(); }

	/*
	*	�����_�[�e�N�X�`�����󂯎��
	* 
	*	@return �����_�[�e�N�X�`���̃C���X�^���X�̃|�C���^
	*/
	DX::RenderTexture* GetRenderTexture() { return m_renderTexture.get(); }

	/*
	*	�e�p�s�N�Z���V�F�[�_�[
	*
	*	@param	(ps)	�s�N�Z���V�F�[�_�[
	*/
	void SetShadowPS(Microsoft::WRL::ComPtr<ID3D11PixelShader> ps)
	{
		m_shadowPS = ps;
	}

	/*
	*	�e�p�s�N�Z���V�F�[�_�[���󂯎��
	* 
	*	@return �s�N�Z���V�F�[�_�[
	*/
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetShadowPS() { return m_shadowPS; }

	/*
	*	�e�p���_�V�F�[�_�[
	*
	*	@param	(vs)	���_�V�F�[�_�[
	*/
	void SetShadowVS(Microsoft::WRL::ComPtr<ID3D11VertexShader> vs)
	{
		m_shadowVS = vs;
	}
	
	/*
	* 
	*	�e�p�V�F�[�_�[���󂯎��
	* 
	*	@return ���_�V�F�[�_�[
	*/
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetShadowVS() { return m_shadowVS; }

	/*
	*	�[�x�p�s�N�Z���V�F�[�_�[
	*
	*	@param	(ps)	�s�N�Z���V�F�[�_�[
	*/
	void SetShadowDepthPS(Microsoft::WRL::ComPtr<ID3D11PixelShader> ps)
	{
		m_shadowDepthPS = ps;
	}

	/*
	*	�e�p�s�N�Z���V�F�[�_�[���󂯎��
	*
	*	@return �s�N�Z���V�F�[�_�[
	*/
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetShadowDepthPS() { return m_shadowDepthPS; }

	/*
	*	�e�p���_�V�F�[�_�[
	*
	*	@param	(vs)	���_�V�F�[�_�[
	*/
	void SetShadowDepthVS(Microsoft::WRL::ComPtr<ID3D11VertexShader> vs)
	{
		m_shadowDepthVS = vs;
	}

	/*
	*
	*	�e�p�V�F�[�_�[���󂯎��
	*
	*	@return ���_�V�F�[�_�[
	*/
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetShadowDepthVS() { return m_shadowDepthVS; }

	/*
	*	�e�萔�o�b�t�@��ݒ肷��
	* 
	*	@param	(buffer)	�R���X�g�o�b�t�@
	*/
	void SetConstBufferShadow(Microsoft::WRL::ComPtr<ID3D11Buffer> buffer)
	{
		m_constantShadowBuffer = buffer;
	}

	/*
	*	�e�萔�o�b�t�@���󂯎��
	* 
	*	@return �R���X�g�o�b�t�@
	*/
	Microsoft::WRL::ComPtr<ID3D11Buffer> GetConstBufferShadow() { return m_constantDepthBuffer; }

	/*
	*	�[�x�萔�o�b�t�@��ݒ肷��
	* 
	*	@param	(buffer)	�R���X�g�o�b�t�@
	*/
	void SetConstBufferDepth(Microsoft::WRL::ComPtr<ID3D11Buffer> buffer)
	{
		m_constantDepthBuffer = buffer;
	}

	/*
	*	�[�x�萔�o�b�t�@���󂯎��
	*
	*	@return �R���X�g�o�b�t�@
	*/
	Microsoft::WRL::ComPtr<ID3D11Buffer> GetConstBufferDepth() { return m_constantDepthBuffer; }

	/*
	*	�V���h�E�}�b�v�̃T���v���[�̍쐻
	* 
	*	@param	(sampler)	�T���v���[
	*/
	void SetShadowMapSampler(Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler)
	{
		m_shadowMapSampler = sampler;
	}

	/*
	*	�V���h�E�}�b�v�T���v���[���󂯎��
	* 
	*	@return �T���v���[
	*/
	Microsoft::WRL::ComPtr<ID3D11SamplerState> GetShadowMapSampler() { return m_shadowMapSampler; }
};