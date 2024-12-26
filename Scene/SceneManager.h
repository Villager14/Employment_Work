/*
* @file		SceneManager.h
* @brief	シーンマネージャー
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include <unordered_map>

#include "Scene/IScene.h"

#include "Effect/PostEffect/PostEffectManager.h"

#include "SceneManagerInformation.h"

#include "Game/Menu/MenuManager.h"

#include "Library/Mouse/MouseKeyInput.h"
#include "Library/Keyboard/KeyboardManager.h"

class PlayScene;
class TitleScene;
class ResultScene;

class SceneManager
{
public:
	//		コンストラクタ
	SceneManager();

	//		デストラクタ
	~SceneManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		オブザーバーの追加
	void AddObserver();

public:

	enum SceneType
	{
		Title,
		Play,
		Result,
		Tutorial,
	};

private:

	//		シーン
	IScene* m_scene;

	//		メニューマネージャー
	std::unique_ptr<MenuManager> m_menuManager;

	//		シーンの情報
	std::unordered_map<SceneType, IScene*> m_sceneInformation;

	//		シーンタイプ
	SceneType m_sceneType;

	//		ポストエフェクトマネージャー
	std::unique_ptr<PostEffectManager> m_postEffectManager;

	//		マウスキー入力
	std::unique_ptr<MouseKeyInput> m_mouseKeyInput;

	//		キーボード入力
	std::unique_ptr<KeyboardManager> m_keyboardInput;
	
	//		シーンマネージャーの情報
	std::unique_ptr<SceneManagerInformation> m_information;

	//		プレイシーン
	std::unique_ptr<PlayScene> m_playScene;

	//		タイトルシーン
	std::unique_ptr<TitleScene> m_titleScene;

	//		リザルトシーン
	std::unique_ptr<ResultScene> m_resultScene;

public:

	/*
	*	シーンを切り替える
	* 
	*	@param	(type)	次のシーン
	*/
	void ChangeScene(SceneType type);

	/*
	*	シーンマネージャの情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	SceneManagerInformation* GetInformation() { return m_information.get(); }
};
