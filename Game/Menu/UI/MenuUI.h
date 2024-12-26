/*
* @file		MenuUI.h
* @brief	メニューのUI
* @author	Morita
* @date		2024/12/18
*/

#pragma once

#include "Effect/UI/Menu/AboveUI/AboveUI.h"
#include "Effect/UI/Menu/Slider/Slider.h"

#include "../Collider/MenuColliderInformation.h"

#include "Tab/MenuTabUI.h"
#include "BackGround/MenuBackGround.h"
#include "MousePointer/MenuMousePointerUI.h"
#include "Title/MenuTitle.h"
#include "Slider/MenuSliderUI.h"
#include "GamePlay/MenuGamePlayUI.h"
#include "Audio/MenuAudioUI.h"
#include "Option/MenuOption.h"
#include "SummarizeColliderInformation/MenuSummarizeColliderInformation.h"

#include "../Observer/BackGroundUI/IMenuBackGroundUIObserver.h"
#include "../Observer/TabUI/IMenuTabUIObserver.h"
#include "../Observer/Mouse/IMenuMouseObserver.h"
#include "../Observer/SelectType/IMenuSelectTypeObserver.h"
#include "../Observer/Title/IMenuTitleUIObserver.h"
#include "../Observer/Icon/IMenuIconUIObserver.h"
#include "../Observer/Collider/IMenuColliderObserver.h"

#include "Library/Mouse/Observer/IMouseKeyInputObserver.h"

#include "Process/MenuSliderProcess.h"

class MenuUI : public IMenuBackGroundUIObserver,
			   public IMenuTabUIObserver,
			   public IMenuMouseObserver,
			   public IMenuSelectTypeObserver,
			   public IMenuTitleUIObserver,
			   public IMenuIconUIObserver,
			   public IMouseKeyInputObserver,
			   public IMenuColliderObserver
{
public:

	//		コンストラクタ
	MenuUI();

	//		デストラクタ
	~MenuUI();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	/*
	*	バーのスケールの変更
	*
	*	@param	(float scale)
	*/
	void BackGroundBarScale(float scale) override;

	/*
	*	メニューの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	void MenuMoveProcess(float move) override;

	/*
	*	タブUIの移動
	*
	*	@param	(move)	移動量(0~1)
	*/
	void TabMove(float move) override;

	/*
	*	タブを使うかどうか
	*
	*	@param	(bool) true : 使う false : 使わない
	*/
	void TabUseJudgement(float judgement) override;

	/*
	*	マウスのX座標の更新
	*
	*	@param	(x) x座標
	*/
	void MousePositionX(int x) override;

	/*
	*	マウスのY座標の更新
	*
	*	@param	(y) y座標
	*/
	void MousePositionY(int y) override;

	/*
	*	選択タイプ
	*
	*	@param	(type)　タイプ
	*/
	void SelectType(MenuUITaype::UIType type) override;

	/*
	*	タイトルの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	void TitleMoveProcess(float move) override;

	/*
	*	アイコンの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	void IconMoveProcess(float move) override;

	/*
	*	マウスの押した瞬間の処理
	*
	*	@param	(key)	押したキー
	*/
	void IsKeyPressed(KeyInputMouse::MouseList key) override;

	/*
	*	マウスの離した瞬間の処理
	*
	*	@param	(key)	離したキー
	*/
	void IsKeyReleased(KeyInputMouse::MouseList key) override;

	/*
	*	マウスの押し続けたの時の処理
	*
	*	@param	(key)	押し続けたキー
	*/
	void IsKeepPushing(KeyInputMouse::MouseList key) override;

	/*
	*	当たったUIのタイプ
	*
	*	@param	(type)	UIのタイプ
	*/
	void HitUIType(UISubType type) override;

private:

	//		上昇スクリプト
	std::unique_ptr<AboveUI> m_aboveUI;

	//		メニューTabUI
	std::unique_ptr<MenuTabUI> m_menuTabUI;

	//		メニューの背景UI
	std::unique_ptr<MenuBackGround> m_menuBackGround;

	//		マウスポインタUI
	std::unique_ptr<MenuMousePointerUI> m_mousePointer;

	//		タイトルUI
	std::unique_ptr<MenuTitle> m_titleUI;

	//		スライダー
	std::unique_ptr<Slider> m_slider;

	//		ゲームプレイ画面のUI
	std::unique_ptr<MenuGamePlayUI> m_gamePlay;
	
	//		オーディオ画面のUI
	std::unique_ptr<MenuAudioUI> m_menuAudio;

	//		オプション画面のUI
	std::unique_ptr<MenuOption> m_menuOption;

	//		メニューのスライダー処理
	std::unique_ptr<MenuSliderProcess> m_sliderProcess;

	//		当たり判定情報をまとめる
	std::unique_ptr<MenuSummarizeColliderInformation> m_summarizeColliderInformation;
public:

	/*
	*	当たり判定の情報
	* 
	*	@return メニューの当たり判定の情報のポインタ
	*/
	const std::vector<MenuColliderInformation>& GetColliderInformation() { return m_summarizeColliderInformation->GetInformation(); }

	/*
	*	スライダーの値を設定の送るオブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddSliderSettingValObserver(ISetSliderSettingValObserver* observer) { m_sliderProcess->AddSliderSettingValObserver(observer); }
};