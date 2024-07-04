/*
* @file		FloorObject.h
* @brief	床オブジェクトの描画
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "WireObjectInformation.h"

class WireObject
{
public:

	//		コンストラクタ
	WireObject();

	//		デストラクタ
	~WireObject();

	//		初期化処理
	void Initialize(DirectX::SimpleMath::Vector3 position, int number);

	/*
	*	更新処理
	*
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition);

	/*
	*	描画処理
	* 
	*	@param	(drawMesh)	メッシュ描画のインスタンスのポインタ
	*/
	void Render();

	//		終了処理
	void Finalize();

private:

	//		ワイヤーモデル
	std::unique_ptr<DirectX::Model> m_wireModel;

	//		ワイヤーの範囲モデル
	std::unique_ptr<DirectX::Model> m_wireRangeModel;

	//		羽オブジェクト
	std::unique_ptr<DirectX::Model> m_wingModel;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//		デバック用のワールド座標
	DirectX::SimpleMath::Matrix m_debugWorld;
	
	//		範囲
	float m_range;

	//		回転
	float m_rotation;

	//		羽の座標
	std::vector<DirectX::SimpleMath::Vector3> m_wingPosition;

	//		情報
	WireObjectInformation m_information;

public:

	/*
	*	ワイヤーオブジェクトが使用可能か？
	* 
	*	@return 使用可能か true : 使用可能 false : 使用不可能
	*/
	bool GetWireAvailableJudgement() { return m_information.m_usedJudgement; }

	/*
	*	座標を受け取る
	* 
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_information.position; }

	WireObjectInformation* GetWireInformation() { return &m_information; }
};
