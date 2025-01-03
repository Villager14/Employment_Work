/*
* @file		AboveUI.h
* @brief	UIの上昇処理
* @author	Morita
* @date		2024/07/09
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class MenuSelect
{
public:

	//		コンストラクタ
	MenuSelect();

	//		デストラクタ
	~MenuSelect();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
		DirectX::SimpleMath::Vector4 time;					//		時間
	};

private:

	//		選択テクスチャ
	const wchar_t* SELECT_TEXTURE = L"Resources/Texture/Menu/Select/Select.png";

	//		メニュー選択VS
	const wchar_t* SELECT_MENU_VS_TEXTURE = L"Resources/Shader/UI/MenuSelect/MenuSelectVS.cso";

	//		メニュー選択GS
	const wchar_t* SELECT_MENU_GS_TEXTURE = L"Resources/Shader/UI/MenuSelect/MenuSelectGS.cso";

	//		メニュー選択PS
	const wchar_t* SELECT_MENU_PS_TEXTURE = L"Resources/Shader/UI/MenuSelect/MenuSelectPS.cso";


private:

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_shader;

	//		コンストバッファ
	ConstBuffer m_constBuffer;

	float m_time;

public:

	/*
	*	描画処理
	*
	*	@param	(type)	描画するUIの種類
	*/
	void Render(DirectX::SimpleMath::Vector2 position);

	//		時間のリセット
	void TimeReset() { m_time = 0.0f; };
};