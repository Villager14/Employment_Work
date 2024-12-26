/*
* @file		PostEffectManager.h
* @brief	�|�X�g�G�t�F�N�g�}�l�[�W���[
* @author	Morita
* @date		2024/10/01
*/

#pragma once

#include "Common/RenderTexture.h"

#include "Library/Shader/StandardShader.h"

#include "PostEffectCommonProcess.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "PostEffectObjectShader.h"

#include "IPostEffect.h"

#include "PostEffectInformation.h"

#include "Game/Observer/Menu/MenuOpenJudgementObserver/IMenuOpenJudgementObserver.h"

class Bler;

class PostEffectManager : public IMenuOpenJudgementObserver
{
public:

	//		�R���X�g���N�^
	PostEffectManager();

	//		�f�X�g���N�^
	~PostEffectManager();

	//		����������
	void Initialize(DirectX::XMVECTORF32 color, PostEffectFlag* flag);

	//		�X�V����
	void Update(PostEffectFlag::Flag flag);

	//		�`�揈��
	void Render(PostEffectFlag::Flag flag);

	//		�ŏI�`�揈��
	void RastRender(PostEffectFlag::Flag flag);

	//		�I������
	void Finalize();

	//		�|�X�g�G�t�F�N�g�̍쐬
	void CreatePostEffect(PostEffectFlag* flag);

	//		�T���v���[�̍쐻
	void CreateSampler();

	//		�����_�[�^�[�Q�b�g�̕ύX
	ID3D11ShaderResourceView* ChangeRenderTarget(DX::RenderTexture* renderTarget,
		ID3D11DepthStencilView* depthStencil);

	//		�����_�[�^�[�Q�b�g����ɖ߂�
	void ResetRenderTarget();

	//		�����_�[�e�N�X�`���̕`��
	void RenderTextureView();

	//		���j���[���J���Ă���
	void MenuOpen() override;

	//		���j���[����Ă���
	void MenuClose() override;

public:

	enum UIType
	{
		RastTexture,
		UITexture,
	};

private:

	//		�|�X�g�G�t�F�N�g�̋��ʏ���
	std::unique_ptr<PostEffectCommonProcess> m_commonProcess;

	//		�X�^���_�[�h�V�F�[�_�[
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

	//		�T���v���[(�ꕔ�����o����)
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	ID3D11ShaderResourceView* m_shaderResourceView;

	//		�u���[�̏���
	std::unique_ptr<Bler> m_bler;

	//		�|�X�g�G�t�F�N�g
	std::unordered_map<PostEffectFlag::Flag, std::unique_ptr<IPostEffect>> m_postEffectProcess;

	//		�w�i�F
	DirectX::XMVECTORF32 m_backColor;

	//		�w�i�`��F
	DirectX::XMVECTORF32 m_backRenderColor;

	//		�I�u�W�F�N�g�ɑ΂���V�F�[�_�[
	std::unique_ptr<PostEffectObjectShader> m_objectShader;

	//		�|�X�g�G�t�F�N�g�̏��
	std::unique_ptr<PostEffectInformation> m_information;

	//		���j���[���J���Ă��邩���f����
	bool m_openMenuJudgement;

public:

	/*
	*	�|�X�g�G�t�F�N�g�̏����󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	PostEffectInformation* GetInformation() { return m_information.get(); }

	/*
	*	�X�^���_�[�h�V�F�[�_�[���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader.get(); }

	/*
	*	�u���[�̏������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	Bler* GetBler() { return m_bler.get(); }

	/*
	*	�w�i�F���󂯎��
	*
	*  @return �w�i�F
	*/
	DirectX::XMVECTORF32 GetBackColor() { return m_backColor; };

	/*
	*	�`��w�i�F���󂯎��
	*
	*	@return �`��w�i�F
	*/
	DirectX::XMVECTORF32 GetBackRenderColor() { return m_backRenderColor; }

	/*
	*	�`��w�i�F��ݒ肷��
	*
	*	@param	(�w�i�F) �F
	*/
	void SetBackRenderColor(DirectX::XMVECTORF32 color) { m_backRenderColor = color; }

	/*
	*	���ʏ������󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	PostEffectCommonProcess* GetCommonProcess() { return m_commonProcess.get(); }

	/*
	*	�I�u�W�F�N�g�V�F�[�_�[���󂯎��
	*
	*	@return �C���X�^���X�̃|�C���^
	*/
	PostEffectObjectShader* GetPostObjectShader() { return m_objectShader.get(); }

	/*
	*	�V�F�[�_�[���\�[�X�r���[���󂯎��
	* 
	*	@return	�|�C���^
	*/
	ID3D11ShaderResourceView* GetShaderTexture() { return m_shaderResourceView; }

	/*
	*	���j���[���J���Ă��邩���f����
	* 
	*	@return true : �J���Ă���@false : �J���Ă��Ȃ�
	*/
	bool GetMenuOpenJudgement() { return m_openMenuJudgement; }

	void SetShaderTexture(ID3D11ShaderResourceView* texture) { m_shaderResourceView = texture; }

	std::unordered_map<PostEffectFlag::Flag, std::unique_ptr<IPostEffect>>* GetPostEffectProcess() { return &m_postEffectProcess; }
};