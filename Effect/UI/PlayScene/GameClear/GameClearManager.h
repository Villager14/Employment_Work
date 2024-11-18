/*
* @file		GameOverManager.h
* @brief	ゲームオーバーマネージャー
* @author	Morita
* @date		2024/05/23
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "../UIManager.h"

#include "Library/Shader/UIRenderManager.h"

class GameClearManager
{
public:
	//		コンストラクタ
	GameClearManager(GameManager* gameManager, UIManager* uiManager);

	//		デストラクタ
	~GameClearManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

private:

	//		メッセージテクスチャパス
	const wchar_t* MESSAGE_TEXTURE_PATH = L"Resources/Texture/UI/GameClear/Messege.png";

	//		中心シェーダーVSパス
	const wchar_t* CENTER_SHADER_VS_PATH = L"Resources/Shader/UI/CenterShader/CenterShaderVS.cso";

	//		中心シェーダーGSパス
	const wchar_t* CENTER_SHADER_GS_PATH = L"Resources/Shader/UI/CenterShader/CenterShaderGS.cso";

	//		中心シェーダーPSパス
	const wchar_t* CENTER_SHADER_PS_PATH = L"Resources/Shader/UI/CenterShader/CenterShaderPS.cso";

private:

	//		UIマネージャーのインスタンスのポインタ
	UIManager* m_uiManager;

	//		ゲームマネージャーのインスタンスのポインタ
	GameManager* m_gameManager;

	//		メッセージのシェーダー描画
	std::unique_ptr<UIRenderManager> m_messageShader;

	ConstBuffer buffer;

	//		経過時間
	float m_elapsedTime;

	//		スケール
	float m_scale;

	//		移動量
	float m_move;
};