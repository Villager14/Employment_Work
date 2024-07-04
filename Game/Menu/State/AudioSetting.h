/*
* @file		AudioSetting.h
* @brief	音の設定
* @author	Morita
* @date		2024/07/03
*/

#pragma once

#include "../IMenu.h"

#include "../MenuManager.h"

class MenuManager;

class AudioSetting : public IMenu
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	()
	*/
	AudioSetting(MenuManager* menuManager);

	//		デストラクタ
	~AudioSetting();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

private:

	//		メニューマネージャーのインスタンスのポインタ
	MenuManager* m_menuManager;

};