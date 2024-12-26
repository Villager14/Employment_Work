/*
* @file		PostEffectManager.h
* @brief	ポストエフェクトマネージャー
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

	//		コンストラクタ
	PostEffectManager();

	//		デストラクタ
	~PostEffectManager();

	//		初期化処理
	void Initialize(DirectX::XMVECTORF32 color, PostEffectFlag* flag);

	//		更新処理
	void Update(PostEffectFlag::Flag flag);

	//		描画処理
	void Render(PostEffectFlag::Flag flag);

	//		最終描画処理
	void RastRender(PostEffectFlag::Flag flag);

	//		終了処理
	void Finalize();

	//		ポストエフェクトの作成
	void CreatePostEffect(PostEffectFlag* flag);

	//		サンプラーの作製
	void CreateSampler();

	//		レンダーターゲットの変更
	ID3D11ShaderResourceView* ChangeRenderTarget(DX::RenderTexture* renderTarget,
		ID3D11DepthStencilView* depthStencil);

	//		レンダーターゲットを基に戻す
	void ResetRenderTarget();

	//		レンダーテクスチャの描画
	void RenderTextureView();

	//		メニューを開いている
	void MenuOpen() override;

	//		メニューを閉じている
	void MenuClose() override;

public:

	enum UIType
	{
		RastTexture,
		UITexture,
	};

private:

	//		ポストエフェクトの共通処理
	std::unique_ptr<PostEffectCommonProcess> m_commonProcess;

	//		スタンダードシェーダー
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

	//		サンプラー(一部を取り出す物)
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	ID3D11ShaderResourceView* m_shaderResourceView;

	//		ブラーの処理
	std::unique_ptr<Bler> m_bler;

	//		ポストエフェクト
	std::unordered_map<PostEffectFlag::Flag, std::unique_ptr<IPostEffect>> m_postEffectProcess;

	//		背景色
	DirectX::XMVECTORF32 m_backColor;

	//		背景描画色
	DirectX::XMVECTORF32 m_backRenderColor;

	//		オブジェクトに対するシェーダー
	std::unique_ptr<PostEffectObjectShader> m_objectShader;

	//		ポストエフェクトの情報
	std::unique_ptr<PostEffectInformation> m_information;

	//		メニューが開いているか判断する
	bool m_openMenuJudgement;

public:

	/*
	*	ポストエフェクトの情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	PostEffectInformation* GetInformation() { return m_information.get(); }

	/*
	*	スタンダードシェーダーを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader.get(); }

	/*
	*	ブラーの処理を受け取る
	*
	*	@return インスタンスのポインタ
	*/
	Bler* GetBler() { return m_bler.get(); }

	/*
	*	背景色を受け取る
	*
	*  @return 背景色
	*/
	DirectX::XMVECTORF32 GetBackColor() { return m_backColor; };

	/*
	*	描画背景色を受け取る
	*
	*	@return 描画背景色
	*/
	DirectX::XMVECTORF32 GetBackRenderColor() { return m_backRenderColor; }

	/*
	*	描画背景色を設定する
	*
	*	@param	(背景色) 色
	*/
	void SetBackRenderColor(DirectX::XMVECTORF32 color) { m_backRenderColor = color; }

	/*
	*	共通処理を受け取る
	*
	*	@return インスタンスのポインタ
	*/
	PostEffectCommonProcess* GetCommonProcess() { return m_commonProcess.get(); }

	/*
	*	オブジェクトシェーダーを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	PostEffectObjectShader* GetPostObjectShader() { return m_objectShader.get(); }

	/*
	*	シェーダーリソースビューを受け取る
	* 
	*	@return	ポインタ
	*/
	ID3D11ShaderResourceView* GetShaderTexture() { return m_shaderResourceView; }

	/*
	*	メニューが開いているか判断する
	* 
	*	@return true : 開いている　false : 開いていない
	*/
	bool GetMenuOpenJudgement() { return m_openMenuJudgement; }

	void SetShaderTexture(ID3D11ShaderResourceView* texture) { m_shaderResourceView = texture; }

	std::unordered_map<PostEffectFlag::Flag, std::unique_ptr<IPostEffect>>* GetPostEffectProcess() { return &m_postEffectProcess; }
};
