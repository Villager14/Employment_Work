/*
* @file		TitleSelectManager.h
* @brief	タイトルの選択マネージャー
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include "ITitleSelect.h"

#include "State/SelectPlayState.h"

#include "Game/PlayScene/UIManager/UIRender.h"

class SelectPlayState;

class TitleSelectManager
{
public:

	enum UIType
	{
		Play,
		End,
		Setting
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

public:

	/*
	*	プレイ選択状態を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	SelectPlayState* GetSelectPlayState() { return m_selectPlayState.get(); }

private:

	//		中心始点
	const DirectX::SimpleMath::Vector2 CENTER_POINT = { 0.0f,120.0f };

	//		下地点
	const DirectX::SimpleMath::Vector2 UNDER_POINT = { 0.0f, 200.0f };

	//		上地点
	const DirectX::SimpleMath::Vector2 UP_POINT = { 0.0f, 40.0f };

private:

	//		UIマネージャー
	std::vector<std::unique_ptr<UIRender>> m_uiRender;

	//		UIの座標
	std::vector<DirectX::SimpleMath::Vector2> m_uiPosition;

	//		UIのサイズ
	std::vector<DirectX::SimpleMath::Vector2> m_uiSize;

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


};