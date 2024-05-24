/*
* @file		Shwdow.h
* @brief	�e�I�u�W�F�N�g
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "ShadowInformation.h"

#include "Game/PlayScene/Player/PlayerInformation.h"


class Shadow
{
public:

	//		�R���e�L�X�g
	Shadow();

	//		�f�X�g���N�^
	~Shadow();

	//		����������
	void Initialize();

	//		�I������
	void Finalize();

	//		�e�̍쐬
	void CreateShadow();

	void Render();

	/*
	*	�����_�[�^�[�Q�b�g�̕ύX
	*
	*	@param	(playerPos)	�v���C���[�̍��W
	*/
	void ChangeRenderTarget(const DirectX::SimpleMath::Vector3& playerpos);

private:

	//		�萔�o�b�t�@�P
	struct ConstantBuffer
	{
		DirectX::XMMATRIX lightViewProj;	// ���C�g�̓��e��Ԃ֍��W�ϊ�����s��
		DirectX::XMVECTOR lightPosition;	// ���C�g�̈ʒu
		DirectX::XMVECTOR lightDirection;	// ���C�g�̕���
		DirectX::XMVECTOR lightAmbient;		// ���C�g�̊���
	};

	//		�萔�o�b�t�@�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	//		�萔�o�b�t�@�Q
	struct ConstantBuffer2
	{
		float fCosTheta;		// �X�|�b�g���C�g��fov/2
		float pad[3];
	};

	//		�萔�o�b�t�@�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer2;

	//		�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture2D;


	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

private:

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowShaderPS;

	//		���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowShaderVS;

	//		�s�N�Z���[�x�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowDepthShaderPS;

	//		���_�[�x�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowDepthShaderVS;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�[�x�X�e���V��
	std::unique_ptr<DepthStencil> m_depthStencil;

	//		�T���v���[�̍쐻
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;

	//		���C�g�̈ʒu
	DirectX::SimpleMath::Vector3 m_lightPosition;

	//		���C�g�̉�]
	DirectX::SimpleMath::Quaternion m_lightRotate;

	//		�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	//		�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_proj;

	//		���C�g�̕���
	DirectX::SimpleMath::Vector3 m_rightDirection;

	DirectX::SimpleMath::Vector3 playerPostion;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	std::unique_ptr<DirectX::Model> m_light;

	//		���C�g�͈̔�
	float m_lightRange;

	//		�V���h�E�}�b�v�T�C�Y
	float m_shadowSize;

	//		�e�̏��
	std::unique_ptr<ShadowInformation> m_information;

public:

		/*
	*	�e�̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	ShadowInformation* GetInformation() { return m_information.get(); }


	/*
	*	�[�x�o�b�t�@�p�r���[�s��
	*
	*	@return �r���[�s��
	*/
	const DirectX::SimpleMath::Matrix& GetDepthView() { return m_view; }

	/*
	*	�[�x�o�b�t�@�p�v���W�F�N�V�����s��
	*
	*	@return	�v���W�F�N�V�����s��
	*/
	const DirectX::SimpleMath::Matrix& GetDpethProj() { return m_proj; }

	/*
	*	�[�x�o�b�t�@�p�s�N�Z���V�F�[�_�[
	*
	*	@return	�s�N�Z���V�F�[�_�[
	*/
	const Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetDepthPSShader()
	{
		return m_shadowDepthShaderPS;
	}

	/*
	*	�[�x�o�b�t�@�p���_�V�F�[�_�[
	*
	*	@return	���_�V�F�[�_�[
	*/
	Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetDepthVSShader()
	{
		return m_shadowDepthShaderVS;
	}

	/*
	*	�e�p�s�N�Z���V�F�[�_�[
	*
	*	@return	�s�N�Z���V�F�[�_�[
	*/
	const Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetShadowPSShader()
	{
		return m_shadowShaderPS;
	}

	/*
	*	�e�p���_�V�F�[�_�[
	*
	*	@return	���_�V�F�[�_�[
	*/
	Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetShadowVSShader()
	{
		return m_shadowShaderVS;
	}

	/*
	*	�萔�o�b�t�@1���󂯎��
	*
	*	@return �萔�o�b�t�@
	*/
	const Microsoft::WRL::ComPtr<ID3D11Buffer>& GetConstantBuffer1()
	{
		return m_constantBuffer;
	}

	/*
	*	�萔�o�b�t�@2���󂯎��
	*
	*	@return �萔�o�b�t�@
	*/
	const Microsoft::WRL::ComPtr<ID3D11Buffer>& GetConstantBuffer2()
	{
		return m_constantBuffer2;
	}

	/*
	*	�T���v���[���󂯎��
	*
	*	@return �T���v���[
	*/
	const Microsoft::WRL::ComPtr<ID3D11SamplerState>& GetSamplerState()
	{
		return m_shadowMapSampler;
	}

	/*
	*	�V�F�[�_�[���\�[�X�r���[�̎擾
	*
	*	@return	�V�F�[�_�[���\�[�X�r���[
	*/
	ID3D11ShaderResourceView* GetShaderResourceView()
	{
		return m_renderTexture->GetShaderResourceView();
	}
};



//class Shadow
//{
//private:
//
//	//		�萔�o�b�t�@�P
//	struct ConstantBufferShadow
//	{
//		DirectX::XMMATRIX lightViewProj;	// ���C�g�̓��e��Ԃ֍��W�ϊ�����s��
//		DirectX::XMVECTOR lightPosition;	// ���C�g�̈ʒu
//		DirectX::XMVECTOR lightDirection;	// ���C�g�̕���
//		DirectX::XMVECTOR lightAmbient;		// ���C�g�̊���
//	};
//
//	//		�萔�o�b�t�@�Q
//	struct ConstantBufferDepth
//	{
//		float fCosTheta;		// �X�|�b�g���C�g��fov/2
//		float pad[3];
//	};
//
//public:
//
//	//		�R���X�g���N�^
//	Shadow(PlayerInformation* playerInformation);
//
//	//		�f�X�g���N�^
//	~Shadow();
//
//	//		����������
//	void Initialize();
//
//	//		�^�[�Q�b�g��ύX����
//	void ChangeTarget();
//
//	//		�e�̍쐻
//	void CreateShadow();
//
//	//		�V�F�[�_�[�̍쐻
//	void CreateShader();
//
//	//		�萔�o�b�t�@�̍쐻
//	void CreateConstBuffer();
//private:
//	//		�e�̏��
//	std::unique_ptr<ShadowInformation> m_information;
//
//	//		�v���C���[�̏��
//	PlayerInformation* m_playerInformation;
//
//	//		�萔�o�b�t�@�ւ̃|�C���^
//	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantShadowBuffer;
//
//	//		�萔�o�b�t�@�ւ̃|�C���^
//	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantDepthBuffer;
//
//	//		�T���v���[�̍쐻
//	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;
//
//	//		�e�̃s�N�Z���V�F�[�_�[
//	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowPS;
//
//	//		�e�̒��_�V�F�[�_�[
//	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowVS;
//
//	//		�e�̐[�x�o�b�t�@�s�N�Z���V�F�[�_�[
//	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_shadowDepthPS;
//
//	//		�e�̐[�x�o�b�t�@���_�V�F�[�_�[
//	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shadowDepthVS;
//
//
//
//	//		�[�x�X�e���V��
//	std::unique_ptr<DepthStencil> m_depthStencil;
//
//	//		�����_�[�e�N�X�`��
//	std::unique_ptr<DX::RenderTexture> m_renderTexture;
//
//public:
//
//	/*
//	*	�e�̏����󂯎��
//	* 
//	*	@return �C���X�^���X�̃|�C���^
//	*/
//	ShadowInformation* GetInformation() { return m_information.get(); }
//
//	/*
//*	�e�p�s�N�Z���V�F�[�_�[���󂯎��
//*
//*	@return �s�N�Z���V�F�[�_�[
//*/
//	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetShadowDepthPS() { return m_shadowDepthPS; }
//
//	/*
//*
//*	�e�p�V�F�[�_�[���󂯎��
//*
//*	@return ���_�V�F�[�_�[
//*/
//	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetShadowDepthVS() { return m_shadowDepthVS; }
//
//};
//
