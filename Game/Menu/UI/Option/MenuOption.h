/*
* @file		MenuOption.h
* @brief	メニューオプションUIのタイトル
* @author	Morita
* @date		2024/12/25
*/

#pragma once

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "../MenuUITabEnums.h"

#include "../../Collider/MenuColliderInformation.h"

#include "../SummarizeColliderInformation/MenuSummarizeColliderInformation.h"

#include "Effect/UI/Menu/Slider/Slider.h"

class MenuOption
{
public:

	MenuOption(AboveUI* aboveUI,
		Slider* slider,
		MenuSummarizeColliderInformation* summarizeColliderInformation);

	~MenuOption();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

	//		タイプの取得
	void SetType(MenuUITaype::UIType type);

	/*
	*	スライダー背景の描画
	*
	*	@param	(position)	座標
	*/
	void SliderBackGroundRender(DirectX::SimpleMath::Vector2 position);

	/*
	*	タイトルの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	void TitleMoveProcess(float move);
	
	/*
	*	ボタンの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	void ButtonMoveProcess(float move);

	/*
	*	スライダーの当たり判定情報の追加
	*
	*	@param	(position)	座標
	*	@param	(type)		UIタイプ
	*/
	void AddMenuColliderInformation(DirectX::SimpleMath::Vector2* position, UISubType type);

private:

	AboveUI* m_aboveUI;

	MenuUITaype::UIType m_type;

	//		移動量タイトル
	float m_titleMove;

	//		移動量ボタン
	float m_buttonMove;

	//		当たり判定を行うかどうか
	bool m_colliderJudgement;

	//		スライダー
	Slider* m_slider;

	//		当たり判定情報
	std::vector<MenuColliderInformation> m_colliderInformation;

	//		当たり判定をまとめる1
	MenuSummarizeColliderInformation* m_summarizeColliderInformation;
public:

	//		メッシュの当たり判定
	std::vector<MenuColliderInformation>* GetMeshColliderInformation() { return &m_colliderInformation; }
};