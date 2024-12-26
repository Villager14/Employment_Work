/*
* @file		MenuSliderProcess.h
* @brief	メニューのスライダーの処理
* @author	Morita
* @date		2024/12/25
*/

#pragma once

#include "Effect/UI/Menu/Slider/Slider.h"

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "../../Collider/MenuColliderInformation.h"

#include "../../Observer/SliderSettingObserver/SetSliderSettingValObserver.h"

class MenuSliderProcess
{
public:

	MenuSliderProcess(Slider* slider, AboveUI* aboveUI);

	~MenuSliderProcess();

	void Initilaize();

	void Update();

	void Finalize();

	/*
	*	当たったボタン
	*
	*	@param	(type)	当たったボタンタイプ
	*/
	void HitBunnton(UISubType type);

private:

	void SliserInformationUpdate();

	float SliderRatio();

	//		オーディオの更新
	void AudioUpdate();

	//		オプションの更新
	void OptionUpdate();

private:

	//		ノブの最大値
	const float KNOB_MAX_VAL = 561.0f;

	//		ノブの最小値
	const float KNOB_MIN_VAL = 81.0f;

	//		スライダーの最大値
	const float SLIDER_MAX_VAL = 590.0f;

	//		スライダーの最小値
	const float SLIDER_MIN_VAL = 95.0f;

private:

	//		マウスの座標X
	int m_mousePositionX;

	//		マウスの入力処理が行われているかどうか
	bool m_mouseInputJudgement;

	Slider* m_slider;

	AboveUI* m_aboveUI;

	//		スライダーが当たった
	AboveUI::UIType m_hitType;

	//		スライダータイプ
	Slider::UIType m_sliderType;

	//		設定オブザーバー
	std::unique_ptr<SetSliderSettingValObserver> m_settingObserver;

public:

	/*
	*	マウスの座標を設定する
	*
	*	@param	(x) x座標
	*/
	void SetMousePosition(int x) { m_mousePositionX = x; }

	/*
	*	マウスの入力処理が行われていないか
	*
	*	@param	(judgement)	true : 押している false : 押していない1
	*/
	void MouseInputJudgement(bool judgement) { m_mouseInputJudgement = judgement; }

	/*
	*	スライダーの値を設定の送るオブザーバーの追加
	* 
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddSliderSettingValObserver(ISetSliderSettingValObserver* observer) { m_settingObserver->AddObserver(observer); }
};