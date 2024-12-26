/*
* @file		SetSliderSettingValObserver.cpp
* @brief	スライダーの値を設定に送るオブザーバー
* @author	Morita
* @date		2024/12/26
*/

#pragma once

#include "ISetSliderSettingValObserver.h"

class SetSliderSettingValObserver
{
public:

	//		コンストラクタ
	SetSliderSettingValObserver();

	//		デストラクタ
	~SetSliderSettingValObserver();

	/*
	*	オブザーバーの追加
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddObserver(ISetSliderSettingValObserver* observer);

	/*
	*	オブザーバーの削除
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void DeleteObserver(ISetSliderSettingValObserver* observer);

	/*
	*	視野角の値を受け取る
	*
	*	@param	(val)　視野の割合
	*/
	void SetFov(float val);

	/*
	*	マウス感度を受け取る
	*
	*	@param	(val)　感度の割合
	*/
	void SetMouseSensitivity(float val) ;


	//		全削除
	void Dalete();

private:

	std::vector<ISetSliderSettingValObserver*> m_observer;

};