/*
* @file		TitleCameraFrontOverHeadCut.h
* @brief	タイトルカメラの頭上カット
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "../ITitleCamera.h"

class TitleCameraManager;

class TitleCameraFrontOverHeadCut : public ITitleCamera
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(titleCameraManager)	タイトルカメラマネージャーのインスタンスのポインタ
	*/
	TitleCameraFrontOverHeadCut(TitleCameraManager* titleCameraManager);

	//		デストラクタ
	~TitleCameraFrontOverHeadCut();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		終了処理
	void Finalize() override;

private:

	//		初期座標
	const DirectX::SimpleMath::Vector3 FIRST_POSITION = { 0.0f, 5.0f, -0.1f };

	//		最終座標
	const DirectX::SimpleMath::Vector3 END_POSITION = { 0.0f, 8.0f, -0.1f };

	//		初期ターゲット
	const DirectX::SimpleMath::Vector3 TARGET = { 0.0f, 4.0f, 0.0f };

private:


	//		経過時間
	float m_elapsedTime;

	//		タイトルカメラマネージャーのインスタンスのポインタ
	TitleCameraManager* m_titleCameraManager;
};