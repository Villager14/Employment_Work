/*
* @file		KeyboardManager.h
* @brief	キーボードマネージャー
* @author	Morita
* @date		2024/12/21
*/

#pragma once

#include "Observer/KeyboardObserver.h"

class KeyboardManager
{
public:

	KeyboardManager();

	~KeyboardManager();

	void Update();

	void Finalize();

public:

	enum KeyType
	{
		Pressed,
		Released,
		State,
	};

public:

	/*
	*	キーボードの入力処理を追加する
	* 
	*	@param	(observer)	オブザーバーのポインタのインスタンス
	*	@param	(key)		キー入力
	*	@param	(keyboard)	キーボードの処理
	*	@param	(type)		キーの種類
	*/
	void AddKeyboard(IKeyboardObserver* observer,
		DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard, KeyType type);

	/*
	*	キーボードの入力処理の削除
	* 
	*	@param	(keyboard)	キーボードの処理
	*	@param	(type)		キーの種類
	*/
	void DeleteKeyboard(KeyboardList::KeyboardList keyboard, KeyType type);

private:

	//		キーボードオブザーバー
	std::unique_ptr<KeyboardObserver> m_keyboardObserver;

};