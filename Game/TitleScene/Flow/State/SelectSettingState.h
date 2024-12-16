/*
* @file		SelectSettingState.h
* @brief	設定を選択した状態
* @author	Morita
* @date		2024/05/26
*/

#pragma once

#include "../ITitleSelect.h"

class TitleFlowManager;

class SelectSettingState : public ITitleSelect
{
public:

	/*
	*	コンストラクタ
	*
	*	@param	(titleFlowManager)	タイトル流れのインスタンスのポインタ
	*/
	SelectSettingState(TitleFlowManager* titleFlowManager);

	//		デストラクタ
	~SelectSettingState();

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