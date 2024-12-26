/*
* @file		MenuTabUI.h
* @brief	メニューのTabUI
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "Library/Shader/StandardShader.h"

class MenuBackGround
{
public:

	MenuBackGround();

	~MenuBackGround();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

	/*
	*	バーのスケールの変更
	* 
	*	@param	(float scale)
	*/
	void BarScale(float scale);

	/*
	*	メニューの動く処理
	* 
	*	@param	(move)	移動量（0~1）
	*/
	void MenuMoveProcess(float move);

private:

	enum UIType
	{
		BackGround,
		Bar1,
		Bar2,
	};

private:

	//		メッセージバーのファイルパス
	const wchar_t* MESSAGE_BAR_FILE_PATH = L"Resources/Texture/UI/GameClear/messegeBer.png";

	//		メッセージ背景のファイルパス
	const wchar_t* MESSAGE_BACK_FILE_PATH = L"Resources/Texture/UI/GameClear/messegeBack.png";

	//		メッセージバー１のメニューが閉じているときの座標
	const DirectX::SimpleMath::Vector2 MESSAGE_BAR1_CLOSE_POSITION = { 0.0f, 13.0f };

	//		メッセージバー１のメニューが開ているときの座標
	const DirectX::SimpleMath::Vector2 MESSAGE_BAR1_OPEN_POSITION = { 0.0f, 300.0f };

	//		メッセージバー２のメニューが閉じているときの座標
	const DirectX::SimpleMath::Vector2 MESSAGE_BAR2_CLOSE_POSITION = { 0.0f, -13.0f };

	//		メッセージバー２のメニューが開ているときの座標
	const DirectX::SimpleMath::Vector2 MESSAGE_BAR2_OPEN_POSITION = { 0.0f, -300.0f };

private:

	//		スタンダードシェーダー
	std::unique_ptr<StandardShader<UIType>> m_standardShader;


};