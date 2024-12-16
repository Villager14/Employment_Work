

#pragma once

#include "Effect/PostEffect/PostEffectFlag.h"
#include "Library/Shader/EffectShaderManager.h"

class EffectManager;

class SmokeEffect
{
public:

	SmokeEffect(EffectManager* effectManager);

	~SmokeEffect();

	//		初期化処理
	void Initialzie();

	//		更新処理
	void Update();

	//		描画処理
	void Render(PostEffectFlag::Flag flag);

	//		終了処理
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

	//		エフェクトマネージャー
	EffectManager* m_effectManager;

	//		コンストバッファ
	ConstBuffer m_constBuffer;

	//		エフェクト
	std::unique_ptr<EffectShaderManager<ConstBuffer>> m_effect;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;
};