/*
* @file		Bler.h
* @brief	�u���[�̏���
* @author	Morita
* @date		2024/10/02
*/

#pragma once

#include "Common/RenderTexture.h"

#include "../../PostEffectManager.h"

#include "Common/DepthStencil.h"

class Bler
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(postEffectManager)	PostEffectManager�̃C���X�^���X�̃|�C���^
	*/
	Bler(PostEffectManager* postEffectManager);

	~Bler();

	//		����������
	void Initialize();

	/*
	*	�`�揈��
	* 
	*	@param	(texture)	�e�N�X�`��
	*	@return �e�N�X�`��
	*/
	ID3D11ShaderResourceView* Render(ID3D11ShaderResourceView* texture);

	//		�V�F�[�_�[�̍쐻������
	void CreateShader();

	//		�I������
	void Finalize();

	//		�����_�[�e�N�X�`���̍쐬
	void CreateRenderTexture();

public:

	//		�R���X�g�o�b�t�@
	struct SideConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
		DirectX::SimpleMath::Vector4 blerValue;				//		�u���[�̒l
	};

private:

	//		�e�X�g�e�N�X�`���p�X
	const wchar_t* TEST_TEXTURE_PATH = L"Resources/Texture/Test.jpg";

	//		���u���[VS�p�X
	const wchar_t* SLIDER_BLER_VS_PATH = L"Resources/Shader/PostEffect/Bler/SideBler/SideBlerVS.cso";

	//		���u���[GS�p�X
	const wchar_t* SLIDER_BLER_GS_PATH = L"Resources/Shader/PostEffect/Bler/SideBler/SideBlerGS.cso";

	//		���u���[PS�p�X
	const wchar_t* SLIDER_BLER_PS_PATH = L"Resources/Shader/PostEffect/Bler/SideBler/SideBlerPS.cso";


	//		�c�u���[VS�p�X
	const wchar_t* WARP_BLER_VS_PATH = L"Resources/Shader/PostEffect/Bler/WarpBler/WarpBlerVS.cso";

	//		�c�u���[GS�p�X
	const wchar_t* WARP_BLER_GS_PATH = L"Resources/Shader/PostEffect/Bler/WarpBler/WarpBlerGS.cso";

	//		�c�u���[PS�p�X
	const wchar_t* WARP_BLER_PS_PATH = L"Resources/Shader/PostEffect/Bler/WarpBler/WarpBlerPS.cso";

	//		�����u���[VS�p�X
	const wchar_t* EXPANSION_BLER_VS_PATH = L"Resources/Shader/PostEffect/Bler/Expansion/ExpansionVS.cso";

	//		�����u���[GS�p�X
	const wchar_t* EXPANSION_BLER_GS_PATH = L"Resources/Shader/PostEffect/Bler/Expansion/ExpansionGS.cso";

	//		�����u���[PS�p�X
	const wchar_t* EXPANSION_BLER_PS_PATH = L"Resources/Shader/PostEffect/Bler/Expansion/ExpansionPS.cso";

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	PostEffectManager* m_postEffectManager;

	//		�������_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_sideRenderTexture;

	//		�c�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_warpRenderTexture;

	//		�g��e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_expansionRenderTexture;

	//		���u���[
	std::unique_ptr<UIRenderManager> m_sideBler;

	//		�c�u���[
	std::unique_ptr<UIRenderManager> m_warpBler;

	//		�g��u���[
	std::unique_ptr<UIRenderManager> m_expansionBler;

	//		���R���X�g�o�b�t�@
	SideConstBuffer m_sideConstBuffer;

	//		���e�N�X�`��
	ID3D11ShaderResourceView* m_sideTexture;

	//		�c�e�N�X�`��
	ID3D11ShaderResourceView* m_warpTexture;

	//		�g��e�N�X�`��
	ID3D11ShaderResourceView* m_expansionTexture;

	//		���[�x�o�b�t�@
	std::unique_ptr<DepthStencil> m_sideDepthStancil;

	//		�c�[�x�o�b�t�@
	std::unique_ptr<DepthStencil> m_warpDepthStancil;

};