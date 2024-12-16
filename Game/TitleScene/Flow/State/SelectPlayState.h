/*
* @file		SelectPlayerState.h
* @brief	プレイを選択した状態
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleFlowManager.h"

class TitleFlowManager;

class SelectPlayState : public ITitleSelect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(titleFlowManager)	タイトル流れのインスタンスのポインタ
	*/
	SelectPlayState(TitleFlowManager* titleFlowManager);

	//		デストラクタ
	~SelectPlayState();

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