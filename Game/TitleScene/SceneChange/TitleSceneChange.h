/*
* @file		TitleSceneChange.h
* @brief	タイトルのシーン変更
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "Scene/SceneManager.h"

#include "../Observer/TitlePostEffectObserver/ITitlePostEffectObserver.h"

#include "../Observer/GameExitObserver/ITitleGameExitObserver.h"

class TitleSceneChange : public ITitlePostEffectObserver,
						 public ITitleGameExitObserver
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(sceneManager)	シーンマネージャーのインスタンスのポインタ
	*/
	TitleSceneChange(SceneManager* sceneManager);

	//		デストラクタ
	~TitleSceneChange();

	//	フェードイン
	void FadeIn() override;

	//		フェードアウト
	void FadeOut() override;

	//		ゲーム終了
	void GameExit() override;
private:

	//		シーンマネージャー
	SceneManager* m_sceneManager;
};