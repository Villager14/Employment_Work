/*
* @file		TitlePlayer.cpp
* @brief	タイトルプレイヤーの処理
* @author	Morita
* @date		2024/12/13
*/

#pragma once

#include "Library/Animation/AnimationManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "../Observer/TitlePlayerAnimationObserver/ITitlePlayerAnimationObserver.h"

#include "Effect/PostEffect/PostEffectObjectShader.h"

class TitlePlayer : public ITitlePlayerAnimationObserver
{
public:

	//		コンストラクタ
	TitlePlayer();

	//		デストラクタ
	~TitlePlayer();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	/*
	*	描画処理
	* 
	*	@param	(flag)	ポストエフェクトフラグ
	*/
	void Render(PostEffectFlag::Flag flag, 
				PostEffectObjectShader* postEffectObjectShader);

	//		終了処理
	void Finalize();

	//		プレイ時のアニメーション
	void PlayAnimation() override;

	//	設定時のアニメーション
	void SettingAnimation() override;

	//	終了時のアニメーション
	void ExitAnimation() override;
private:

	//		プレイヤーアニメーション
	std::unique_ptr<AnimationManager> m_playerAnimation;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;
};