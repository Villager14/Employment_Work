/*
* @file		ConcentrationLineManager.h
* @brief	集中線のマネージャー
* @author	Morita
* @date		2024/06/17
*/

#pragma once

#include "../ConcentrationLineShader.h"

class ConcentrationLineManager
{
public:

	//		コンストラクタ
	ConcentrationLineManager();

	//		デストラクタ
	~ConcentrationLineManager();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	* 
	*	@param	(gameManager)	ゲームマネージャーのインスタンスのポインタ
	*/
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:

	//		集中線シェーダー
	std::unique_ptr<ConcentrationLineShader> m_concentrationLineShader;

	//		経過時間
	float m_elapsedTime;

	//		移動量
	float m_move;

	//		更新時間
	float m_updateTime;
};