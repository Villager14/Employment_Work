/*
* @file		TitleCameraBackCut.cpp
* @brief	タイトルカメラの背景カット
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "../ITitleCamera.h"

class TitleCameraManager;

class TitleCameraBackCut : public ITitleCamera
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(titleCameraManager)	タイトルカメラマネージャーのインスタンスのポインタ
	*/
	TitleCameraBackCut(TitleCameraManager* titleCameraManager);

	//		デストラクタ
	~TitleCameraBackCut();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		終了処理
	void Finalize() override;

private:

	//		初期角度
	const float FIRST_RADIAN = 70.0f;

	//		最終角度
	const float END_RADIAN = -100.0f;

	//		初期ターゲット
	const DirectX::SimpleMath::Vector3 FIRST_TARGET = { 0.0f, 1.0f, 0.0f };

	//		最終ターゲット
	const DirectX::SimpleMath::Vector3 END_TARGET = { 0.0f, 3.5f, 0.0f };

private:


	//		経過時間
	float m_elapsedTime;

	//		タイトルカメラマネージャーのインスタンスのポインタ
	TitleCameraManager* m_titleCameraManager;
};