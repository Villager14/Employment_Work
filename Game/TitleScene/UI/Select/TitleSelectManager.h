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


#include "Library/Shader/UIRenderManager.h"

#include <unordered_map>

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

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;
		DirectX::SimpleMath::Vector2 scale;
	};

	enum State
	{
		PlayState,
		EndState,
		SettingState,
		ChangState,
		StartState
	};

	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
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
	void ChangeState(State state);

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

public:

	/*
	*	最大スケールを受け取る
	* 
	*	@return 大きさ
	*/
	const float GetMaxScale() { return MAX_SCALE; }

	/*
	*	最小スケールを受け取る
	* 
	*	@return 大きさ
	*/
	const float GetMinScale() { return MIN_SCALE; }

private:

	//		選択
	ITitleSelect* m_iState;

	//		状態の情報
	std::unordered_map<State, std::unique_ptr<ITitleSelect>> m_stateInformation;

	//		現在の状態
	State m_state;

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

	//		メニューを開いているかどうか
	bool m_menuJudgement;

	//		背景移動処理
	std::unique_ptr<BackGroundMove> m_backGroundMove;


	ConstBuffer m_constBuffer;

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_shader;
	
	//		シェーダーの情報
	std::unordered_map<UIType, UIInformation> m_shaderInformation;

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

	/*
	*	メニューを開いているかどうか受け取る
	* 
	*	@param	(judgement)	true : 開いている　false : 開いていない
	*/
	void SetMenuJudgement(bool judgement) { m_menuJudgement = judgement; }
};