/*
* @file		SelectEndState.h
* @brief	終了を選択した状態
* @author	Morita
* @date		2024/05/26
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleFlowManager.h"

class TitleFlowManager;

class SelectEndState : public ITitleSelect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(titleFlowManager)	タイトル流れのインスタンスのポインタ
	*/
	SelectEndState(TitleFlowManager* titleFlowManager);

	//		デストラクタ
	~SelectEndState();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		終了処理
	void Finalize() override;

	//		シーンを切り替える処理
	void ChangeSceneProcess();

private:

	//		タイトルの流れのインスタンスのポインタ
	TitleFlowManager* m_titleFlow;

};