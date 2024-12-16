/*
* @file		TitleCameraFrontCut.h
* @brief	タイトルカメラのフロントカット
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "../ITitleCamera.h"

class TitleCameraManager;

class TitleCameraFrontCut : public ITitleCamera
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(titleCameraManager)	タイトルカメラマネージャーのインスタンスのポインタ
	*/
	TitleCameraFrontCut(TitleCameraManager* titleCameraManager);

	//		デストラクタ
	~TitleCameraFrontCut();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		終了処理
	void Finalize() override;

private:

	//		初期角度
	const float FIRST_RADIAN = 90.0f;

	//		最終角度
	const float END_RADIAN = 210.0f;

	//		ターゲット
	const DirectX::SimpleMath::Vector3 TARGET = { 0.0f, 4.0f, 0.0f };

private:


	//		経過時間
	float m_elapsedTime;

	//		タイトルカメラマネージャーのインスタンスのポインタ
	TitleCameraManager* m_titleCameraManager;
};