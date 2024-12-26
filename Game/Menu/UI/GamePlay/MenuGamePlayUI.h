/*
* @file		MenuGamePlayUI.h
* @brief	メニューゲームプレイUIのタイトル
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "../MenuUITabEnums.h"

#include "Effect/UI/Menu/FrameWalkUI/FrameWalkUI.h"

#include "../../Collider/MenuColliderInformation.h"

#include "../SummarizeColliderInformation/MenuSummarizeColliderInformation.h"

class MenuGamePlayUI
{
public:

	MenuGamePlayUI(AboveUI* aboveUI,
		MenuSummarizeColliderInformation* summarizeColliderInformation);

	~MenuGamePlayUI();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

	//		タイプの取得
	void SetType(MenuUITaype::UIType type);

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
	void AddMenuColliderInformation(DirectX::SimpleMath::Vector2 *position, UISubType type);

	/*
	*	当たったボタン
	* 
	*	@param	(type)	当たったボタンタイプ
	*/
	void HitBunnton(UISubType type);

private:

	AboveUI* m_aboveUI;

	MenuUITaype::UIType m_type;

	//		移動量タイトル
	float m_titleMove;

	//		移動量ボタン
	float m_buttonMove;

	//		当たり判定を追加するかどうか
	bool m_colliderJudgement;

	//		当たり判定情報
	std::vector<MenuColliderInformation> m_colliderInformation;

	//		UIのフレームワーク
	std::unique_ptr<FrameWalkUI> m_frameWalkUI;

	//		当たり判定をまとめる1
	MenuSummarizeColliderInformation* m_summarizeColliderInformation;
public:

	//		メッシュの当たり判定
	std::vector<MenuColliderInformation>* GetMeshColliderInformation() { return &m_colliderInformation; }
};