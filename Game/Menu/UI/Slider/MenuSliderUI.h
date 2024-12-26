/*
* @file		MenuSliderUI.h
* @brief	メニューのスライダーUI
* @author	Morita
* @date		2024/12/20
*/

#pragma once

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "Effect/UI/Menu/Slider/Slider.h"

#include "../MenuUITabEnums.h"

#include "../../Collider/MenuColliderInformation.h"

class MenuSliderUI
{
public:

	//		コンストラクタ
	MenuSliderUI(AboveUI* abvoceUI);

	//		デストラクタ
	~MenuSliderUI();

	//		初期化処理
	void Initialize();
	
	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:

	//		オーディオの描画
	void AudioRender();

	//		ゲームプレイの描画
	void GamePlayRender();

	//		オプションの描画
	void OptionRender();

	/*
	*	スライダー背景の描画
	* 
	*	@param	(position)	座標
	*/
	void SliderBackGroundRender(DirectX::SimpleMath::Vector2 position);

	/*
	*	スライダーの当たり判定情報の追加
	* 
	*	@param	(position)	座標
	*	@param	(type)		UIタイプ
	*/
	void AddMenuColliderInformation(DirectX::SimpleMath::Vector2 position, UISubType type);

public:

	/*
	*	スライダーUIの移動
	*
	*	@param	(move)	移動量(0~1)
	*/
	void SliderMove(float move);

	std::vector<MenuColliderInformation>* GetMeshColliderInformation() { return &m_colliderInformation; }

private:

	//		上昇UI
	AboveUI* m_abvoceUI;

	//		移動量
	float m_move;

	//		メニューのタイプ
	MenuUITaype::UIType m_type;

	//		エフェクト経過時間
	float m_effectElapsedTime;

	//		スライダーUI
	std::unique_ptr<Slider> m_slider;

	//		当たり判定情報
	std::vector<MenuColliderInformation> m_colliderInformation;

public:

	/*
	*	メニュー種類を設定する
	* 
	*	@param	(type)	UIの種類
	*/
	void SetSliderType(MenuUITaype::UIType type);
};