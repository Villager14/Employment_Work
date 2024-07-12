/*
* @file		MenuManager.h
* @brief	メニューのマネージャー
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include <unordered_map>

#include "IMenu.h"

#include "State/AudioSetting.h"
#include "State/MenuStart.h"
#include "State/OptionSetting.h"
#include "State/EndSetting.h"
#include "State/MenuClose.h"


#include "MenuInformation.h"

class MenuManager
{
public:
	//		コンストラクタ
	MenuManager();

	//		デストラクタ
	~MenuManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();
	
	//		メニューの背景の描画
	void MenuBackRneder();

	//		四角の当たり判定
	bool BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max);

public:
	enum MenuType
	{
		Start,
		Audio,
		Option,
		GamePlay,
		Close,

		Empty,
	};

private:

	//		現在のタイプ
	MenuType m_type;

	//		次の状態を設定する
	MenuType m_selectUI;

	//		現在の状態
	IMenu* m_state;

	//		メニューの状態の情報
	std::unordered_map<MenuType, std::unique_ptr<IMenu>> m_menuStateInformation;

	//		選択UI
	AboveUI::UIType m_rangeUI;

	//		スライダーを使っているUIの種類
	AboveUI::UIType m_slideUIType;

	//		メニューを開いているかどうか
	bool *m_menuJudgement;

	//		初めて音楽メニューを開いているかどうか
	bool m_firstAudioMenuJudgement;

	//		メニューの情報
	std::unique_ptr<MenuInformation> m_information;

public:

	/*
	*	メニューの情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	MenuInformation* GetInformation() { return m_information.get(); }

	/*
	*	大まかなメニューの描画
	* 
	*	@param	(transitionTime)	遷移時間
	*/
	void RoughMenuViwe(float transitionTime);

	//		選択したメニューの描画
	void MenuSelectView();

	/*
	*	状態の切り替え
	* 
	*	@param	(type)	状態
	*/
	void ChangState(MenuType type);

	//		メニューのESCボタンで閉じる処理
	bool MenuEscCloseProcess();

	/*
	*	選択したかどうか
	* 
	*	@param	(type)	選択しないメニューの種類
	*/
	bool ButtonCollider(MenuType type);

	/*
	*	UIの遷移処理
	* 
	*	@param	(transitionTime1)	遷移時間１
	*	@param	(transitionTime2)	遷移時間２
	*	@param	(transitionTime3)	遷移時間３
	*	@param	(startJudgement)	スタートしているかどうか判断する
	*	@param	(endJudgement)		終わらせるかどうか判断する
	*	@param	(moveJudgement)		遷移時間３を動かすか判断する
	*/
	bool Transition(float* transitionTime1, float* transitionTime2, float* transitionTime3,
		bool *startJudgement, bool endJudgement, bool moveJudgement);

	/*
	*	スライダーの処理
	* 
	*	@param	(type)	種類
	*/
	void SlideProcess(AboveUI::UIType type);

	/*
	*	イージング関数通常UI用
	* 
	*	@param	(time)	時間
	*/
	float EasingIcon(float time) { return 1.0f - pow(1.0f - time, 3.0f); }

	/*
	*	イージング関数背景用
	* 
	*	@param	(time) 時間
	*/
	float EasingBackUI(float time) {
		if (time == 1.0f)
		{
			return 1.0f;
		}
		else
		{
			return 1.0f - pow(2.0f, -10.0f * time);
		}
	}

	/*
	*	メニューを開いているかを設定する
	*	
	*	@param	true : 開いている false : 開いていない
	*/
	void SetMenuJudgement(bool* judgement) { m_menuJudgement = judgement; }

	/*
	*	メニューを開いているかを受け取る
	* 
	*	@param	true : 開いている false : 開いていない
	*/
	bool* GetMenuJudgement() { return m_menuJudgement; }

	/*
	*	Audioメニューをメニューを開いた時一度だけ行う処理を受け取る
	* 
	*	@retun	true : 行う false : 行わない
	*/
	bool GetFirstAudioMenuJudgement() { return m_firstAudioMenuJudgement; }

	/*
	*	Audioメニューをメニューを開いた時一度だけ行う処理を設定する
	*
	*	@param	(judgement)	true : 行う false : 行わない
	*/
	void SetFirstAudioMenuJudgement(bool judgement) { m_firstAudioMenuJudgement = judgement; }
};