/*
* @file		TitleKeyGuidance.h
* @brief	タイトルのキーガイド
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "Library/Shader/StandardShader.h"


class TitleKeyGuidance
{
public:

	//		コンストラクタ
	TitleKeyGuidance();

	//		デストラクタ
	~TitleKeyGuidance();

	//		初期化処理
	void Initialize();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	/*
	*	上選択時の処理
	* 
	*	@param	(processingTime)	処理時間
	*/
	void UpSelect(float processingTime);

	/*
	*	下選択時の処理
	*
	*	@param	(processingTime)	処理時間
	*/
	void DownSelect(float processingTime);

private:

	enum UIType
	{
		Space,		//		スペース
		W,			//		W
		A,			//		A
	};

	enum CenterUIType
	{
		Not,
		Play,		//		プレイ
		End,		//		終了
		Setting,	//		設定
	};

private:

	//		Wのプレイ時座標
	const DirectX::SimpleMath::Vector2 W_PLAY = { 120.0f, 40.0f };

	//		スペースのエンド時座標
	const DirectX::SimpleMath::Vector2 SPACE_END = { 270.0f, 120.0f };

	//		スペースのプレイ時座標
	const DirectX::SimpleMath::Vector2 SPACE_PLAY = { 300.0f, 120.0f };

	//		スペースの設定時座標
	const DirectX::SimpleMath::Vector2 SPACE_SETTING = { 410.0f, 120.0f };

	//		Wのエンド時座標
	const DirectX::SimpleMath::Vector2 W_END = { 110.0f, 40.0f };

	//		Aの設定時座標
	const DirectX::SimpleMath::Vector2 A_SETTING = { 180.0f, 200.0f };

	//		最大スケール
	const float MAX_SCALE = 1.0f;
private:

	//		タイトルUIマネージャー
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

	//		中心のUIタイプ
	CenterUIType m_centerUIType;
};