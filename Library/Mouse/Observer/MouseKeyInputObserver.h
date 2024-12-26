/*
* @file		MouseKeyInputObserver.h
* @brief	マウスのキー入力オブザーバー
* @author	Morita
* @date		2024/12/22
*/

#pragma once

#include "IMouseKeyInputObserver.h"

#include "../MouseList.h"

#include "Process/MouseKeyInputProcess.h"

class MouseKeyInputObserver
{
public:

	//		コンストラクタ
	MouseKeyInputObserver();

	//		デストラクタ
	~MouseKeyInputObserver();

	/*
	*	マウスの押した時のオブザーバーの追加
	*
	*	@param	(observer)		オブザーバー
	*	@param	(buttonState)	マウス入力
	*	@param	(key)			使用するキー
	*/
	void AddPressedObserver(IMouseKeyInputObserver* observer,
		KeyInputMouse::MouseState state, KeyInputMouse::MouseList key);

	/*
	*	マウスの離した時のオブザーバーの追加
	*
	*	@param	(observer)		オブザーバー
	*	@param	(buttonState)	マウス入力
	*	@param	(key)			使用するキー
	*/
	void AddReleasedObserver(IMouseKeyInputObserver* observer,
		KeyInputMouse::MouseState state, KeyInputMouse::MouseList key);

	/*
	*	マウスの押し続けたの時のオブザーバーの追加
	*
	*	@param	(observer)		オブザーバー
	*	@param	(buttonState)	マウス入力
	*	@param	(key)			使用するキー
	*/
	void AddKeepPushingObserver(IMouseKeyInputObserver* observer,
		KeyInputMouse::MouseState state, KeyInputMouse::MouseList key);

	/*
	*	マウスをキーを押したときのオブザーバーの削除
	*
	*	@param	(MouseList)	マウスのキー
	*/
	void DeletePressedObserver(KeyInputMouse::MouseList keyboard);

	/*
	*	マウスをキーを離した時のオブザーバーの削除
	*
	*	@param	(MouseList)	マウスのキー
	*/
	void DeleteReleasedObserver(KeyInputMouse::MouseList keyboard);

	/*
	*	マウスの押し続けたのオブザーバーの削除
	*
	*	@param	(MouseList)	マウスのキー
	*/
	void DeleteKeepPushingObserver(KeyInputMouse::MouseList keyboard);

	//	マウスの押した瞬間の処理
	void IsKeyPressed();

	//	マウスの離した瞬間の処理
	void IsKeyReleased();

	//	マウスの押し続けた時の処理
	void IsKeepPushing();

	//		全削除
	void Dalete();

private:

	//		マウスの入力処理
	std::unique_ptr<MouseKeyInputProcess> m_keyInputProcess;

	//		マウスを押したときのオブザーバー
	std::unordered_map<KeyInputMouse::MouseList, std::pair<IMouseKeyInputObserver*, KeyInputMouse::MouseState>> m_pressedObserver;

	//		マウスの離したときのキーオブザーバー
	std::unordered_map<KeyInputMouse::MouseList, std::pair<IMouseKeyInputObserver*, KeyInputMouse::MouseState>> m_releasedObserver;

	//		マウスの押し続けたの時のキーオブザーバー
	std::unordered_map<KeyInputMouse::MouseList, std::pair<IMouseKeyInputObserver*, KeyInputMouse::MouseState>> m_keepPushingObserver;
};