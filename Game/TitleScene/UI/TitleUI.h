/*
* @file		TitleUI.h
* @brief	タイトルのUI
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "Library/Shader/StandardShader.h"

#include "Effect/UI/TitleScene/BackGroundMove.h"

#include "Effect/UI/TitleScene/SelectionBar/SelectionBar.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "../Observer/TitleUIObserver/ITitleUIObserver.h"

#include "Effect/UI/TitleScene/KeyGuidance/TitleKeyGuidance.h"

#include "Effect/UI/TitleScene/Fade/FadeUI.h"

#include "../Observer/FadeObserver/IFadeObserver.h"

class TitleUI : public ITitleUIObserver, public IFadeObserver
{
public:

	//		コンストラクタ
	TitleUI();

	//		デストラクタ
	~TitleUI();

	//		初期化処理
	void Initalize();

	//		更新処理
	void Update();

	/*
	*	描画処理
	* 
	*	@param	(postEffectType)	ポストエフェクトのタイプ
	*/
	void Render(int postEffectType);

	//		終了処理
	void Finalize();

	/*
	*	下への移動処理
	* 
	*	@param	(processingTime)	処理時間
	*/
	void DownSelect(float processingTime) override;

	/*
	*	上への移動処理
	*
	*	@param	(processingTime)	処理時間
	*/
	void UpSelect(float processingTime) override;

	//		シーン終了フェードアウト
	void SceneEndFadeOut() override;

	//		フェードアウト
	void FadeOut() override;

private:

	//		生成
	void Generation();

private:

	//		UIの種類
	enum TitleUIType
	{
		TitleRogo,	//		タイトルロゴ
	};

private:

	//		タイトルロゴの座標
	const DirectX::SimpleMath::Vector2 TITLE_POINT = { 0.0f, -170.0f };

	//		最大スケール
	const float MAX_SCALE = 1.0f;

	//		最小スケール
	const float MIN_SCALE = 0.5f;

private:

	//		タイトルUIマネージャー
	std::unique_ptr<StandardShader<TitleUIType>> m_standardShader;

	//		背景処理
	std::unique_ptr<BackGroundMove> m_backGround;

	//		選択バー
	std::unique_ptr<SelectionBar> m_selectionBar;

	//		キーガイダンス
	std::unique_ptr<TitleKeyGuidance> m_keyGuidance;

	//		UI以外を消すフェード処理
	std::unique_ptr<FadeUI> m_fadeUI;
};