/*
* @file		ClockTime.h
* @brief	UI時計の数字
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class ClockTime
{
public:

	//		コンストラクタ
	ClockTime();

	//		デストラクタ
	~ClockTime();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	* 
	*	@param	(elapsedTime)	経過時間
	*/
	void Update(float elapsedTime);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		アスペクト比
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		回転行列
		DirectX::SimpleMath::Vector4 number;			//		数字
	};

private:

	//		分(十の位)の座標minutes
	const DirectX::SimpleMath::Vector2 TEN_PLACE_MINUTES_POSITION = { 1060.0f, 560.0f };

	//		分(一の位)の座標
	const DirectX::SimpleMath::Vector2 ONE_PLACE_MINUTES_POSITION = { 1090.0f, 560.0f };

	//		秒(十の位)の座標
	const DirectX::SimpleMath::Vector2 TEN_PLACE_SECONDS_POSITION = { 1150.0f, 560.0f };

	//		秒(一の位)の座標
	const DirectX::SimpleMath::Vector2 ONE_PLACE_SECONDS_POSITION = { 1180.0f, 560.0f };

	//		最大描画時間(秒)
	const int MAX_TIME = 5999;

private:

	//		数字のシェーダー
	std::unique_ptr<UIRenderManager> m_shader;

	//		時間
	int m_time;

	//		コンストバッファ
	ConstBuffer buffer;
};
