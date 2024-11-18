/*
* @file		OptionSetting.h
* @brief	オプションの設定
* @author	Morita
* @date		2024/07/10
*/

#pragma once

#include "../IMenu.h"

#include "../MenuManager.h"

class MenuManager;

class OptionSetting : public IMenu
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(menuManager)	インスタンスのポインタ
	*/
	OptionSetting(MenuManager* menuManager);

	//		デストラクタ
	~OptionSetting();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

private:
	//		スライダーの座標１
	const DirectX::SimpleMath::Vector2 SLIDER_POSITION1 = { 200.0f, -100.0f };

	//		スライダーの座標２
	const DirectX::SimpleMath::Vector2 SLIDER_POSITION2 = { 200.0f, 50.0f };

	//		視野角の最大値
	const float FOV_MAX_VAL = 120.0f;

	//		視野角の最小値
	const float FOV_MIN_VAL = 70.0f;

	//		マウス感度最小値
	const float MOUSE_SENSITIVITY_MIN = 0.1f;

	//		マウス感度最大値
	const float MOUSE_SENSITIVITY_MAX = 10.0f;

private:

	//		メニューマネージャーのインスタンスのポインタ
	MenuManager* m_menuManager;

	//		タイトルの遷移時間
	float m_transitionTitleTime;

	//		大まかなメニューの遷移時間
	float m_transitionRoughTime;

	//		設定する部分のUIの遷移時間
	float m_transitionSettingUITime;

	//		初期遷移を行うかどうか判断する
	bool m_startJudgement;

	//		終了遷移を行うかどうか判断する
	bool m_endJudgement;

	//		閉めるかどうか
	bool m_menuCloseJudgement;

};