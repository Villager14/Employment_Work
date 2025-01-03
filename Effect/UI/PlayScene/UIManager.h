/*
* @file		UIManager.h
* @brief	UIマネージャー
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/StandardShader.h"

#include "Game/PlayScene/Player/Observer/IPObserver.h"
#include "Game/PlayScene/Player/Observer/SpeedObserver/IPSpeedObserver.h"

class ClockManager;
class CoolTime;
class GameOverManager;
class GameClearManager;
class SpeedLine;
class GameStart;
class CountDown;

class UIManager : public IPObserver, public IPSpeedObserver
{
public:
	//		コンストラクタ
	UIManager(GameManager* gameManager);

	//		デストラクタ
	~UIManager();

	//		初期処理
	void Initialize();

	//		生成
	void Generation();

	//		更新処理
	void Update();

	//		終了処理
	void Finalize();

	void FrontRender();

	void BackRender();

	//		UIテクスチャの作製
	void CreateStandardUITexture();

	
	/*
	*	ダッシュクールタイム
	* 
	*	@param	(coolTime)	クールタイム
	*/
	void DashCoolTime(float coolTime) override;

	/*
	*	現在プレイヤーの速度
	* 
	*	@param	(speed)	速度
	*/
	void NowSpeed(float speed) override;

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
		GameStartTimeLimit,		//		ゲームスタートタイムリミット
		GameStartTimeTen		//		ゲームスタートタイムリミットの点
	}; 

public:

	//		時計背景座標
	const DirectX::SimpleMath::Vector2 CLOCK_BACK_GROUND_POSITION = { 480.0f, 200.0f };

	//		時計時間背景座標
	const DirectX::SimpleMath::Vector2 CLOCK_BACK_TIME_GROUND_POSITION = { 539.0f, 0.0f };

	//		次の状態誘導座標
	const DirectX::SimpleMath::Vector2 NEXT_INDCCTION = { 0.0f, 200.0f };

	//		メッセージバー上の座標
	const DirectX::SimpleMath::Vector2 MESSAGE_BER_UP = { 0.0f, 13.0f };

	//		メッセージバー下の座標
	const DirectX::SimpleMath::Vector2 MESSAGE_BER_DOWN = { 0.0f, -13.0f };

	//		時計背景テクスチャパス
	const wchar_t* CLOCK_BACK_GROUND_PAHT = L"Resources/Texture/UI/Clock/ClockBackGround.png";

	//		クロック背景テクスチャパス
	const wchar_t* CLOCK_COLON_TEXTURE_PATH = L"Resources/Texture/UI/Clock/ClockColon.png";

	//		クールタイム背景テクスチャパス
	const wchar_t* COOL_TIME_BACK_TEXTURE_PATH = L"Resources/Texture/UI/CoolTime/CoolTimeBack.png";

	//		ゲームオーバーテクスチャパス
	const wchar_t* GAME_OVER_TEXTURE_PATH = L"Resources/Texture/UI/GameOver/GameOver.png";

	//		コンテニューテクスチャパス
	const wchar_t* CONTINUE_TEXTURE_PATH = L"Resources/Texture/UI/GameOver/Continue.png";

	//		ボタンテクスチャパス
	const wchar_t* BUTTON_TEXTURE_PATH = L"Resources/Texture/UI/GameOver/button.png";

	//		スクリーンレイテクスチャパス
	const wchar_t* SCREEN_RAY_TEXTURE_PATH = L"Resources/Texture/UI/ScreenRay/ScreenRay.png";

	//		メッセージバーテクスチャパス
	const wchar_t* MESSAGE_BAR_TEXTURE_PATH = L"Resources/Texture/UI/GameClear/messegeBer.png";

	//		タイムリミットテクスチャパス
	const wchar_t* TIME_LIMIT_TEXTURE_PATH = L"Resources/Texture/UI/GameStart/TimeLimit.png";

	//		点テクスチャパス
	const wchar_t* TEN_TEXTURE_PATH = L"Resources/Texture/UI/GameStart/Ten.png";


	//		メッセージ背景のファイルパス
	const wchar_t* MESSAGE_BACK_FILE_PATH = L"Resources/Texture/UI/GameClear/messegeBack.png";

private:
	//		時計の背景
	std::unique_ptr<ClockManager> m_clockManager;

	//		クールタイム
	std::unique_ptr<CoolTime> m_coolTime;

	//		カウントダウン
	std::unique_ptr<CountDown> m_countDonw;
		
	//		ゲームオーバー
	std::unique_ptr<GameOverManager> m_gameOver;

	//		スピードライン
	std::unique_ptr<SpeedLine> m_speedLine;

	//		ゲームスタート
	std::unique_ptr<GameStart> m_gameStart;

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

	/*
	*	ゲームマネージャーを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	GameManager* GetGameManager() { return m_gameManager; }
};