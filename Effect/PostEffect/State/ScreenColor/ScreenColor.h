/*
* @file		ScreenColor.h
* @brief	�X�N���[���̐F
* @author	Morita
* @date		2024/10/21
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"


class ScreenColor : public IPostEffect
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(manager)	�|�C���^�̃C���X�^���X
	*/
	ScreenColor(PostEffectManager* postEffectManager);

	//		�f�X�g���N�^
	~ScreenColor();

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

	//		�Ԃ����
	bool RedScreen();

	//		�O���[���
	bool GrayScreen();

	//		�����_�[�^�[�Q�b�g���쐬����
	void CreateRenderTarget();

public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
		float elasedTime = 0.0f;							//		�o�ߎ���
		DirectX::SimpleMath::Vector3 pad;
		DirectX::SimpleMath::Vector4 color;					//		�F
	};

private:

	//		���v�w�i�e�N�X�`���p�X
	const wchar_t* CLOCK_BACK_GROUND_TEXTURE_PATH = L"Resources/Texture/UI/Clock/ClockBackGround.png";

	//		�X�N���[���J���[VS�p�X
	const wchar_t* SCREEN_COLOR_VS_PATH = L"Resources/Shader/PostEffect/ScreenColor/ScreenColorVS.cso";

	//		�X�N���[���J���[GS�p�X
	const wchar_t* SCREEN_COLOR_GS_PATH = L"Resources/Shader/PostEffect/ScreenColor/ScreenColorGS.cso";

	//		�X�N���[���J���[PS�p�X
	const wchar_t* SCREEN_COLOR_PS_PATH = L"Resources/Shader/PostEffect/ScreenColor/ScreenColorPS.cso";

private:

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^�̃C���X�^���X
	PostEffectManager* m_postEffectManager;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�t�H�O�e�N�X�`��
	ID3D11ShaderResourceView* m_colorTexture;

	//		�[�x�̕`��
	std::unique_ptr<UIRenderManager> m_depthShaderView;

	//		�t�H�O�V�F�[�_�[�萔�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�o�ߎ���
	float m_elapsedTime;

	//		�t���O
	bool m_menuOpenJudgement;

};