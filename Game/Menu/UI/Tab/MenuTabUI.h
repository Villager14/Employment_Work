/*
* @file		MenuTabUI.h
* @brief	メニューのTabUI
* @author	Morita
* @date		2024/12/19
*/

#include "Effect/UI/Menu/AboveUI/AboveUI.h"

#include "Effect/UI/Menu/MenuSelect/MenuSelect.h"

#include "../MenuUITabEnums.h"

#include "../../Collider/MenuColliderInformation.h"

#include "../SummarizeColliderInformation/MenuSummarizeColliderInformation.h"

class MenuTabUI
{
public:

	//		コンストラクタ
	MenuTabUI(AboveUI* abvoceUI,
		MenuSummarizeColliderInformation* summarizeColliderInformation);

	//		デストラクタ
	~MenuTabUI();

	//		初期化処理
	void Initialize();
	
	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	/*
	*	タブUIの移動
	*
	*	@param	(move)	移動量(0~1)
	*/
	void TabMove(float move);

	/*
	*	スライダーの当たり判定情報の追加
	*
	*	@param	(position)	座標
	*	@param	(type)		UIタイプ
	*/
	void AddMenuColliderInformation(DirectX::SimpleMath::Vector2 *position, UISubType type);

private:

	//		上昇UI
	AboveUI* m_abvoceUI;

	//		メニューの項目選択
	std::unique_ptr<MenuSelect> m_menuSelect;

	//		移動量
	float m_move;

	//		メニューのタイプ
	MenuUITaype::UIType m_type;

	//		エフェクト経過時間
	float m_effectElapsedTime;

	//		当たっているかどうか
	bool m_hitJudgement;

	bool m_colliderJudgement;

	//		当たり判定情報
	std::vector<MenuColliderInformation> m_colliderInformation;

	//		当たり判定をまとめる1
	MenuSummarizeColliderInformation* m_summarizeColliderInformation;

	//		Tabを使うかどうか
	bool m_useJudgement;

public:

	/*
	*	メニュー種類を設定する
	* 
	*	@param	(type)	UIの種類
	*/
	void SetTabType(MenuUITaype::UIType type) { m_type = type; m_hitJudgement = true; }

	std::vector<MenuColliderInformation>* GetMeshColliderInformation() { return &m_colliderInformation; }

	void TabUserJudgement(bool judgement) { m_useJudgement = judgement; }
};