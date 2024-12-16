

#pragma once

#include "Effect/PostEffect/PostEffectFlag.h"
#include "Library/Shader/EffectShaderManager.h"

class EffectManager;

class SmokeEffect
{
public:

	SmokeEffect(EffectManager* effectManager);

	~SmokeEffect();

	//		����������
	void Initialzie();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render(PostEffectFlag::Flag flag);

	//		�I������
	void Finalize();

public:

	struct  ConstBuffer
	{
		DirectX::SimpleMath::Matrix matWorld;
		DirectX::SimpleMath::Matrix matView;
		DirectX::SimpleMath::Matrix matProj;
		DirectX::SimpleMath::Vector4 Diffuse;
	};

private:

	//		�G�t�F�N�g�}�l�[�W���[
	EffectManager* m_effectManager;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�G�t�F�N�g
	std::unique_ptr<EffectShaderManager<ConstBuffer>> m_effect;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;
};