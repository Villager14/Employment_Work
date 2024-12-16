/*
* @file		SelectionBar.h
* @brief	選択バー
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "Library/Shader/StandardShader.h"

#include "SelectionBarMoveProcess.h"

class SelectionBar
{
public:

	//		コンストラクタ
	SelectionBar();

	//		デストラクタ
	~SelectionBar();

	//		初期化処理
	void Initialize();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	/*
	*	上を選択したときの処理
	* 
	*	@param	(processingTime)	処理時間
	*/
	void UpSelect(float processingTime);

	/*
	*	下を選択したときの処理
	*
	*	@param	(processingTime)	処理時間
	*/
	void DownSelect(float processingTime);

private:

	enum UIType
	{
		Play,		//		プレイ
		End,		//		終了
		Setting,	//		設定
	};

public:

	//		タイトルプレイテクスチャパス
	const wchar_t* TITLE_PLAY_TEXTURE_PATH = L"Resources/Texture/TitleScene/Select/TitlePlay.png";

	//		タイトル終了テクスチャパス
	const wchar_t* TITLE_END_TEXTURE_PATH = L"Resources/Texture/TitleScene/Select/TitleEnd.png";

	//		タイトル終了テクスチャパス
	const wchar_t* TITLE_SETTING_TEXTURE_PATH = L"Resources/Texture/TitleScene/Select/TitleSetting.png";

	//		中心始点
	const DirectX::SimpleMath::Vector2 CENTER_POINT = { 0.0f,120.0f };

	//		下地点
	const DirectX::SimpleMath::Vector2 UNDER_POINT = { 0.0f, 200.0f };

	//		上地点
	const DirectX::SimpleMath::Vector2 UP_POINT = { 0.0f, 40.0f };

	//		最大スケール
	const float MAX_SCALE = 1.0f;

	//		最小スケール
	const float MIN_SCALE = 0.5f;

private:

	//		タイトルUIマネージャー
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

	//		選択バー移動処理
	std::unique_ptr<SelectionBarMoveProcess> m_selectionBarMoveProcess;

	//		中心タイプ
	UIType m_centerType;
};