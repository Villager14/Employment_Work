/*
* @file		TitleCameraFrontAscendingCut.h
* @brief	タイトルカメラのフロント上昇カット
* @author	Morita
* @date		2024/12/15
*/

#pragma once

#include "../ITitleCamera.h"

class TitleCameraManager;

class TitleCameraFrontAscendingCut : public ITitleCamera
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(titleCameraManager)	タイトルカメラマネージャーのインスタンスのポインタ
	*/
	TitleCameraFrontAscendingCut(TitleCameraManager* titleCameraManager);

	//		デストラクタ
	~TitleCameraFrontAscendingCut();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		終了処理
	void Finalize() override;

private:

	//		初期座標
	const DirectX::SimpleMath::Vector3 FIRST_POSITION = { 0.0f, 1.0f, -3.0f };

	//		最終座標
	const DirectX::SimpleMath::Vector3 END_POSITION = { 0.0f, 3.7f, -3.0f };

	//		初期ターゲット
	const DirectX::SimpleMath::Vector3 FIRST_TARGET = { 0.0f, 1.0f, 0.0f };

	//		最終ターゲット
	const DirectX::SimpleMath::Vector3 END_TARGET = { 0.0f, 3.7f, 0.0f };

private:


	//		経過時間
	float m_elapsedTime;

	//		タイトルカメラマネージャーのインスタンスのポインタ
	TitleCameraManager* m_titleCameraManager;
};