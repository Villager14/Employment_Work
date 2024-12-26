/*
* @file		MenuMousePointerUI.h
* @brief	メニューのマウスポインタ処理
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "Library/Shader/StandardShader.h"

class MenuMousePointerUI
{
public:

	//		コンストラクタ
	MenuMousePointerUI();

	//		デストラクタ
	~MenuMousePointerUI();

	//		初期化処理
	void Initialize();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:

	enum UIType
	{
		MousePointa,
	};

private:

	//		メッセージ背景のファイルパス
	const wchar_t* MOUSE_POINTA_FILE_PATH = L"Resources/Texture/Menu/Title/mousePointa.png";

private:

	//		スタンダードシェーダー
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

public:

	/*
	*	マウスの座標Xを設定する
	* 
	*	@param	(position)	座標
	*/
	void SetMousePositionX(int position) { 
		(*m_standardShader->GetUIInformation())[UIType::MousePointa].position.x = static_cast<int>(position) - LibrarySingleton::GetInstance()->GetScreenSize().x / 2.0f; }

	/*
	*	マウスの座標Yを設定する
	*
	*	@param	(position)	座標
	*/
	void SetMousePositionY(int position) { (*m_standardShader->GetUIInformation())[UIType::MousePointa].position.y = static_cast<float>(position) - LibrarySingleton::GetInstance()->GetScreenSize().y / 2.0f; }
};