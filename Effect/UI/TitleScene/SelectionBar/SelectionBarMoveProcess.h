/*
* @file		SelectionBarMoveProcess.h
* @brief	選択バーの移動処理
* @author	Morita
* @date		2024/12/12
*/

#pragma once

class SelectionBar;

class SelectionBarMoveProcess
{
public:

	/*
	*	コンストラクタ
	*
	*	@param	(selectionBar)	選択バーのポインタ
	*/
	SelectionBarMoveProcess(SelectionBar* selectionBar);

	//		デストラクタ
	~SelectionBarMoveProcess();

	/*
	*	中心と上の間の処理
	*
	*	@param	(direction)	向き
	*	@param	(time)		経過時間
	*	@param	(position)	座標
	*	@param	(scale)		スケール
	*/
	void CenterToTopProcess(bool direction, float time,
		DirectX::SimpleMath::Vector2* position,
		DirectX::SimpleMath::Vector2* scale);

	/*
	*	中心と下の間の処理
	*
	*	@param	(direction)	向き
	*	@param	(time)		経過時間
	*	@param	(position)	座標
	*	@param	(scale)		スケール
	*/
	void CenterToBottom(bool direction, float time,
		DirectX::SimpleMath::Vector2* position,
		DirectX::SimpleMath::Vector2* scale);

	/*
	*	上と下の間の処理
	*
	*	@param	(direction)	向き
	*	@param	(time)		経過時間
	*	@param	(position)	座標
	*	@param	(scale)		スケール
	*/
	void FromTopToBottom(bool direction, float time,
		DirectX::SimpleMath::Vector2* position,
		DirectX::SimpleMath::Vector2* scale);

private:

	/*
	*	減少処理
	*
	*	@param	(time)	時間
	*/
	inline void DecreaseValue(float time);

	/*
	*	上昇処理
	*
	*	@param	(time)	時間
	*/
	inline void ElevatedValue(float time);

	/*
	*	座標とサイズの更新
	* 
	*	@param	(position)	座標
	*	@param	(scale)		スケール
	*/
	void PositionSizeUpdate(DirectX::SimpleMath::Vector2* position,
		DirectX::SimpleMath::Vector2* scale);

private:

	//		初期座標
	DirectX::SimpleMath::Vector2 m_firstPosition;

	//		最終座標
	DirectX::SimpleMath::Vector2 m_endPosition;

	SelectionBar* m_selectionBar;

	//		遷移量(移動)
	float m_move;

	//		遷移量(サイズ)
	float m_size;

	//		初期サイズ
	float m_firstSize;

	//		最終サイズ
	float m_endSize;

};