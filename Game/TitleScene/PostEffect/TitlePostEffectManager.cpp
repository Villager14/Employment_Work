/*
* @file		TitlePostEffectManager.cpp
* @brief	タイトルポストエフェクトマネージャー
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitlePostEffectManager.h"

TitlePostEffectManager::TitlePostEffectManager
		(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
	//		ポストエフェクトフラグの作製
	m_posteffectFlag = std::make_unique<PostEffectFlag>();

	//		タイトルポストエフェクトオブザーバー
	m_titlePostEffectObserver = std::make_unique<TitlePostEffectObserver>();
}

TitlePostEffectManager::~TitlePostEffectManager()
{
}

void TitlePostEffectManager::Initialize()
{
	//		使用するエフェクトの種類
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Bloom);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::UI);
	//m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::PlayerView);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::UIBack);
	m_posteffectFlag->TrueFlag(PostEffectFlag::Flag::Fade);

	//		ポストエフェクトマネージャーの初期化処理
	m_postEffectManager->Initialize(DirectX::Colors::Black,  m_posteffectFlag.get());
}

void TitlePostEffectManager::Update()
{
	//		ポストエフェクトの更新
	for (int i = 1; i <= PostEffectFlag::Fade;)
	{
		//		フラグが立っていない処理は行わない
		if (!m_posteffectFlag->FlagJudgement(PostEffectFlag::Flag(i)))
		{
			i = i + i;

			continue;
		}

		//		ポストエフェクトの更新
		m_postEffectManager->Update(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		フェードイン終了
	if (m_postEffectManager->GetInformation()->
		FlagJudgement(PostEffectInformation::Flag::FadeInEnd))
	{
		m_titlePostEffectObserver->FadeIn();
		m_postEffectManager->GetInformation()->FalseFlag
		(PostEffectInformation::Flag::FadeInEnd);
	}

	//		フェードアウト終了
	if (m_postEffectManager->GetInformation()->FlagJudgement
		(PostEffectInformation::Flag::SceneEnd))
	{
		m_titlePostEffectObserver->FadeOut();
	}
}

bool TitlePostEffectManager::PostEffectUseJudgement(int postEffectFlag)
{
	//		フラグが立っているかどうか
	if (m_posteffectFlag->FlagJudgement(PostEffectFlag::Flag(postEffectFlag))) return true;

	return false;
}

void TitlePostEffectManager::PostEffectUpdate(int postEffectFlag)
{
	//		ポストエフェクトの更新
	m_postEffectManager->Render(PostEffectFlag::Flag(postEffectFlag));
}

void TitlePostEffectManager::PostEffectRender(int postEffectFlag)
{
	//		ポストエフェクトの描画
	m_postEffectManager->RastRender(PostEffectFlag::Flag(postEffectFlag));
}

void TitlePostEffectManager::PostEffectTextureRender()
{
	//		レンダーテクスチャをリセットする
	m_postEffectManager->ResetRenderTarget();

	//		レンダーテクスチャの描画
	m_postEffectManager->RenderTextureView();
}

void TitlePostEffectManager::SceneEndFadeOut()
{
	//		シーン変更フェードアウト
	m_postEffectManager->GetInformation()->TrueFlag(PostEffectInformation::Flag::SceneEndFade);
}

void TitlePostEffectManager::FadeOut()
{
}

void TitlePostEffectManager::Finalize()
{
	m_postEffectManager->Finalize();

	m_titlePostEffectObserver->Dalete();
}
