/*
* @file		TitlePostEffectManager.h
* @brief	タイトルポストエフェクトマネージャー
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Effect/PostEffect/PostEffectManager.h"

#include "../Observer/TitlePostEffectObserver/TitlePostEffectObserver.h"

#include "../Observer/FadeObserver/IFadeObserver.h"

class TitlePostEffectManager : public IFadeObserver
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(postEffectManager)	ポストエフェクトマネージャーのポインタ
	*/
	TitlePostEffectManager(PostEffectManager* postEffectManager);

	//		デストラクタ
	~TitlePostEffectManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	/*
	*	ポストエフェクトを使用するかどうか
	* 
	*	@param	(int)	フラグ番号
	*	return true : 使用する　false : 使用しない
	*/
	bool PostEffectUseJudgement(int postEffectFlag);

	/*
	*	ポストエフェクトの更新
	* 
	*	@param	(int)	フラグ番号	
	*/
	void PostEffectUpdate(int postEffectFlag);

	/*
	*	ポストエフェクトの描画処理
	*
	*	@param	(int)	フラグ番号
	*/
	void PostEffectRender(int postEffectFlag);

	//		ポストエフェクトのテクスチャ描画処理
	void PostEffectTextureRender();

	//		シーン変更フェードアウト
	void SceneEndFadeOut() override;

	//		フェードアウト
	void FadeOut() override;

	void Finalize();

private:

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_posteffectFlag;

	//		ポストエフェクトマネージャー
	PostEffectManager* m_postEffectManager;

	//		タイトルポストエフェクトオブザーバー
	std::unique_ptr<TitlePostEffectObserver> m_titlePostEffectObserver;

public:

	/*
	*	タイトルポストエフェクトオブザーバーを追加する
	* 
	*	@param	(observer)	オブザーバー
	*/
	void AddTitlePostEffectObserver(ITitlePostEffectObserver* observer) { m_titlePostEffectObserver->AddObserver(observer); };
};