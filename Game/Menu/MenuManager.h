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


#include "Game/PlayScene/UIManager/UIRender.h"

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

	//		スライダーの描画
	void SliderRender(DirectX::SimpleMath::Vector2 position);

public:

	enum MenuType
	{
		Start,
		Audio,

	};

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

	//		現在のタイプ
	MenuType m_type;

	//		現在の状態
	IMenu* m_state;

	//		メニューの状態の情報
	std::unordered_map<MenuType, std::unique_ptr<IMenu>> m_menuStateInformation;

	//		UIの描画
	//std::vector<std::unique_ptr<UIRender>> m_uiRender;

	std::unordered_map<UIType, std::unique_ptr<UIRender>> m_uiRender;

public:

	/*
	*	状態の切り替え
	* 
	*	@param	(type)	状態
	*/
	void ChangState(MenuType type);

	/*
	*	UIRnederの生成
	*
	*	@param	(type)		UIの種類
	*	@param	(path)		ファイルパス
	*	@param	(position)	座標
	*	@param	(size)		サイズ
	*/
	void CreateUIRender(UIType type, const wchar_t* path, DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size);


	/*
	*	UIのインスタンスを受け取る
	* 
	*	@return インスタンス
	*/
	std::unordered_map<UIType, std::unique_ptr<UIRender>>* GetUIRender() { return &m_uiRender; }
};