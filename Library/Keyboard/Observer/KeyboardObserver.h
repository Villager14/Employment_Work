/*
* @file		KeyboardObserver.h
* @brief	キーボードオブザーバー
* @author	Morita
* @date		2024/12/21
*/

#pragma once

#include "IKeyboardObserver.h"

#include "../KeyboardList.h"

class KeyboardObserver
{
public:

	//		コンストラクタ
	KeyboardObserver();

	//		デストラクタ
	~KeyboardObserver();

	/*
	*	押した瞬間のオブザーバーの追加
	*
	*	@param	(observer)	オブザーバー
	*	@param	(key)		キー入力
	*	@param	(keyboard)	キーボードの処理内容
	*/
	void AddPressedObserver(IKeyboardObserver* observer,
					 DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard);

	/*
	*	離した瞬間のオブザーバーの追加
	*
	*	@param	(observer)	オブザーバー
	*	@param	(key)		キー入力
	*	@param	(keyboard)	キーボードの処理内容
	*/
	void AddReleasedObserver(IKeyboardObserver* observer,
		DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard);

	/*
	*	キーを押しているオブザーバーの追加
	*
	*	@param	(observer)	オブザーバー
	*	@param	(key)		キー入力
	*	@param	(keyboard)	キーボードの処理内容
	*/
		void AddStateObserver(IKeyboardObserver* observer,
		DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard);

	/*
	*	押した瞬間のオブザーバーの削除
	*
	*	@param	(observer)	オブザーバー
	*/
	void DeletePressedObserver(KeyboardList::KeyboardList keyboard);

	/*
	*	離した瞬間のオブザーバーの削除
	*
	*	@param	(observer)	オブザーバー
	*/
	void DeleteReleasedObserver(KeyboardList::KeyboardList keyboard);

	/*
	*	キーを押しているオブザーバーの削除
	*
	*	@param	(observer)	オブザーバー
	*/
	void DeleteStateObserver(KeyboardList::KeyboardList keyboard);

	//	キーを押した時の処理
	void IsKeyPressed();

	//	キーを離した時の処理
	void IsKeyReleased();

	//	キーを押している時の処理
	void IsKeyState();

	//		全削除
	void Dalete();

private:

	//		キーを押した瞬間のオブザーバー
	std::unordered_map<KeyboardList::KeyboardList, std::pair<IKeyboardObserver*, DirectX::Keyboard::Keys>> m_keyPressedObserver;

	//		キーを離した瞬間のオブザーバー
	std::unordered_map<KeyboardList::KeyboardList, std::pair<IKeyboardObserver*, DirectX::Keyboard::Keys>> m_keyReleasedObserver;

	//		キーを押しているオブザーバー
	std::unordered_map<KeyboardList::KeyboardList, std::pair<IKeyboardObserver*, DirectX::Keyboard::Keys>> m_keyStateObserver;
};