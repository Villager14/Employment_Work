/*
* @file		UIManager.h
* @brief	UIマネージャー
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Fade/FadeIn.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/StandardShader.h"

class ClockManager;
class CoolTime;
class GameOverManager;
class GameClearManager;

class UIManager
{
public:
	//		コンストラクタ
	UIManager(PlayerInformation* playerInformation, GameManager* gameManager);

	//		デストラクタ
	~UIManager();

	//		初期処理
	void Initialize();

	//		更新処理
	void Update();

	void FrontRender();

	void BackRender();

	//		UIテクスチャの作製
	void CreateStandardUITexture();

public:

	enum UIType
	{
		ClockBackGround,		//		時計の背景
		ClockColon,				//		時計のコロン
		CloolTimeBackGround,	//		クールタイムの背景
		GameOver,				//		ゲームオーバー
		GameOverContinue,		//		ゲームオーバーのコンティニュー
		NextInduction,			//		次の状態の誘導
		ScreenRay,				//		スクリーンのレイ
		GameClearBarUnder,		//		ゲームクリアのバー
		GameClearBarUp,			//		ゲームクリアのバー		
		GameClearBackGround,	//		ゲームクリアの背景
	}; 

private:
	//		時計の背景
	std::unique_ptr<ClockManager> m_clockManager;

	//		クールタイム
	std::unique_ptr<CoolTime> m_coolTime;

	//		フェード
	std::unique_ptr<FadeIn> m_fadeIn;
		
	//		ゲームオーバー
	std::unique_ptr<GameOverManager> m_gameOver;

	//		プレイヤーの情報を受け取る
	PlayerInformation* m_playerInformation;

	//		ゲームマネージャー
	GameManager* m_gameManager;

	//		ゲームクリアマネージャー
	std::unique_ptr<GameClearManager> m_clearManager;

	//		スタンダードシェーダー
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

public:

	/*
	*	スタンダードシェーダーを受け取る
	* 
	*	@return スタンダードシェーダーを受け取る
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader.get(); }

};