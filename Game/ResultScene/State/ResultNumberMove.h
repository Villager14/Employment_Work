/*
* @file		ResultNumberMove.h
* @brief	リザルト数字移動処理
* @author	Morita
* @date		2024/05/29
*/

#pragma once

#include "../ResultManager.h"

#include "../IResultManager.h"

class ResultManager;

class ResultNumberMove : public IResultManager
{
public:
	
	/*
	*	コンストラクタ
	* 
	*	@param	(resultManager)	リザルトマネージャーのインスタンスのポインタ
	*/
	ResultNumberMove(ResultManager* resultManager);

	//		デストラクタ
	~ResultNumberMove();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;
private:

	//		リザルトマネージャー
	ResultManager* m_resultManager;

	float m_time;
};