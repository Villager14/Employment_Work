/*
* @file		FloorObject.h
* @brief	床オブジェクトの描画
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

class WallObject
{
public:

	//		コンストラクタ
	WallObject();

	//		デストラクタ
	~WallObject();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	/*
	*	描画処理
	* 
	*	@param	(drawMesh)	メッシュ描画のインスタンスのポインタ
	*/
	void Render(DrawMesh* drawMesh);

	//		終了処理
	void Finalize();

private:

	//		床モデル
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		オブジェクトのメッシュ
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	DirectX::SimpleMath::Vector3 m_move;

public:

	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return インスタンス
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};
