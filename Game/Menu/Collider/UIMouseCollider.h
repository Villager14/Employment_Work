/*
* @file		UIMouseCollider.h
* @brief	メニューのUIの当たり判定
* @author	Morita
* @date		2024/12/20
*/

#include "pch.h"

#include "../Observer/Mouse/IMenuMouseObserver.h"

#include "../Collider/MenuColliderInformation.h"

#include "../Observer/Collider/MenuColliderObserver.h"

class UIMouseCollider : public IMenuMouseObserver
{
public:

	//		コンストラクタ
	UIMouseCollider();

	//		デストラクタ
	~UIMouseCollider();

	//		終了処理
	void Finalize();

	/*
	*	マウスのX座標の更新
	*
	*	@param	(x) x座標
	*/
	void MousePositionX(int x) override;

	/*
	*	マウスのY座標の更新
	*
	*	@param	(y) y座標
	*/
	void MousePositionY(int y) override;

	void CollitionProcess(const std::vector<MenuColliderInformation>& information);

	/*
	*	四角の当たり判定の処理
	* 
	*	@param	(information)	メッシュの情報
	*	@param	(boxLength)		四角の半分の長さ
	*/
	void BoxColliderProcess(MenuColliderInformation information,
							DirectX::SimpleMath::Vector2 boxLength);

	/*
	*	四角の当たり判定
	*
	*	@param	(min)	最小値
	*	@param	(max)	最大値
	*	@return true : 当たっている false : 当たっていない
	*/
	bool BoxCollider(DirectX::SimpleMath::Vector2 min, DirectX::SimpleMath::Vector2 max);

private:

	//		つまみの大きさ
	const DirectX::SimpleMath::Vector2 KNOB_LENGTH = { 15.0f, 33.0f };

	//		タブの大きさ
	const DirectX::SimpleMath::Vector2 TAB_LENGTH = { 140.0f, 52.0f };

	//		ボタンの大きさ
	const DirectX::SimpleMath::Vector2 BUTTON_LENGTH = { 199.0f, 58.0f };

private:

	//		マウスの座標X
	int m_mousePositionX;

	//		マウスの座標Y
	int m_mousePositionY;

	//		当たり判定オブザーバー
	std::unique_ptr<MenuColliderObserver> m_colliderObserver;

public:

	/*
	*	オブザーバーの追加
	* 
	*	@param	オブザーバのインスタンスのポインタ
	*/
	void AddColliderObserver(IMenuColliderObserver* observer) { m_colliderObserver->AddObserver(observer); }
};