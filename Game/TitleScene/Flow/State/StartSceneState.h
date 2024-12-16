/*
* @file		ChangeSceneState.h
* @brief	シーン切り替えをした状態
* @author	Morita
* @date		2024/05/27
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleFlowManager.h"

class StartSceneState : public ITitleSelect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(titleFlowManager)	タイトル流れのインスタンスのポインタ
	*/
	StartSceneState(TitleFlowManager* titleFlowManager);

	//		デストラクタ
	~StartSceneState();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		終了処理
	void Finalize() override;

private:

	//		タイトルの流れのインスタンスのポインタ
	TitleFlowManager* m_titleFlow;
};