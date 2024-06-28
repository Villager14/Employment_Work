/*
* @file		TitleSelectManager.h
* @brief	タイトルの選択マネージャー
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include "ITitleSelect.h"

#include "State/SelectPlayState.h"
#include "State/SelectEndState.h"
#include "State/SelectSettingState.h"
#include "State/ChangeSceneState.h"
#include "State/StartSceneState.h"

#include "Game/PlayScene/UIManager/UIRender.h"

#include "Game/TitleScene/UI/BackGroundMove.h"

#include "Game/PlayScene/UIManager/Fade/FadeRender.h"

#include "../TVOFEffec.h"

class SelectPlayState;
class SelectEndState;
class SelectSettingState;
class ChangeSceneState;
class StartSceneState;

class TitleSelectManager
{
public:

	enum UIType
	{
		Play,
		End,
		Setting,
		TitleRogo
	};


public:

	//		コンストラクタ
	TitleSelectManager();

	//		デストラクタ
	~TitleSelectManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		キー入力
	void InputKey();

	/*
	*	状態を変更する
	*
	*	@param	(state)	状態
	*/
	void ChangeState(ITitleSelect* state);

	/*
	*	中心から上への処理
	* 
	*	@bool (direction)	true : 上へ移動する false : 中心へ移動する
	*/
	void CentreUP(bool direction, float time, UIType type);

	/*
	*	中心から下への処理
	* 
	*	@bool (direction)	true : 下へ移動する false : 中心へ移動する
	*/
	void CenterUnder(bool direction, float time, UIType type);

	/*
	*	中心から下への処理
	*
	*	@bool (direction)	true : 下へ移動する false : 中心へ移動する
	*/
	void UPUnder(bool direction, float time, UIType type);


	/*
	*	UIを追加する
	* 
	*	@param	(path)		テクスチャファイルパス
	*	@param	(position)	座標
	*	@param	(size)		サイズ
	*/
	void AddRenderUI(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size);

private:

	//		選択
	ITitleSelect* m_state;

	//		プレイ状態
	std::unique_ptr<SelectPlayState> m_selectPlayState;

	//		終了状態
	std::unique_ptr<SelectEndState> m_selectEndState;

	//		設定状態
	std::unique_ptr<SelectSettingState> m_selectSettingState;

	//		シーンを切り替える状態
	std::unique_ptr<ChangeSceneState> m_changeSceneState;

	//		スタート状態
	std::unique_ptr<StartSceneState> m_startSeceneState;
public:

	/*
	*	プレイ選択状態を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	SelectPlayState* GetSelectPlayState() { return m_selectPlayState.get(); }

	/*
	*	終了選択状態を受け取る
	*
	*	@return インスタンスのポインタ
	*/
	SelectEndState* GetSelectEndState() { return m_selectEndState.get(); }
	
	/*
	*	設定状態を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	SelectSettingState* GetSelectSettingState() { return m_selectSettingState.get(); }

	/*
	*	シーンを切り替える状態を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	ChangeSceneState* GetChangeSceneState() { return m_changeSceneState.get(); }

private:

	//		中心始点
	const DirectX::SimpleMath::Vector2 CENTER_POINT = { 0.0f,120.0f };

	//		下地点
	const DirectX::SimpleMath::Vector2 UNDER_POINT = { 0.0f, 200.0f };

	//		上地点
	const DirectX::SimpleMath::Vector2 UP_POINT = { 0.0f, 40.0f };

	//		移動速度
	const float MOVE_SPEED = 7.0f;

	//		最大スケール
	const float MAX_SCALE = 1.0f;

	//		最小スケール
	const float MIN_SCALE = 0.5f;

	//		背景移動処理
	std::unique_ptr<BackGroundMove> m_backGroundMove;

private:

	//		テレビ削除エフェクト
	std::unique_ptr<TVOFEffec> m_tvOffEffect;

	//		UIマネージャー
	std::vector<std::unique_ptr<UIRender>> m_uiRender;

	//		UIの座標
	std::vector<DirectX::SimpleMath::Vector2> m_uiPosition;

	//		UIのサイズ
	std::vector<DirectX::SimpleMath::Vector2> m_uiSize;

	//		描画順を設定する
	std::vector<int> m_drawOder;

	//		キー入力があったかどうか
	bool m_inputKey;

	//		移動方向
	bool m_direction;

	//		スクロールの値
	int m_scrollWheeel;

	//		シーンを変更するかどうか
	bool m_changeSceneJudgement;

	//		フェード
	std::unique_ptr<FadeRender> m_fade;

public:

	/*
	*	座標を設定する
	* 
	*	@parma	(position)	座標
	*	@param	(type)		UIのタイプ
	*/
	void SetUIPosition(const DirectX::SimpleMath::Vector2& position, UIType type) { m_uiPosition[type] = position; }

	/*
	*	UI座標を設定する
	* 
	*	@return 座標
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetUIPosition() { return m_uiPosition; }

	/*
	*	サイズを設定する
	*
	*	@parma	(size)	サイズ
	*	@param	(type)	UIのタイプ
	*/
	void SetUISize(const DirectX::SimpleMath::Vector2& size, UIType type) { m_uiSize[type] = size; }

	/*
	*	UIサイズを設定する
	*
	*	@return サイズ
	*/
	const std::vector<DirectX::SimpleMath::Vector2>& GetUISize() { return m_uiSize; }

	/*
	*	中心ポイントを受け取る
	* 
	*	@return 中心ポイント
	*/
	const DirectX::SimpleMath::Vector2& GetCenterPoint() { return CENTER_POINT; }

	/*
	*	下ポイントを受け取る
	*
	*	@return 下ポイント
	*/
	const DirectX::SimpleMath::Vector2& GetUnderPoint() { return UNDER_POINT; }

	/*
	*	上ポイントを受け取る
	*
	*	@return 上ポイント
	*/
	const DirectX::SimpleMath::Vector2& GetUPPoint() { return UP_POINT; }

	/*
	*	キー入力があるかどうか受け取る
	* 
	*	@return true : キー入力がある false : キー入力がない
	*/
	bool GetKeyInput() { return m_inputKey; }

	/*
	*	キー入力があるかどうか受け取る
	*
	*	@param	(judgement) true : キー入力がある false : キー入力がない
	*/
	void SetKeyInput(bool judgement) { m_inputKey = judgement; }

	/*
	*	移動方向を受け取る
	*
	*	@return true : 上 false : 下
	*/
	bool GetDirection() { return m_direction; }

	/*
	*	移動方向受け取る
	*
	*	@param	(direction) true : 上 false : 下
	*/
	void SetDirection(bool direction) { m_direction = direction; }

	/*
	*	移動速度を受け取る
	* 
	*	@return 移動速度
	*/
	float GetMoveSpeed() { return MOVE_SPEED; }

	/*
	*	シーンを切り替えるかどうか判断する
	*
	*	@param	(judgement)	true : 切り替える false : 切り替えない
	*/
	void SetChangeSceneJudgement(bool judgement) { m_changeSceneJudgement = judgement; }


	/*
	*	シーンを切り替えるかどうか判断する
	* 
	*	@return true : 切り替える false : 切り替えない
	*/
	bool GetChangeScnenJudgemnet() { return m_changeSceneJudgement; }


	/*
	*	フェードの描画
	*
	*	@param	(time)	時間
	*/
	void FadeViewProcess(float time) { m_fade->Render(time); }
};