/*
* @file		MenuInformation.h
* @brief	メニューの情報
* @author	Morita
* @date		2024/07/12
*/

#pragma once

#include "pch.h"

#include "Library/Shader/StandardShader.h"
#include "UI/AboveUI.h"
#include "UI/Slider.h"
#include "UI/MenuSelect.h"

class MenuInformation
{
public:
	//		コンストラクタ
	MenuInformation()
	{
		//		スタンダードシェーダーの生成
		m_standardShader = std::make_unique<StandardShader<UIType>>();

		//		上昇UIの生成
		m_aboveUI = std::make_unique<AboveUI>();

		//		スライダーUIの生成
		m_slider = std::make_unique<Slider>();

		//		メニュー選択UIの生成
		m_menuSelect = std::make_unique<MenuSelect>();
	}

	//		デストラクタ
	~MenuInformation() {}

	void Initialzie()
	{
		//		スタンダードシェーダーの初期化処理
		m_standardShader->Initialize();

		m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png",
			{ 0.0f, 13.0f }, { 0.0f, 1.0f }, UIType::Bar1);
		m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBer.png",
			{ 0.0f, -13.0f }, { 0.0f, 1.0f }, UIType::Bar2);
		m_standardShader->CreateUIInformation(L"Resources/Texture/UI/GameClear/messegeBack.png",
			{ 0.0f, 0.0f }, { 0.0f, 1.0f }, UIType::BackGround);

		//		上昇UIの初期化
		m_aboveUI->Initialize();

		//		スライダーUIの初期化
		m_slider->Initialize();

		//		メニュー選択UIの初期化
		m_menuSelect->Initialize();

	}
	


public:
	//		音楽タイトルの座標
	const DirectX::SimpleMath::Vector2 AUDIO_TITLE_POSITION_MIN = { 119.0f, 106.0f };
	const DirectX::SimpleMath::Vector2 AUDIO_TITLE_POSITION_MAX = { 400.0f, 210.0f };

	//		オプションタイトルの座標
	const DirectX::SimpleMath::Vector2 OPTION_TITLE_POSITION_MIN = { 119.0f, 227.0f };
	const DirectX::SimpleMath::Vector2 OPTION_TITLE_POSITION_MAX = { 400.0f, 329.0f };

	//		終了タイトルの座標
	const DirectX::SimpleMath::Vector2 GAMEPLAY_TITLE_POSITION_MIN = { 119.0f, 347.0f };
	const DirectX::SimpleMath::Vector2 GAMEPLAY_TITLE_POSITION_MAX = { 400.0f, 452.0f };

	//		遷移速度
	const float TRANSITION_SPEED = 3.0f;

	//		メニューの速度
	const float MENU_SPEED = 2.0f;

	//		つまみの大きさ
	const DirectX::SimpleMath::Vector2 KNOB_LENGTH = { 15.0f, 33.0f };

public:

	enum UIType
	{
		Bar1,
		Bar2,
		BackGround,
		AudioSelect,
		OptionSelect,
		GamePlaySelect,
		Slide,
		AudioTitle
	};

private:

	//		スタンダードシェーダー
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

	//		上昇UI
	std::unique_ptr<AboveUI> m_aboveUI;

	//		スライダーUI
	std::unique_ptr<Slider> m_slider;

	//		メニューの選択
	std::unique_ptr<MenuSelect> m_menuSelect;

public:

	/*
	*	スタンダードシェーダーを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader.get(); }

	/*
	*	上昇UIを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	AboveUI* GetAboveUI() { return m_aboveUI.get(); }

	/*
	*	スライダーUIを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	Slider* GetSlider() { return m_slider.get(); }

	/*
	*	メニュー選択UIを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	MenuSelect* GetMenuSelect() { return m_menuSelect.get(); }
};