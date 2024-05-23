/*
* @file		ScreenEffectManager.h
* @brief	スクリーンエフェクトのマネージャー
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

	//		コンストラクタ
	ScreenEffectManager(GameManager* gameManager);

	//		デストラクタ
	~ScreenEffectManager();

	//		初期化処理
	void Initialize();

	//		アップデート
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		レンダーテクスチャを作成する
	void CreateRenderTexture();

	//		レンダーターゲットを変更する
	void ChangeRenderTarget();

	//		初期のレンダーターゲットにする
	void FirstRenderTarget();

private:
	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		サンプラー(一部を取り出す物)
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	//		シェーダーリソース
	ID3D11ShaderResourceView* m_shaderResouceView;

	//		赤いスクリーン
	std::unique_ptr<RedScreen> m_redScreen;

	//		ゲームマネージャー
	GameManager* m_gameManager;
};
