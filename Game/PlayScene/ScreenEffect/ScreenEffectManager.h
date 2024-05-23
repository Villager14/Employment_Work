/*
* @file		ScreenEffectManager.h
* @brief	�X�N���[���G�t�F�N�g�̃}�l�[�W���[
* @author	Morita
* @date		2024/05/22
*/

#pragma once

#include "Common/RenderTexture.h"

#include "FailureScreen/RedScreen.h"

#include "Game/PlayScene/GameManager/GameManager.h"

class ScreenEffectManager
{
public:

	//		�R���X�g���N�^
	ScreenEffectManager(GameManager* gameManager);

	//		�f�X�g���N�^
	~ScreenEffectManager();

	//		����������
	void Initialize();

	//		�A�b�v�f�[�g
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		�����_�[�e�N�X�`�����쐬����
	void CreateRenderTexture();

	//		�����_�[�^�[�Q�b�g��ύX����
	void ChangeRenderTarget();

	//		�����̃����_�[�^�[�Q�b�g�ɂ���
	void FirstRenderTarget();

private:
	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�T���v���[(�ꕔ�����o����)
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	//		�V�F�[�_�[���\�[�X
	ID3D11ShaderResourceView* m_shaderResouceView;

	//		�Ԃ��X�N���[��
	std::unique_ptr<RedScreen> m_redScreen;

	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;
};
