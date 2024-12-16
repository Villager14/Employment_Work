/*
* @file		ITitleCamera.h
* @brief	タイトルカメラマネージャー
* @author	Morita
* @date		2024/12/15
*/

#pragma once

class ITitleCamera
{
public:

	//		デストラクタ
	virtual ~ITitleCamera() = default;

	//		初期化処理
	virtual void Initialize() = 0;

	//		カメラの更新
	virtual void Update() = 0;

	//		終了処理
	virtual void Finalize() = 0;
};