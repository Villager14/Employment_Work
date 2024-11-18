/*
* @file		ScreenObjectView.h
* @brief	�X�N���[���ɃI�u�W�F�N�g��`�悷��̏���
* @author	Morita
* @date		2024/11/11
*/

#pragma once

#include "../../PostEffectManager.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"

class ScreenObjectView : public IPostEffect
{
public:

	ScreenObjectView(PostEffectManager* postEffectManager);

	~ScreenObjectView();
	
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

public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
	};

private:

	//		���v�w�i�e�N�X�`���p�X
	const wchar_t* CLOCK_BACK_GROUND_TEXTURE_PATH = L"Resources/Texture/UI/Clock/ClockBackGround.png";

	//		�X�N���[���I�u�W�F�N�g�`��VS�p�X
	const wchar_t* SCREEN_OBJECT_VIEW_VS_PATH = L"Resources/Shader/PostEffect/ScreenObjectView/ScreenObjectViewVS.cso";

	//		�X�N���[���I�u�W�F�N�g�`��GS�p�X
	const wchar_t* SCREEN_OBJECT_VIEW_GS_PATH = L"Resources/Shader/PostEffect/ScreenObjectView/ScreenObjectViewGS.cso";

	//		�X�N���[���I�u�W�F�N�g�`��PS�p�X
	const wchar_t* SCREEN_OBJECT_VIEW_PS_PATH = L"Resources/Shader/PostEffect/ScreenObjectView/ScreenObjectViewPS.cso";

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^�̃C���X�^���X
	PostEffectManager* m_postEffectManager;

	//		�e�N�X�`��
	ID3D11ShaderResourceView* m_texture;
	ID3D11ShaderResourceView* m_objectTexture;

	//		�����_�[�}�l�[�W���[
	std::unique_ptr<UIRenderManager> m_screenObjectShader;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	std::unique_ptr<DX::RenderTexture> m_objectrenderTexture;

};